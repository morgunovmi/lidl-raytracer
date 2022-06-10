#include "material.h" 
#include "objects/hittable.h"

class dielectric : public material {
public:
    dielectric(double index_of_refraction) : m_ir(index_of_refraction) {} 

    virtual bool scatter(
        const ray &r_in, const hit_info &info, color &attenuation, ray &scattered
    ) const override {
        attenuation = color{1.0, 1.0, 1.0};
        const auto refraction_ratio = info.front_face ? (1.0 / m_ir) : m_ir;

        const auto unit_direction = r_in.direction().normalize();
        const auto cos_theta = (-unit_direction).dot(info.normal);

        if (refraction_ratio * std::sqrt(1.0 - cos_theta * cos_theta) > 1.0
            || reflectance(cos_theta, refraction_ratio) > random_double()) {
            scattered = ray(info.p, reflect(unit_direction, info.normal));
        } else {
            scattered = ray(info.p, refract(unit_direction, info.normal, refraction_ratio));
        }

        return true;
    }

private:
    double m_ir;

    static double reflectance(double cosine, double ref_idx) {
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0  + (1 - r0) * std::pow((1 - cosine), 5);
    }
};
