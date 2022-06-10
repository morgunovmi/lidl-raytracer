#pragma once

#include "material.h"
#include "rt_header.h"
#include "objects/hittable.h"

class metal : public material {
public:
    metal(const color& a, double f) : m_albedo(a), m_fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(
        const ray& r_in, const hit_info& info, color& attenuation, ray& scattered
    ) const override {
        const auto reflected = reflect(r_in.direction().normalize(), info.normal); 
        scattered = ray{ info.p, reflected + m_fuzz * random_in_unit_sphere() };
        attenuation = m_albedo;
        return (info.normal.dot(scattered.direction()) > 0);
    }

private:
    color m_albedo;
    double m_fuzz;
};
