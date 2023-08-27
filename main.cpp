#include <matplot/matplot.h>

#include <vector>

#include "create_continuous_path.h"

class MyPoint : public wangzheng::Point {
 public:
  MyPoint(double x, double y) : wangzheng::Point(x, y) {}
};

int main() {
  std::vector<MyPoint> points;
  points.emplace_back(0, 0);
  points.emplace_back(2, 0);

  points.emplace_back(1, -1);
  points.emplace_back(1, 0.5);

  points.emplace_back(1, 0.5);
  points.emplace_back(2, 1);

  points.emplace_back(2, 1);
  points.emplace_back(0, 2);

  points.emplace_back(2, 1.5);
  points.emplace_back(0, 1.5);

  points.emplace_back(1, 2);
  points.emplace_back(0, 1);

  points.emplace_back(0, 1);
  points.emplace_back(0, 0);

  auto res = wangzheng::CreateContinuousPath(points);
  std::cout << "res.size():" << res.size() << std::endl;

  // visualize
  matplot::figure(1);
  matplot::hold(matplot::on);
  auto plot_points = [&](const std::vector<MyPoint>& points,
                         std::string_view line_spec) {
    for (size_t i = 0; i < points.size() - 1; i++) {
      std::vector<double> x = {points[i].x, points[i + 1].x};
      std::vector<double> y = {points[i].y, points[i + 1].y};
      matplot::plot(x, y, line_spec);
    }
  };
  plot_points(points, "r-o");
  plot_points(res, "b-o");

  matplot::axis({-1, 2, -1, 2});
  matplot::xlabel("X");
  matplot::ylabel("Y");
  matplot::hold(matplot::off);
  matplot::show();
  return 0;
}
