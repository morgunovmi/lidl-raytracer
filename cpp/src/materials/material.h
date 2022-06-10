#pragma once

#include "rt_header.h"

struct hit_info;

class material {
public:
    virtual bool scatter(
        const ray& r_in, const hit_info& info, color& attenuation, ray& scattered
    ) const { return true; }

    virtual ~material() = default;
};
