#pragma once

#include "rt_header.h"

class material;

struct hit_info {
    slr::point3 p;
    Vec3d normal;
    std::shared_ptr<material> mat_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const Vec3d& outward_normal) {
        front_face = r.direction().dot(outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_info& info) const = 0;

    virtual ~hittable() = default;
};
