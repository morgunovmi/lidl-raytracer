#pragma once

#include <cmath>
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>

#include <random>
#include <cstdlib>

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

template <typename T>
T clip(const T& n, const T& lower, const T& upper);

template<class T>
struct Vec2 {
    T x, y;

    Vec2() : x(T()), y(T()) {}

    Vec2(T _x, T _y) : x(_x), y(_y) {}

    Vec2(const Vec2<T>& v) : x(v.x), y(v.y) {}

    Vec2<T>& operator=(const Vec2<T>& v) {
        x = v.x;
        y = v.y;
        return *this;
    }

    T operator[](std::size_t i) const {
        assert(i < 2);
        if (x == 0) return x; else return y;
    }

    T& operator[](std::size_t i) {
        assert(i < 2);
        if (x == 0) return x; else return y;
    }

    Vec2<T> operator+(const Vec2<T>& V) const { return Vec2<T>{x + V.x, y + V.y}; }
    Vec2<T> operator-(const Vec2<T>& V) const { return Vec2<T>{x - V.x, y - V.y}; }
    Vec2<T> operator*(float f) const { return Vec2<T>{static_cast<T>(x * f), static_cast<T>(y * f)}; }

    Vec2<T> operator-() const { return Vec2<T>{-x, -y}; }

    Vec2<T>& operator+=(const Vec2<T>& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vec2<T>& operator*=(const T f) {
        x *= f;
        y *= f;
    }

    Vec2<T>& operator/=(const T f) {
        assert(f != 0);
        return *this *= 1/f;
    }

    friend std::ostream& operator<<(std::ostream& s, Vec2<T>& v) {
        s << "(" << v.x << ", " << v.y << ")\n";
        return s;
    }
};

template<typename T>
Vec2<T> operator*(float f, Vec2<T> vec) { return Vec2<T>{static_cast<T>(vec.x * f), static_cast<T>(vec.y * f)}; }

template<class T>
struct Vec3 {
    T x, y, z;

    Vec3() : x(T()), y(T()), z(T()) {}

    Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

    template<class U>
    Vec3(const Vec3<U>& v);

    Vec3(const Vec3<T>& v) : x(v.x), y(v.y), z(v.z) {}

    Vec3<T>& operator=(const Vec3<T>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    T operator[](std::size_t i) const {
        assert(i < 3);
        if (i == 0) return x; else if (i == 1) return y; else return z;
    }

    T& operator[](std::size_t i) {
        assert(i < 3);
        if (i == 0) return x; else if (i == 1) return y; else return z;
    }

    inline Vec3<T> operator^(const Vec3<T>& v) const {
        return Vec3<T>{y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    inline Vec3<T> operator+(const Vec3<T>& v) const { return Vec3<T>{x + v.x, y + v.y, z + v.z}; }
    Vec3<T> operator-(const Vec3<T>& v) const { return Vec3<T>{x - v.x, y - v.y, z - v.z}; }

    Vec3<T> operator*(float f) const {
        return Vec3<T>{static_cast<T>(x * f), static_cast<T>(y * f), static_cast<T>(z * f)};
    }
    Vec3<T> operator/(float f) const {
        return Vec3<T>{static_cast<T>(x / f), static_cast<T>(y / f), static_cast<T>(z / f)};
    }

    Vec3<T> operator-() const { return Vec3<T>{-x, -y, -z}; }

    Vec3<T>& operator+=(const Vec3<T>& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3<T>& operator*=(const T f) {
        x *= f;
        y *= f;
        z *= f;
    }

    Vec3<T>& operator/=(const T f) {
        assert(f != 0);
        return *this *= 1/f;
    }

    inline Vec3<T> operator*(const Vec3<T>& v) const { return Vec3<T>{x * v.x , y * v.y , z * v.z}; }
    inline T dot(const Vec3<T>& v) const { return x * v.x + y * v.y + z * v.z; }

    [[nodiscard]] float norm() const { return std::sqrt(x * x + y * y + z * z); }

    [[nodiscard]] Vec3<T>& normalize(T l = 1) {
        *this = (*this) * l / std::sqrt(x * x + y * y + z * z);
        return *this;
    }

    inline friend std::ostream& operator<<(std::ostream& s, Vec3<T>& v) {
        s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
        return s;
    }

    inline static Vec3<T> random() {
        return Vec3<T>{random_double(), random_double(), random_double()};
    } 

    inline static Vec3<T> random(double min, double max) {
        return Vec3<T>{random_double(min, max),
            random_double(min, max),
            random_double(min, max)};
    } 

    bool near_zero() const {
        const auto eps = 1e-8;
        return (fabs(x) < eps) && (fabs(y) < eps) && (fabs(z) < eps);
    }
};


template<typename T>
Vec3<T> operator*(double f, Vec3<T> vec) {
    return Vec3<T>{static_cast<T>(vec.x * f), static_cast<T>(vec.y * f), static_cast<T>(vec.z * f)};
}

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;
using Vec3f = Vec3<float>;
using Vec3i = Vec3<int>;
using Vec3d = Vec3<double>;

using point3 = Vec3d;
using color = Vec3d;

template<>
template<>
Vec3<int>::Vec3(const Vec3<float>& v);

template<>
template<>
Vec3<float>::Vec3(const Vec3<int>& v);

inline Vec3d random_in_unit_sphere() {
    while (true) {
        const auto p = Vec3d::random(-1, 1);
        if (p.norm() >= 1) continue;
        return p;
    }
}

inline Vec3d random_unit_vector() {
    return random_in_unit_sphere().normalize();
}

template<typename T>
inline Vec3<T> reflect(const Vec3<T>& v, const Vec3<T>& n) {
    return v - 2 * n.dot(v) * n;
}

template<typename T>
inline Vec3<T> refract(const Vec3<T>& i, const Vec3<T>& n, double n1_over_n2) {
    const auto n_dot_i = i.dot(n);
    const auto t_perp = n1_over_n2 * (i - n_dot_i * n);
    const auto t_parralel = -std::sqrt(1 - n1_over_n2 * n1_over_n2 * (1 - n_dot_i * n_dot_i)) * n;
    return t_parralel + t_perp;
}

///////////////////

const int DEFAULT_SIZE = 4;

class Matrix {

public:
    [[nodiscard]] inline std::size_t nrows() const { return mMatrix.size(); }

    [[nodiscard]] inline std::size_t ncols() const { return mMatrix[0].size(); }

    Matrix operator*(const Matrix& m) const;

    static Matrix eye(std::size_t size);

    Matrix transpose();

    friend std::ostream& operator<<(std::ostream& s, const Matrix& m);

    std::vector<float>& operator[](std::size_t i);

    explicit Matrix(std::size_t row = DEFAULT_SIZE, std::size_t col = DEFAULT_SIZE);

    ~Matrix() = default;

private:
    std::size_t mCols;
    std::size_t mRows;
    std::vector<std::vector<float>> mMatrix;
};
