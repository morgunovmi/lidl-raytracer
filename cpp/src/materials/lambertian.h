#pragma once

#include "material.h"
#include "objects/hittable.h"

class lambertian : public material {
public:
    lambertian(const slr::color& a) : m_albedo(a) {} 

    virtual bool scatter(
        const ray& r_in, const hit_info& info, slr::color& attenuation, ray& scattered
    ) const override {
        auto scatter_direction = info.normal + slr::random_unit_vector(); 

        if (scatter_direction.near_zero()) {
            scatter_direction = info.normal;
        }

        scattered = ray{ info.p, scatter_direction };
        attenuation = m_albedo;

        return true;
    }

private:
    slr::color m_albedo;
};
