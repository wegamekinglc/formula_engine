#pragma once

#include <fel/settings.hpp>
#include <fel/operators/nodes.hpp>
#include <fel/operators/crosssections.hpp>
#include <fel/time/date.hpp>
#include <fel/data/pgstore.hpp>

namespace FEngine {
    inline const Last& CLOSE() {
        static Last res("close");
        return res;
    }

    inline const Last& OPEN() {
        static Last res("OPEN");
        return res;
    }

    inline const Last& HIGH() {
        static Last res("high");
        return res;
    }

    inline const Last& LOW() {
        static Last res("low");
        return res;
    }
}