#ifndef __worker_HPP__
#define __worker_HPP__

#include "../parser/parser.hpp"

namespace s21 {
class Worker {
 public:
  Worker();

  bool parse_file(const string& file_path);

  tuple<const double*, size_t> get_vertex_array();

  tuple<const Polygon*, size_t> get_polygon_array();

  void scale(double scale_coef);
  void move_figure(double x_factor, double y_factor, double z_factor);
  void rotate_figure(double x_angle, double y_angle, double z_angle, bool undo);
  size_t get_n_vertices() const;
  size_t get_n_polygons() const;
  size_t get_n_polygons_edges() const;
  double get_move_coeff() const;

 private:
  Figure& figure;
};
};  // namespace s21

#include "worker.tpp"

#endif
