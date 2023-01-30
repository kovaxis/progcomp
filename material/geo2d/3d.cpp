#include "../common.h"

typedef double T;

struct Vec3 {
    T x;
    T y;
    T z;

    Vec3(T x_, T y_, T z_) : x{x_}, y{y_}, z{z_} {}
    Vec3() : x{0}, y{0}, z{0} {}

    friend ostream& operator<<(ostream& out, const Vec3& self) {
        out << "(" << self.x << ", " << self.y << ", " << self.x << ")";
        return out;
    }
    friend istream& operator>>(istream& in, Vec3& self) {
        in >> self.x;
        in >> self.y;
        in >> self.z;
        return in;
    }

    Vec3& operator+=(const Vec3& r) {
        this->x += r.x;
        this->y += r.y;
        this->z += r.z;
        return *this;
    }
    friend Vec3 operator+(Vec3 l, const Vec3& r) {
        return {l.x + r.x, l.y + r.y, l.z + r.z};
    }

    Vec3& operator-=(const Vec3& r) {
        this->x -= r.x;
        this->y -= r.y;
        this->z -= r.z;
        return *this;
    }
    friend Vec3 operator-(Vec3 l, const Vec3& r) {
        return {l.x - r.x, l.y - r.y, l.z - r.z};
    }
    Vec3 operator-() { return {-this->x, -this->y, -this->z}; }

    Vec3& operator*=(const T& r) {
        this->x *= r;
        this->y *= r;
        this->z *= r;
        return *this;
    }
    friend Vec3 operator*(Vec3 l, const T& r) {
        return {l.x * r, l.y * r, l.z * r};
    }
    friend Vec3 operator*(const T& l, Vec3 r) {
        return {l * r.x, l * r.y, l * r.z};
    }

    Vec3& operator/=(const T& r) {
        this->x /= r;
        this->y /= r;
        this->z /= r;
        return *this;
    }
    friend Vec3 operator/(Vec3 l, const T& r) {
        return {l.x / r, l.y / r, l.z / r};
    }

    // Dot product
    friend T operator*(Vec3 l, const Vec3& r) {
        return l.x * r.x + l.y * r.y + l.z * r.z;
    }

    // Cross product
    friend Vec3 operator^(Vec3 l, const Vec3& r) {
        return {l.y * r.z - r.y * l.z, l.x * r.z - r.x * l.z,
                l.x * r.y - r.x * l.y};
    }

    T magsq() {
        return this->x * this->x + this->y * this->y + this->z * this->z;
    }
    T mag() { return sqrt(this->magsq()); }
    Vec2 unit() { return (1. / this->mag()) * (*this); }
};

#ifndef NOMAIN_3D

int main() {}

#endif