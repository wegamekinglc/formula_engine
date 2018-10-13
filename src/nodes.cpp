#include "nodes.hpp"

namespace FEngine {

    Depends Last::depends(const DateTime& base) const {
        return Depends(name_, base);
    }

    Series Last::calculate(const DataPack& data, const DateTime& base) const {
        
    }

}