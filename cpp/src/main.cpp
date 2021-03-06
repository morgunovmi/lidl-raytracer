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
#include "materials/dielectric.h"

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_info info{};

    if (depth <= 0) {
        return {0.0, 0.0, 0.0};
    }

    if (world.hit(r, 0.001, inf, info)) {
        ray scattered;
        color attenuation;
        if (info.mat_ptr->scatter(r, info, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth - 1);
        }
        return color{0, 0, 0};
    }

    auto unit_direction = r.direction().normalize();
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1 - t) * color{1.0, 1.0, 1.0} + t * color{0.5, 0.7, 1.0};
}

hittable_list random_scene() {
    hittable_list world{};

    const auto ground_material = std::make_shared<lambertian>(color{0.5, 0.5, 0.5});
    world.add(std::make_shared<sphere>(point3{0, -1000, 0}, 1000, ground_material));

    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            const auto choose_mat = random_double();
            point3 center{a + 0.9 * random_double(), 0.2, b + 0.9 * random_double()};

            if ((center - point3{4, 0.2, 0}).norm() > 0.9) {
                std::shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    const auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    const auto albedo = color::random(0.5, 1);
                    const auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    const auto n = random_double(1.1, 1.9);
                    sphere_material = std::make_shared<dielectric>(n);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    const auto material1 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(point3{0, 1, 0}, 1.0, material1));

    const auto material2 = std::make_shared<lambertian>(color{0.4, 0.2, 0.1});
    world.add(std::make_shared<sphere>(point3{-4, 1, 0}, 1.0, material2));

    const auto material3 = std::make_shared<metal>(color{0.7, 0.6, 0.5}, 0.0);
    world.add(std::make_shared<sphere>(point3{4, 1, 0}, 1.0, material3));

    return world;
}

int main() {
    // Image

    const auto aspect_ratio = 16.0 / 9.0;

    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 500;
    const int max_depth = 50;

    // World

    //hittable_list world{};
    const auto world = random_scene();

    /*
    const auto material_ground = std::make_shared<lambertian>(color{0.8, 0.8, 0.0});
    const auto material_left = std::make_shared<dielectric>(1.5);
    const auto material_center = std::make_shared<lambertian>(color{0.1, 0.1, 0.8});
    const auto material_right = std::make_shared<metal>(color{0.8, 0.6, 0.2}, 0.0);

    world.add(std::make_shared<sphere>(point3{0, -100.5, -1}, 100.0, material_ground));
    world.add(std::make_shared<sphere>(point3{-1, 0, -1}, 0.5, material_left));
    world.add(std::make_shared<sphere>(point3{-1, 0, -1}, -0.48, material_left));
    world.add(std::make_shared<sphere>(point3{-1, 0, -3}, 0.5, material_center));
    world.add(std::make_shared<sphere>(point3{0, 0, -1}, 0.5, material_center));
    world.add(std::make_shared<sphere>(point3{1, 0, -1}, 0.5, material_right));
    */

    point3 lookfrom{13, 2, 3};
    point3 lookat{0, 0, 0};
    Vec3d vup{0, 1, 0};
    //const auto dist_to_focus = (lookfrom - lookat).norm();
    const auto dist_to_focus = 10.0;
    const auto aperture = 0.1;

    // camera
    camera cam{lookfrom, lookat, vup, 20.0, aspect_ratio, aperture, dist_to_focus};

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
                color pixel_color{0, 0, 0};
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
