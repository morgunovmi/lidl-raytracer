use std::fs::File;
use std::io::BufWriter;
use std::io::prelude::*;
use num;

use math::vector::Color;

pub fn write_color(writer: &mut BufWriter<File>, pixel_color: &Color, samples_per_pixel: u32) -> std::io::Result<()> {
    let mut r = pixel_color.x;
    let mut g = pixel_color.y;
    let mut b = pixel_color.z;

    let scale = 1.0 / samples_per_pixel as f64;
    r *= scale;
    g *= scale;
    b *= scale;

    (*writer).write_all(
        format!("{} {} {}\n",
            (256.0 * num::clamp(r, 0.0, 0.999)) as i32,
            (256.0 * num::clamp(g, 0.0, 0.999)) as i32,
            (256.0 * num::clamp(b, 0.0, 0.999)) as i32).as_bytes()
    )?;

    Ok(())
}
