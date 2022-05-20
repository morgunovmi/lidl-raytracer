#include <fmt/format.h>
#include <fstream>

#include <random>

#include "camera.h"

#include "color.h"
#include "rt_header.h"
#include "objects/sphere.h"
#include "objects/hittable_list.h"

#include "materials/material.h"
#include "materials/lambertian.h"
#include "materials/metal.h"

slr::color ray_color(const ray& r, const hittable& world, int depth) {
    hit_info info{};

    if (depth <= 0) {
        return {0.0, 0.0, 0.0};
    }

    if (world.hit(r, 0.001, inf, info)) {
        ray scattered;
        slr::color attenuation;
        if (info.mat_ptr->scatter(r, info, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth - 1);
        }
        return slr::color{0, 0, 0};
    }

    auto unit_direction = r.direction().normalize();
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1 - t) * slr::color{1.0, 1.0, 1.0} + t * slr::color{0.5, 0.7, 1.0};
}

int main() {
    // Image

    const auto aspect_ratio = 16.0 / 9.0;

    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 500;
    const int max_depth = 50;

    // World

    hittable_list world{};

    const auto material_ground = std::make_shared<lambertian>(slr::color{0.8, 0.8, 0.0});
    const auto material_center = std::make_shared<lambertian>(slr::color{0.7, 0.3, 0.3});
    const auto material_left = std::make_shared<metal>(slr::color{0.8, 0.8, 0.8}, 0.3);
    const auto material_right = std::make_shared<metal>(slr::color{0.8, 0.6, 0.2}, 1.0);

    world.add(std::make_shared<sphere>(point3{0, -100.5, -1}, 100.0, material_ground));
    world.add(std::make_shared<sphere>(point3{0, 0, -1}, 0.5, material_center));
    world.add(std::make_shared<sphere>(point3{-1, 0, -1}, 0.5, material_left));
    world.add(std::make_shared<sphere>(point3{1, 0, -1}, 0.5, material_right));

    // camera
    camera cam{};

    // Render
    const std::string image_name{"image.ppm"};

    if (auto ofs = std::ofstream{ image_name }) {
        ofs << fmt::format("P3\n{} {}\n255\n", image_width, image_height);

        //TODO handle random properly
        std::random_device dre{};
        std::mt19937 gen{dre()};
        std::uniform_real_distribution<double> urd{0.0, 1.0};

        for (int y = image_height - 1; y >= 0; --y) {
            fmt::print("{} scanlines remaining\n", y);
            for (int x = 0; x < image_width; ++x) {
                slr::color pixel_color{0, 0, 0};
                for (int s = 0; s < samples_per_pixel; ++s) {
                    const auto u = (x + urd(gen)) / (image_width - 1);
                    const auto v = (y + urd(gen)) / (image_height - 1);
                    const auto r = cam.get_ray(u, v);
                    pixel_color += ray_color(r, world, max_depth);
                }
                write_color(ofs, pixel_color, samples_per_pixel);
            }
        }
    }
    fmt::print("\nDone.\n");

    return 0;
}
