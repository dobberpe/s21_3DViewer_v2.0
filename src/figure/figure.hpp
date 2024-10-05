#ifndef __figure_HPP__
#define __figure_HPP__

#include <cmath>
#include <iostream>

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

  double get_move_coeff() const { return move_coefficient; }

  void align_to_center();

  void scale_figure(double scale_coef);

  void calc_move_coeff(size_t index);

  void move_figure(double x_factor, double y_factor, double z_factor);

  void rotate_figure(double alpha_x, double alpha_y, double alpha_z, bool undo);

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

  double move_coefficient;
};

};  // namespace s21

#include "figure.tpp"

#endif
