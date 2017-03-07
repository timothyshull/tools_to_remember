#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H

#include <deque>
#include <vector>
#include <cassert>

#include "Point_2d.h"

class Graham_scan {
private:
    std::deque<Point_2d> _hull; // stack

public:
    Graham_scan(std::vector<Point_2d> points) // copy in
    {
        if (points.empty()) { throw std::invalid_argument("points vector is empty"); }

        std::sort(points.begin(), points.end());
        std::sort(points.begin(), points.end(), Point_2d::polar_order());
        _hull.push_back(points[0]);

        auto n = points.size();

        int k1;
        for (k1 = 1; k1 < n; ++k1) { if (points[0] != points[k1]) { break; }}
        if (k1 == n) { return; }

        int k2;
        for (k2 = k1 + 1; k2 < n; ++k2) { if (Point_2d::ccw(points[0], points[k1], points[k2]) != 0) { break; }}
        _hull.push_back(points[k2 - 1]);

        for (auto i = k2; i < n; i++) {
            auto top = _hull.back();

            while (Point_2d::ccw(_hull.back(), top, points[i]) <= 0) {
                top = _hull.back();
                _hull.pop_back();
            }
            _hull.push_back(top);
            _hull.push_back(points[i]);
        }

        assert(_is_convex());
    }

    std::vector<Point_2d> hull()
    {
        return {_hull.rbegin(), _hull.rend()};
//        Stack <Point_2d> s = new Stack<Point_2d>();
//        for (Point_2d p : _hull) { s.push(p); }
//        return s;
    }

private:
    bool _is_convex()
    {
        auto n = _hull.size();
        if (n <= 2) { return true; }
        std::vector<Point_2d> points(n);
        auto k = 0;
        for (auto p : hull()) { points[k++] = p; }
        for (auto i = 0; i < n; ++i) {
            if (Point_2d::ccw(points[i], points[(i + 1) % n], points[(i + 2) % n]) <= 0) { return false; }
        }
        return true;
    }
};

#endif // GRAHAM_SCAN_H
