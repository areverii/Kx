#pragma once

#include "../Base/Definitions.h"

#include <vector>

namespace KRASKA {

    class FrameBuffer {

    public:
        FrameBuffer(uint width, uint height);

        void set_pixel(uint x, uint y, Color color);
        auto get_pixel(uint x, uint y) const->Color;

        void reset();

    private:
        uint width;
        uint height;

        auto pixel_index(uint x, uint y) const->uint;

        std::vector<Color> buffer;
    };
}