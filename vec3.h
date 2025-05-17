#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <ostream>
class Vec3 {
public:
  Vec3() = default;
  Vec3(double x, double y, double z) : x_(x), y_(y), z_(z) {}

  auto x() const -> double { return x_; }
  auto y() const -> double { return y_; }
  auto z() const -> double { return z_; }

  auto operator+=(const Vec3 &other) -> Vec3 & {
    x_ += other.x_;
    y_ += other.y_;
    z_ += other.z_;
    return *this;
  }

  auto operator-=(const Vec3 &other) -> Vec3 & {
    x_ -= other.x_;
    y_ -= other.y_;
    z_ -= other.z_;
    return *this;
  }

  auto operator-() const -> Vec3 { return Vec3(-x_, -y_, -z_); }

  auto operator*=(const double t) -> Vec3 & {
    x_ *= t;
    y_ *= t;
    z_ *= t;
    return *this;
  }

  auto operator/=(const double t) -> Vec3 & {
    x_ /= t;
    y_ /= t;
    z_ /= t;
    return *this;
  }

  auto length() -> double { return std::sqrt(lengthSquared()); }

  auto lengthSquared() -> double { return x_ * x_ + y_ * y_ + z_ * z_; }

  auto toUnitVector() -> Vec3 {
    Vec3 res(*this);
    return res /= length();
  }

  friend std::ostream &operator<<(std::ostream &os, const Vec3 &vec);

private:
  double x_{0}, y_{0}, z_{0};
};

inline std::ostream &operator<<(std::ostream &os, const Vec3 &vec) {
  os << vec.x_ << ' ' << vec.y_ << ' ' << vec.z_;
  return os;
}

inline auto operator+(const Vec3 &vec1, const Vec3 &vec2) -> Vec3 {
  Vec3 res(vec1);
  res += vec2;
  return res;
}

inline auto operator-(const Vec3 &vec1, const Vec3 &vec2) -> Vec3 {
  Vec3 res(vec1);
  res -= vec2;
  return res;
}

inline auto operator*(const Vec3 &vec, double t) -> Vec3 {
  Vec3 res(vec);
  res *= t;
  return res;
}

inline auto operator*(double t, const Vec3 &vec) -> Vec3 {
  Vec3 res(vec);
  res *= t;
  return res;
}

inline auto operator/(const Vec3 &vec, double t) -> Vec3 {
  Vec3 res(vec);
  res /= t;
  return res;
}

inline auto dot(const Vec3 &a, const Vec3 &b) -> double {
  return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

using Point3 = Vec3;

#endif