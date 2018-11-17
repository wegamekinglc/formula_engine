#pragma once

#include <fel/settings.hpp>
#include <fel/operators/nodes.hpp>
#include <fel/operators/crosssections.hpp>
#include <fel/time/date.hpp>
#include <fel/data/pgstore.hpp>
#include <fel/time/calendars/china.hpp>


namespace FEngine {
    inline const Last& CLOSE() {
        static Last res("closePrice");
        return res;
    }

    inline const Last& OPEN() {
        static Last res("openPrice");
        return res;
    }

    inline const Last& HIGH() {
        static Last res("highestPrice");
        return res;
    }

    inline const Last& LOW() {
        static Last res("lowestPrice");
        return res;
    }

    inline const Last& PE() {
        static Last res("PE");
        return res;
    }

    inline const Last& PB() {
        static Last res("PB");
        return res;
    }
}