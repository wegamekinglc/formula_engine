#pragma once

#include <fel/settings.hpp>
#include <fel/operators/nodes.hpp>
#include <fel/operators/crosssections.hpp>

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