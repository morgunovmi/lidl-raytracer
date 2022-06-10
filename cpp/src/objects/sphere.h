#pragma once

#include "hittable.h"
#include "materials/material.h"

class sphere : public hittable {
public:
    sphere() = default;
    sphere(point3 center, double radius, std::shared_ptr<material> mat_ptr)
        : m_center(center), m_radius(radius), m_mat_ptr(mat_ptr) {}

    virtual bool hit(
        const ray& r, double t_min, double t_max, hit_info& info
    ) const override;

private:
    point3 m_center;
    double m_radius;
    std::shared_ptr<material> m_mat_ptr;
};

inline bool sphere::hit(const ray &r, double t_min, double t_max, hit_info &info) const {
    const auto oc = r.origin() - m_center;
    const auto a = r.direction().dot(r.direction());
    const auto half_b = r.direction().dot(oc);
    const auto c = oc.dot(oc) - m_radius * m_radius; 
    const auto discr = half_b * half_b - a * c;

    if (discr < 0) {
        return false;
    } 
    const auto sqrtd = std::sqrt(discr);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    info.t = root;
    info.p = r.at(root);
    const auto outward_normal = (info.p - m_center) / m_radius;
    info.set_face_normal(r, outward_normal);
    info.mat_ptr = m_mat_ptr;

    return true;
}
