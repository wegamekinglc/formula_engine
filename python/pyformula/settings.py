"""
Created on 2018-9-24

@author: cheng.li
"""

import datetime as dt
from contextlib import contextmanager


REF_DATE = None
SYMBOLS = None


def parse_date(value):
    if isinstance(value, dt.datetime):
        return value
    else:
        return dt.datetime.strptime(value, '%Y-%m-%d')


@contextmanager
def set_global_date(ref_date):
    global REF_DATE
    try:
        REF_DATE = parse_date(ref_date)
        yield
    finally:
        REF_DATE = None


def global_date():
    return REF_DATE


@contextmanager
def set_global_symbols(symbols):
    global SYMBOLS
    try:
        SYMBOLS = symbols
        yield
    finally:
        SYMBOLS = None


def global_symbols():
    return SYMBOLS
