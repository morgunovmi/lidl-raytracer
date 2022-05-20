mod color_helper;
mod ray;

use std::fs::File;
use std::io::prelude::*;
use std::io::BufWriter;

use math::vector::{self, Vec3, Color, Point3};
use ray::Ray;

fn hit_sphere(center: &Point3, radius: f64, r: &Ray) -> f64 {
    let oc = *r.origin() - *center;
    let a = r.direction().length_squared();
    let half_b = vector::dot(&oc, r.direction());
    let c = oc.length_squared() - radius * radius;
    let discr = half_b * half_b - a * c;
    if discr < 0.0 {
        return -1.0;
    } else {
        return (-half_b - discr.sqrt()) / a;
    }
}

fn ray_color(r: &ray::Ray) -> Color {
    let t = hit_sphere(&Point3::new(0.0, 0.0, -1.0), 0.5, r);
    if t > 0.0 {
        let N = vector::unit_vector(&(r.at(t) - Vec3::new(0.0, 0.0, -1.0)));
        return 0.5 * Color::new(N.x + 1.0, N.y + 1.0, N.z + 1.0);
    }
    let unit_direction = vector::unit_vector(r.direction());
    let t = 0.5 * (unit_direction.y + 1.0);
    (1.0 - t) * Color::new(1.0, 1.0, 1.0) + t * Color::new(0.5, 0.7, 1.0)
}

fn main() -> std::io::Result<()> {
    // Image
    let aspect_ratio = 16.0 / 9.0;
    let image_width = 1000;
    let image_height = (image_width as f64 / aspect_ratio) as i32;

    // Camera

    let viewport_height = 2.0;
    let viewport_width = aspect_ratio * viewport_height;
    let focal_length = 1.0;

    let origin = Point3::new(0.0, 0.0, 0.0);
    let horizontal = Vec3::new(viewport_width, 0.0, 0.0);
    let vertical = Vec3::new(0.0, viewport_height, 0.0);
    let lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - Vec3::new(0.0, 0.0, focal_length);

    let image_file = File::create("image.ppm")?;
    let mut buf_writer = BufWriter::new(image_file);

    buf_writer.write_all(
        format!("P3\n{} {}\n255\n",
            image_width, image_height).as_bytes())?;

    for j in (0..image_height).rev() {
        println!("Scanlines remaining: {}", j);
        for i in 0..image_width {
            let u = i as f64 / (image_width - 1) as f64;
            let v = j as f64 / (image_height - 1) as f64;
            let r = Ray::new(&origin, &(lower_left_corner + u * horizontal + v * vertical - origin));
            let pixel_color = ray_color(&r);

            color_helper::write_color(&mut buf_writer, &pixel_color)?;
        }
    }
    println!("Done.");

    Ok(())
}