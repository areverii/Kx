#pragma once

#include "../Base/Definitions.h"
#include "../Base/Options.h"

#include "../Util/bitwise.h"
#include "../Util/KRboy_Log.h"

#include <cstdio>

namespace KRASKA {

    class Serial {

    public:
        Serial(Options& inOptions) : options(inOptions) {}

        auto read() const->u8;
        void write(u8 byte);
        void write_control(u8 byte) const;

    private:
        Options& options;

        u8 data;
    };
}