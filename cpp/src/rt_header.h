#pragma once

#include <limits>
#include <fmt/format.h>

// Constants

const double inf = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Util

inline double deg_to_rad(double degrees) {
    return degrees * pi / 180.0;
}

// Common headers

#include "ray.h"
#include "math/math.h"
