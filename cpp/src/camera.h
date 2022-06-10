#pragma once

#include "rt_header.h"

class camera {
public:
    camera(
        point3 lookfrom,
        point3 lookat,
        Vec3d vup,
        double vfov, // deg
        double aspect_ratio
    ) {
        const auto theta = deg_to_rad(vfov);
        const auto h = std::tan(theta / 2);
        const auto viewport_height = 2.0 * h;
        const auto viewport_width = aspect_ratio * viewport_height;

        const auto w = (lookfrom - lookat).normalize();
        const auto u = (vup ^ w).normalize();
        const auto v = w ^ u;

        m_origin = lookfrom;
        m_horizontal = viewport_width * u;
        m_vertical = viewport_height * v;
        m_lower_left_corner = m_origin - m_horizontal / 2.0 - m_vertical / 2.0 - w;
    }

    ray get_ray(double u, double v) const {
        return {m_origin, m_lower_left_corner + u * m_horizontal + v * m_vertical - m_origin};
    }

private:
    point3 m_origin;
    point3 m_lower_left_corner;
    Vec3d m_horizontal;
    Vec3d m_vertical;
};
