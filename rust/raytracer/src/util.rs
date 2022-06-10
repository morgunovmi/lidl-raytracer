use rand::Rng;

pub const PI: f64 = std::f64::consts::PI;

pub fn deg_to_rad(deg: f64) -> f64 {
    deg * PI / 180.0
}

pub fn rad_to_deg(rad: f64) -> f64 {
    180.0 * rad / PI
}

// 0..1
pub fn random_f64() -> f64 {
    rand::thread_rng().gen_range(0.0..1.0)
}

// a..b 
pub fn random_f64_range(min: f64, max: f64) -> f64 {
    rand::thread_rng().gen_range(min..max)
}
