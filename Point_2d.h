#ifndef POINT_2D_H
#define POINT_2D_H

#include <string>

class Point_2d;

struct X_order {
    bool operator<(Point_2d& lhs, Point_2d& rhs);
};

struct Y_order {
    bool operator<(Point_2d& lhs, Point_2d& rhs);
};

struct R_order {
    bool operator<(Point_2d& lhs, Point_2d& rhs);
};

class Atan_2_order {
public:
    inline explicit Atan_2_order(const Point_2d c) : _comparison_point{c} {}

    bool operator<(Point_2d& lhs, Point_2d& rhs);

private:
    const Point_2d _comparison_point;
};

class Polar_order {
public:
    inline explicit Polar_order(const Point_2d c) : _comparison_point{c} {}

    bool operator<(Point_2d& lhs, Point_2d& rhs);

private:
    const Point_2d _comparison_point;
};

class Distance_to_order {
public:
    inline explicit Distance_to_order(const Point_2d c) : _comparison_point{c} {}

    bool operator<(Point_2d& lhs, Point_2d& rhs);

private:
    const Point_2d _comparison_point;
};

class Point_2d {
public:
    const static X_order x_order = X_order{};
    const static Y_order y_order = Y_order{};
    const static R_order r_order = R_order{};

    Point_2d() = default;

    Point_2d(const Point_2d&) = default;

    Point_2d(Point_2d&&) = default;

    ~Point_2d() = default;

    Point_2d& operator=(const Point_2d&) = default;

    Point_2d& operator=(Point_2d&&) = default;

    Point_2d(double c, double y);

    inline double x() const noexcept { return _x; }

    inline double y() const noexcept { return _y; }

    inline double r() const { return std::sqrt(_x * _x + _y * _y); }

    inline double theta() const { return std::atan2(_y, _x); }

    double angle_to(Point_2d& that) const;

    static int ccw(Point_2d& a, Point_2d& b, Point_2d& c);

    static int ccw(Point_2d&& a, Point_2d& b, Point_2d& c);

    static double area2(Point_2d& a, Point_2d& b, Point_2d& c);

    double distance_to(Point_2d& rhs) const;

    double distance_squared_to(Point_2d& rhs) const;

    bool operator<(Point_2d& rhs);

    inline bool operator==(Point_2d& rhs) { return _x == rhs._x && _y == rhs._y; }

    inline bool operator!=(Point_2d& rhs) { return !(*this == rhs); }

    std::string to_string();

    std::size_t hash_code();

    void draw();

    void draw_to(Point_2d& rhs);

    inline static Polar_order polar_order() const { return Polar_order{*this}; }

    inline static Atan_2_order atan_2_order() const { return Atan_2_order{*this}; }

    inline static Distance_to_order distance_to_order() const { return Distance_to_order{*this}; }

private:
    const double _x;
    const double _y;

    friend class X_order;

    friend class Y_order;

    friend class R_order;

    friend class Atan_2_order;

    friend class Polar_order;

    friend class Distance_to_order;
};

std::ostream& operator<<(std::ostream& os, Point_2d& out);

#endif // POINT_2D_H
