mod color_helper;
mod ray;
mod objects;
mod camera;
mod util;

use std::fs::File;
use std::io::prelude::*;
use std::io::BufWriter;

use math::vector::{self, Vec3, Color, Point3};
use ray::Ray;
use objects::{Hittable, HitRecord, HittableList, Sphere};
use camera::Camera;
use util::random_f64;

fn ray_color<T: Hittable>(r: &Ray, world: &T, depth: i32) -> Color {
    let mut rec = HitRecord::new();

    if depth <= 0 {
        return Color::new(0.0, 0.0, 0.0);
    }

    if world.hit(r, 0.0, f64::INFINITY, &mut rec) {
        let target = rec.p + rec.normal + Vec3::random_in_unit_sphere(); 
        return 0.5 * ray_color(&Ray::new(&rec.p, &(target - rec.p)), world, depth - 1);
    }

    let unit_direction = vector::unit_vector(r.direction());
    let t = 0.5 * (unit_direction.y + 1.0);
    (1.0 - t) * Color::new(1.0, 1.0, 1.0) + t * Color::new(0.5, 0.7, 1.0)
}

fn main() -> std::io::Result<()> {
    // Image
    let aspect_ratio = 16.0 / 9.0;
    let image_width = 400;
    let image_height = (image_width as f64 / aspect_ratio) as i32;
    let samples_per_pixel = 100u32;
    let max_depth = 50;

    // world
    let mut world = HittableList::new(Sphere::new(Point3::new(0.0, 0.0, -1.0), 0.5));
    world.add(Sphere::new(Point3::new(0.0, -100.5, -1.0), 100.0));

    // Camera
    let cam = Camera::new();

    // Draw
    let image_file = File::create("image.ppm")?;
    let mut buf_writer = BufWriter::new(image_file);

    buf_writer.write_all(
        format!("P3\n{} {}\n255\n",
            image_width, image_height).as_bytes())?;

    for j in (0..image_height).rev() {
        println!("Scanlines remaining: {}", j);
        for i in 0..image_width {
            let mut pixel_color = Color::new(0.0, 0.0, 0.0);
            for _ in 0..samples_per_pixel {
                let u = (i as f64 + random_f64()) / (image_width - 1) as f64;
                let v = (j as f64 + random_f64()) / (image_height - 1) as f64;
                let r = cam.get_ray(u, v);
                pixel_color += ray_color(&r, &world, max_depth);
            }
            color_helper::write_color(&mut buf_writer, &pixel_color, samples_per_pixel)?;
        }
    }
    println!("Done.");

    Ok(())
}
