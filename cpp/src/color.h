#pragma once

#include <fmt/format.h>
#include <fstream>

#include "math/math.h"

inline void write_color(std::ofstream &ofs, slr::color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x;
    auto g = pixel_color.y;
    auto b = pixel_color.z;

    const auto scale = 1.0 / samples_per_pixel;
    r = std::sqrt(r * scale);
    g = std::sqrt(g * scale);
    b = std::sqrt(b * scale);

    ofs << fmt::format("{} {} {}\n",
                       static_cast<int>(std::clamp(r, 0.0, 0.999) * 256),
                       static_cast<int>(std::clamp(g, 0.0, 0.999) * 256),
                       static_cast<int>(std::clamp(b, 0.0, 0.999) * 256));
}
