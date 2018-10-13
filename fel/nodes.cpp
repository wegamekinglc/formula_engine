#include <fel/nodes.hpp>
#include <fel/settings.hpp>

namespace FEngine {

    Depends Last::depends(const DateTime& base) const {
        vector<DateTime> dts(1, base);
        Depends res;
        res[name_] = dts;
        return res;
    }

    Series Last::calculate(const DataPack& data, const DateTime& base) const {
        vector<string> symbols = Settings::instance().symbols();
        vector<double> values(symbols.size());
        for(size_t i = 0; i != symbols.size(); ++i) {
            values[i] = data.at(symbols[i]).at(name_).at(base);
        }
        return Series(symbols, values);
    }
}