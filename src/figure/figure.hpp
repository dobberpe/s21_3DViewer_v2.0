#ifndef __figure_HPP__
#define __figure_HPP__

#include <iostream>
#include "logger/logger.h"

using namespace std;

typedef enum { x = 0, y, z, homo } crd;

struct Polygon {
  vector<unsigned int> points;
  size_t n_points;
  Polygon(const vector<unsigned int>& p_line)
      : points(p_line), n_points(p_line.size()) {}
};

namespace s21 {

class Figure {
 public:
  static Figure& get_instance();

  Figure(const Figure&) = delete;

  Figure& operator=(const Figure&) = delete;

  void add_vertex(double x, double y, double z);

  size_t get_n_vertex() const;

  size_t get_n_polygons() const;

  size_t get_n_polygons_edges() const;

  tuple<const double*, size_t> get_vertex() const;

  void add_polygon(const Polygon& polygon);

  tuple<const Polygon*, size_t> get_polygon() const;

  double get_x_max_() const { return x_max; }
  double get_y_max_() const { return y_max; }
  double get_z_max_() const { return z_max; }
  double get_x_min_() const { return x_min; }
  double get_y_min_() const { return y_min; }
  double get_z_min_() const { return z_min; }

  void align_to_center();

  void scale_figure(double scale_coef);

  void move_figure(double x_factor, double y_factor, double z_factor);

  void rotate_figure(double alpha_x, double alpha_y, double alpha_z);

  void clear_figure();

 private:
  Figure();
  ~Figure() {};

  void fill_move_matrix(double x_factor, double y_factor, double z_factor);

  void move_();

  void fill_rotation_matrix_crd(double alpha, int crd);

  void rotate_(int crd);

  vector<double> vertex;
  size_t n_vertex;

  vector<Polygon> polygons;
  size_t n_polygons;
  size_t n_polygon_edges;

  double x_min, y_min, z_min, x_max, y_max, z_max;

  vector<double> move_matrix;
  vector<double> rotation_matrix;
};

};  // namespace s21

#include "figure.tpp"

#endif
