use std::ops;
use std::fmt;

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Vec3 {
    pub x: f64,
    pub y: f64,
    pub z: f64,
}

impl Vec3 {
    pub fn new(x: f64, y: f64, z: f64) -> Vec3 {
        Vec3 {
            x, y, z
        }
    }

    pub fn length_squared(&self) -> f64 {
        self.x * self.x 
        + self.y * self.y 
        + self.z * self.z 
    }

    pub fn length(&self) -> f64 {
        Self::length_squared(&self).sqrt()
    }
}

impl ops::Neg for Vec3 {
    type Output = Self;

    fn neg(self) -> Self::Output {
        Vec3::new(-self.x, -self.y, -self.z)
    }
}

impl ops::AddAssign for Vec3 {
    fn add_assign(&mut self, rhs: Self) {
        self.x += rhs.x;
        self.y += rhs.y;
        self.z += rhs.z;
    }
}

impl ops::MulAssign<f64> for Vec3 {
    fn mul_assign(&mut self, rhs: f64) {
        self.x *= rhs;
        self.y *= rhs;
        self.z *= rhs;
    }
}

impl ops::DivAssign<f64> for Vec3 {
    fn div_assign(&mut self, rhs: f64) {
        *self = *self / rhs;
    }
}

pub use Vec3 as Point3;
pub use Vec3 as Color;

//Utility
impl fmt::Display for Vec3 {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "({}, {}, {})", self.x, self.y, self.z)
    }
}

impl ops::Add for Vec3 {
    type Output = Vec3;

    fn add(self, rhs: Vec3) -> Vec3 {
        Vec3::new(
            self.x + rhs.x,
            self.y + rhs.y,
            self.z + rhs.z,
        )
    }
}

impl ops::Sub for Vec3 {
    type Output = Vec3;

    fn sub(self, rhs: Vec3) -> Vec3 {
        Vec3::new (
            self.x - rhs.x,
            self.y - rhs.y,
            self.z - rhs.z,
        )
    }
}

impl ops::Mul for Vec3 {
    type Output = Vec3;

    fn mul(self, rhs: Vec3) -> Vec3 {
        Vec3::new(
            self.x * rhs.x,
            self.y * rhs.y,
            self.z * rhs.z,
        )
    }
}

impl ops::Mul<f64> for Vec3 {
    type Output = Vec3;

    fn mul(self, rhs: f64) -> Vec3 {
        Vec3::new (
                self.x * rhs,
                self.y * rhs,
                self.z * rhs,
        )
    }
}

impl ops::Mul<Vec3> for f64 {
    type Output = Vec3;

    fn mul(self, rhs: Vec3) -> Vec3 {
        Vec3::new (
                rhs.x * self,
                rhs.y * self,
                rhs.z * self,
        )
    }
} 

impl ops::Div<f64> for Vec3 {
    type Output = Vec3;

    fn div(self, rhs: f64) -> Vec3 {
        self * (1.0 / rhs)
    }
}

pub fn dot(u: &Vec3, v: &Vec3) -> f64 {
    u.x * v.x
    + u.y * v.y
    + u.z * v.z
}

pub fn cross(u: &Vec3, v: &Vec3) -> Vec3 {
    Vec3::new (
            u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x,
    )
}

pub fn unit_vector(v: &Vec3) -> Vec3 {
    *v / v.length()
}
