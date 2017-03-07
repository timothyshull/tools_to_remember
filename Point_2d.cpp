#include <cmath>
#include <sstream>

#include "Point_2d.h"
#include "Std_draw.h"

bool X_order::operator<(Point_2d& lhs, Point_2d& rhs)
{
    return lhs._x < rhs._x;
}

bool Y_order::operator<(Point_2d& lhs, Point_2d& rhs)
{
    return lhs._y < rhs._y;
}

bool R_order::operator<(Point_2d& lhs, Point_2d& rhs)
{
    double delta{(lhs._x * lhs._x + lhs._y * lhs._y) - (rhs._x * rhs._x + rhs._y * rhs._y)};
    return delta < 0;
}

bool Atan_2_order::operator<(Point_2d& lhs, Point_2d& rhs)
{
    double angle1{_comparison_point.angle_to(lhs)};
    double angle2{_comparison_point.angle_to(rhs)};
    return angle1 < angle2;
}

int Polar_order::operator<(Point_2d& lhs, Point_2d& rhs)
{
    double dx1{lhs._x - _comparison_point._x};
    double dy1{lhs._y - _comparison_point._y};
    double dx2{rhs._x - _comparison_point._x};
    double dy2{rhs._y - _comparison_point._y};

    if (dy1 >= 0 && dy2 < 0) { return -1; }
    else if (dy2 >= 0 && dy1 < 0) { return +1; }
    else if (dy1 == 0 && dy2 == 0) {
        if (dx1 >= 0 && dx2 < 0) { return -1; }
        else if (dx2 >= 0 && dx1 < 0) { return +1; }
        else { return 0; }
    } else {
        Point_2d tmp{_comparison_point};
        return -Point_2d::ccw(tmp, lhs, rhs);
    }
}

bool Distance_to_order::operator<(Point_2d& lhs, Point_2d& rhs)
{
    double dist1{_comparison_point.distance_squared_to(lhs)};
    double dist2{_comparison_point.distance_squared_to(rhs)};
    return dist1 < dist2;
}

Point_2d::Point_2d(double x, double y) : _x{x == 0.0 ? 0.0 : x}, _y{y == 0.0 ? 0.0 : y}
{
    if (std::isinf(_x) || std::isinf(y)) {
        throw utility::Illegal_argument_exception{"Coordinates must be finite"};
    }
    if (std::isnan(_x) || std::isnan(y)) {
        throw utility::Illegal_argument_exception{"Coordinates cannot be NaN"};
    }
}

double Point_2d::angle_to(Point_2d& rhs) const
{
    double dx{rhs._x - _x};
    double dy{rhs._y - _y};
    return std::atan2(dy, dx);
}

int Point_2d::ccw(Point_2d& a, Point_2d& b, Point_2d& c)
{
    double area2{(b._x - a._x) * (c._y - a._y) - (b._y - a._y) * (c._x - a._x)};
    if (area2 < 0) { return -1; }
    else if (area2 > 0) { return +1; }
    else { return 0; }
}

int Point_2d::ccw(Point_2d&& a, Point_2d& b, Point_2d& c)
{
    double area2{(b._x - a._x) * (c._y - a._y) - (b._y - a._y) * (c._x - a._x)};
    if (area2 < 0) { return -1; }
    else if (area2 > 0) { return +1; }
    else { return 0; }
}

double Point_2d::area2(Point_2d& a, Point_2d& b, Point_2d& c)
{
    return (b._x - a._x) * (c._y - a._y) - (b._y - a._y) * (c._x - a._x);
}

double Point_2d::distance_to(Point_2d& rhs) const
{
    double dx{_x - rhs._x};
    double dy{_y - rhs._y};
    return std::sqrt(dx * dx + dy * dy);
}

double Point_2d::distance_squared_to(Point_2d& rhs) const
{
    double dx{_x - rhs._x};
    double dy{_y - rhs._y};
    return dx * dx + dy * dy;
}

bool Point_2d::operator<(Point_2d& rhs)
{
    if (_y < rhs._y) { return -1; }
    if (_y > rhs._y) { return +1; }
    if (_x < rhs._x) { return -1; }
    if (_x > rhs._x) { return +1; }
    return 0;
}

std::string Point_2d::to_string()
{
    std::stringstream ss;
    ss << "Point_2d(x: " << _x << ", y: " << _y << ")";
    return ss.str();
}

std::size_t Point_2d::hash_code()
{
    std::size_t hash_x{std::hash<double>{}(_x)};
    std::size_t hash_y{std::hash<double>{}(_y)};
    return 31 * hash_x + hash_y;
}

void Point_2d::draw()
{
    Std_draw::point(_x, _y);
}

void Point_2d::draw_to(Point_2d& rhs)
{
    Std_draw::line(_x, _y, rhs._x, rhs._y);
}

std::ostream& operator<<(std::ostream& os, Point_2d& out)
{
    return os << out.to_string();
}
