#pragma once

#include "math/math.h"

using slr::Vec3d;
using slr::point3;

class ray {
public:
    ray() = default;
    ray(const Vec3d& origin, const Vec3d& direction) : m_origin(origin), m_direction(direction) {}

    point3 origin() const { return m_origin; }
    Vec3d direction() const { return m_direction; }

    Vec3d at(double t) const { return m_origin + m_direction * t; }

private:
    Vec3d m_origin;
    Vec3d m_direction;
};
