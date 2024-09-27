#ifndef __worker_HPP__
#define __worker_HPP__

#include "../parser/parser.hpp"

using namespace std;

class Worker {
 public:
  Worker() : figure(Figure::get_instance()) {}

  bool parse_file(const string& file_path) {
    Parser parser;
    bool res = false;
    res = parser.parse_file_to_figure(file_path);
    figure.align_to_center();
    return res;
  }

  tuple<const double*, size_t> get_vertex_array() {
    return figure.get_vertex();
  }

  tuple<const Polygon*, size_t> get_polygon_array() {
    return figure.get_polygon();
  }

  // pass 1.1 or 0.99
  void scale(double scale_coef) { figure.scale_figure(scale_coef); }

  void move_figure(double x_factor, double y_factor, double z_factor) {
    figure.move_figure(x_factor, y_factor, z_factor);
  }

  void rotate_figure(double x_angle, double y_angle, double z_angle) {
    figure.rotate_figure(x_angle, y_angle, z_angle);
  }

  size_t get_n_vertices() const { return figure.get_n_vertex(); }
  size_t get_n_polygons() const { return figure.get_n_polygons(); }
  size_t get_n_polygons_edges() const { return figure.get_n_polygons_edges(); }
  double get_x_max() const { return figure.get_x_max_(); }
  double get_y_max() const { return figure.get_y_max_(); }
  double get_z_max() const { return figure.get_z_max_(); }
  double get_x_min() const { return figure.get_x_min_(); }
  double get_y_min() const { return figure.get_y_min_(); }
  double get_z_min() const { return figure.get_z_min_(); }

 private:
  Figure& figure;
};

#endif