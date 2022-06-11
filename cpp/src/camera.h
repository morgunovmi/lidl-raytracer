#pragma once

#include <algorithm>
#include "rt_header.h"

class camera {
public:
    camera(
        point3 lookfrom,
        point3 lookat,
        Vec3d vup,
        double vfov, // deg
        double aspect_ratio,
        double aperture,
        double focus_dist
    ) {
        const auto theta = deg_to_rad(vfov);
        const auto h = std::tan(theta / 2);
        const auto viewport_height = 2.0 * h;
        const auto viewport_width = aspect_ratio * viewport_height;

        m_w = (lookfrom - lookat).normalize();
        m_u = (vup ^ m_w).normalize();
        m_v = m_w ^ m_u;

        m_origin = lookfrom;
        m_horizontal = focus_dist * viewport_width * m_u;
        m_vertical = focus_dist * viewport_height * m_v;
        m_lower_left_corner = m_origin - m_horizontal / 2.0 - m_vertical / 2.0 - focus_dist * m_w;

        m_lens_radius = aperture / 2;
    }

    ray get_ray(double s, double t) const {
        const auto rd = m_lens_radius * random_in_unit_disk();
        const auto offset = m_u * rd.x + m_v * rd.y;
        return {m_origin + offset, m_lower_left_corner + s * m_horizontal + t * m_vertical - m_origin - offset};
    }

private:
    point3 m_origin;
    point3 m_lower_left_corner;
    Vec3d m_horizontal;
    Vec3d m_vertical;
    Vec3d m_u, m_v, m_w;

    double m_lens_radius;
};
