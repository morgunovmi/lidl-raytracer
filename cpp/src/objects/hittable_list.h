#pragma once

#include <memory>
#include <vector>

#include "hittable.h"

class hittable_list : public hittable {
public:
    hittable_list() = default;
    hittable_list(std::shared_ptr<hittable> object) { add(object); }

    void clear() { m_objects.clear(); }
    void add(std::shared_ptr<hittable> object) { m_objects.push_back(object); }

    virtual bool hit(
        const ray& r, double t_min, double t_max, hit_info& info
    ) const override;

private:
    std::vector<std::shared_ptr<hittable>> m_objects;
};

inline bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_info &info) const {
    hit_info temp_info;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto & object : m_objects) {
        if (object->hit(r, t_min, closest_so_far, temp_info)) {
            hit_anything = true;
            closest_so_far = temp_info.t;
            info = temp_info;
        }
    }

    return hit_anything;
}
