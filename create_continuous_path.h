#pragma once

#include <cmath>
#include <iostream>
#include <optional>
#include <vector>
namespace wangzheng {

class Point {
  public:
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
  double Distance(const Point& p) const {
    return std::hypot(x - p.x, y - p.y);
  }
};

template <typename PointT>
struct Line {
  PointT p1, p2;
  Line(const PointT& p1, const PointT& p2) : p1(p1), p2(p2) {}
};

template <typename PointT>
static std::optional<PointT> CheckIntersection(const Line<PointT>& l1, const Line<PointT>& l2) {
  if (l1.p2.Distance(l2.p1) < 1e-6 || l1.p1.Distance(l2.p2) < 1e-6) {
    return std::nullopt;
  }
  PointT a = l1.p1, b = l1.p2, c = l2.p1, d = l2.p2;
  // Line AB represented as a1x + b1y = c1
  double a1 = b.y - a.y;
  double b1 = a.x - b.x;
  double c1 = a1 * (a.x) + b1 * (a.y);
  // Line CD represented as a2x + b2y = c2
  double a2 = d.y - c.y;
  double b2 = c.x - d.x;
  double c2 = a2 * (c.x) + b2 * (c.y);

  double det = a1 * b2 - a2 * b1;

  if (std::abs(det) < 1e-6) {        // Lines are parallel or coincident
    if (std::abs(c1 - c2) < 1e-6) {  // Lines are coincident
      return c;
    } else {
      return std::nullopt;
    }
  } else {
    double x = (b2 * c1 - b1 * c2) / det;
    double y = (a1 * c2 - a2 * c1) / det;
    // Check if the intersection point lies within both line segments
    if ((x >= std::min(a.x, b.x) && x <= std::max(a.x, b.x)) &&
        (y >= std::min(a.y, b.y) && y <= std::max(a.y, b.y)) &&
        (x >= std::min(c.x, d.x) && x <= std::max(c.x, d.x)) &&
        (y >= std::min(c.y, d.y) && y <= std::max(c.y, d.y))) {
      return PointT(x, y);
    } else {
      return std::nullopt;
    }
  }
}

template <typename PointT>
static void UpdatePointSet(std::vector<PointT>& points, const PointT& p) {
  if (points.size() <= 1) {
    points.push_back(p);
    return;
  }

  Line cur_line(points.back(), p);
  std::cout << "cur_line:" << cur_line.p1.x << "," << cur_line.p1.y << " "
            << cur_line.p2.x << "," << cur_line.p2.y << std::endl;
  for (size_t i = 0; i < points.size() - 1; ++i) {
    Line line(points[i], points[i + 1]);
    std::cout << "line:" << line.p1.x << "," << line.p1.y << " " << line.p2.x
              << "," << line.p2.y << std::endl;
    auto intersection = CheckIntersection<PointT>(line, cur_line);
    std::cout << "intersection:" << intersection.has_value() << std::endl;
    if (intersection.has_value()) {
      std::cout << "intersection:" << intersection.value().x << ","
                << intersection.value().y << std::endl;
      // remove all points after i and add the intersection and p2
      points.erase(points.begin() + i + 1, points.end());
      points.push_back(intersection.value());
      points.push_back(p);
      return;
    }
  }
  // No intersection found, add p
  points.push_back(p);
}

template <typename PointT>
inline std::vector<PointT> CreateContinuousPath(
    const std::vector<PointT>& points) {
  if (points.size() <= 2) {
    return points;
  }

  std::vector<PointT> input_points = {points.front()};
  for (size_t i = 1; i < points.size(); ++i) {
    if (points[i-1].Distance(points[i]) < 1e-6) {
      continue;
    }
    input_points.push_back(points[i]);
    std::cout << points[i].x << "|" << points[i].y << std::endl;
  }

  std::vector<PointT> res;
  for (size_t i = 0; i < input_points.size(); ++i) {
    UpdatePointSet<PointT>(res, input_points[i]);
  }

  for (const auto& pt : res) {
    std::cout << pt.x << "," << pt.y << std::endl;
  }
  return res;
}
}  // namespace wangzheng
