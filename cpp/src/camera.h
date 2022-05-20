#pragma once

#include "rt_header.h"

class camera {
public:
    camera() {
        const auto aspect_ratio = 16.0 / 9.0; 
        const auto viewport_height = 2.0;
        const auto viewport_width = aspect_ratio * viewport_height;
        const auto focal_length = 1.0;

        m_origin = {0, 0, 0};
        m_horizontal = {viewport_width, 0, 0};
        m_vertical = {0, viewport_height, 0};
        m_lower_left_corner = m_origin - Vec3d{0, 0, focal_length} - m_horizontal / 2.0 - m_vertical / 2.0;
    }

    ray get_ray(double u, double v) const {
        return {m_origin, m_lower_left_corner + u * m_horizontal + v * m_vertical};
    }

private:
    point3 m_origin;
    point3 m_lower_left_corner;
    Vec3d m_horizontal;
    Vec3d m_vertical;
};
