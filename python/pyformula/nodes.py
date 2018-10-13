"""
Created on 2018-9-24

@author: cheng.li
"""

import copy
import datetime as dt
import math
import pandas as pd
from pyformula.settings import global_date
from pyformula.settings import global_symbols


def parse_name(name):
    if isinstance(name, Node):
        return name
    else:
        return Last(name)


def merge_depends(lhs, rhs):
    ret = copy.deepcopy(lhs)
    for name in lhs:
        if name in rhs:
            ret[name] += rhs[name]

    for name in rhs:
        if name not in lhs:
            ret[name] = rhs[name]

    return ret


def shift_dates(base, p):
    return [base] + [base + dt.timedelta(days=-i) for i in range(1, p)]


class Node:

    def __add__(self, rhs):
        return PlusOperator(self, rhs)

    def __sub__(self, rhs):
        return MinusOperator(self, rhs)

    def __mul__(self, rhs):
        return TimesOperator(self, rhs)

    def __truediv__(self, rhs):
        return DividesOperator(self, rhs)

    def __neg__(self):
        return NegativeOperator(self)

    def clone(self):
        return copy.deepcopy(self)


class Last(Node):

    def __init__(self, name):
        self.name = name

    def depends(self, base_date):
        return {self.name: [base_date]}

    def calculate(self, data, base_date):
        ret = {}
        for symbol in global_symbols():
            if symbol in data:
                ret[symbol] = data[symbol][self.name][base_date]
            else:
                ret[symbol] = math.nan

        return pd.Series(ret)


class MovingAverage(Node):

    def __init__(self, name, window):
        self.inner = parse_name(name)
        self.window = window

    def depends(self, base_date):
        base_dates = shift_dates(base_date, self.window)
        ret = {}
        for date in base_dates:
            ret = merge_depends(ret, self.inner.depends(date))
        return ret

    def calculate(self, data, base_date):
        base_dates = shift_dates(base_date, self.window)
        values = [self.inner.calculate(data, base_date) for base_date in base_dates]
        return sum(values) / self.window


class UnaryOperator(Node):

    def __init__(self, rhs):
        super().__init__()
        self.rhs = rhs.clone()

    def depends(self, base_date):
        return self.rhs.depends(base_date)


class NegativeOperator(UnaryOperator):

    def __init__(self, rhs):
        super().__init__(rhs)

    def calculate(self, data, base_date):
        return -self.rhs.calculate(data, base_date)


class BinaryOperator(Node):

    def __init__(self, lhs, rhs):
        super().__init__()
        self.lhs = lhs.clone()
        self.rhs = rhs.clone()

    def depends(self, base_date):
        return merge_depends(self.lhs.depends(base_date), self.rhs.depends(base_date))


class PlusOperator(BinaryOperator):

    def __init__(self, lhs, rhs):
        super().__init__(lhs, rhs)

    def calculate(self, data, base_date):
        return self.lhs.calculate(data, base_date) + self.rhs.calculate(data, base_date)


class MinusOperator(BinaryOperator):

    def __init__(self, lhs, rhs):
        super().__init__(lhs, rhs)

    def calculate(self, data, base_date):
        return self.lhs.calculate(data, base_date) - self.rhs.calculate(data, base_date)


class TimesOperator(BinaryOperator):

    def __init__(self, lhs, rhs):
        super().__init__(lhs, rhs)

    def calculate(self, data, base_date):
        return self.lhs.calculate(data, base_date) * self.rhs.calculate(data, base_date)


class DividesOperator(BinaryOperator):

    def __init__(self, lhs, rhs):
        super().__init__(lhs, rhs)

    def calculate(self, data, base_date):
        return self.lhs.calculate(data, base_date) / self.rhs.calculate(data, base_date)


if __name__ == '__main__':
    import numpy as np
    from pyformula.settings import set_global_date
    from pyformula.settings import set_global_symbols

    periods = 4
    ref_date = dt.datetime(2018, 9, 2)
    rel_dates = shift_dates(ref_date, 4)
    sample_data = pd.Series(np.arange(0., periods, 1.), rel_dates)
    data_pack = dict(aapl=dict(ep=sample_data,
                               roe=sample_data),
                     goog=dict(ep=-sample_data,
                               roe=-sample_data))

    with set_global_date(ref_date), set_global_symbols(['aapl', 'goog']):
        res = Last("ep") + MovingAverage(-Last("roe"), 4)
        print(res.depends(global_date()))

        print(res.calculate(data_pack, ref_date))
