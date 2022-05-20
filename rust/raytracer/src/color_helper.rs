use std::fs::File;
use std::io::BufWriter;
use std::io::prelude::*;

use math::vector::Color;

pub fn write_color(writer: &mut BufWriter<File>, pixel_color: &Color) -> std::io::Result<()> {
    (*writer).write_all(
        format!("{} {} {}\n",
            (255.999 * pixel_color.x) as i32,
            (255.999 * pixel_color.y) as i32,
            (255.999 * pixel_color.z) as i32).as_bytes()
    )?;

    Ok(())
}
