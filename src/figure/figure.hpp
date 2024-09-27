#ifndef __figure_HPP__
#define __figure_HPP__

#include <iostream>
using namespace std;

typedef enum { x = 0, y, z, homo } crd;

struct Polygon {
  vector<long> points;
  size_t n_points;
  Polygon(const vector<long>& p_line)
      : points(p_line), n_points(p_line.size()) {}
};

class Figure {
 public:
  static Figure& get_instance() {
    static Figure instance;
    return instance;
  }

  Figure(const Figure&) = delete;
  Figure& operator=(const Figure&) = delete;

  void add_vertex(double x, double y, double z) {
    if (!n_vertex) {
      x_max = x;
      y_max = y;
      z_max = z;
      x_min = x;
      y_min = y;
      z_min = z;
    } else {
      if (x > x_max) x_max = x;
      if (y > y_max) y_max = y;
      if (z > z_max) z_max = z;
      if (x < x_min) x_min = x;
      if (y < y_min) y_min = y;
      if (z < z_min) z_min = z;
    }
    vertex.push_back(x);
    vertex.push_back(y);
    vertex.push_back(z);
    ++n_vertex;
  }

  size_t get_n_vertex() const { return n_vertex; }

  size_t get_n_polygons() const { return n_polygons; }

  size_t get_n_polygons_edges() const { return n_polygon_edges; }

  tuple<const double*, size_t> get_vertex() const {
    return make_tuple(vertex.data(), n_vertex);
  }

  void add_polygon(const Polygon& polygon) {
    polygons.push_back(polygon);
    ++n_polygons;
    n_polygon_edges += polygon.n_points / 2;
  }

  tuple<const Polygon*, size_t> get_polygon() const {
    return make_tuple(polygons.data(), n_polygons);
  }

  double get_x_max_() const { return x_max; }
  double get_y_max_() const { return y_max; }
  double get_z_max_() const { return z_max; }
  double get_x_min_() const { return x_min; }
  double get_y_min_() const { return y_min; }
  double get_z_min_() const { return z_min; }

  void align_to_center() {
    double x_center = (x_min + x_max) / 2.0;
    double y_center = (y_min + y_max) / 2.0;
    double z_center = (z_min + z_max) / 2.0;
    for (size_t i = 0; i < n_vertex; ++i) {
      vertex[i * 3 + x] = (vertex[i * 3 + x] - x_center);
      vertex[i * 3 + y] = (vertex[i * 3 + y] - y_center);
      vertex[i * 3 + z] = (vertex[i * 3 + z] - z_center);
    }
  }

  void scale_figure(double scale_coef) {
    if (scale_coef > 1e-6) {
      for (size_t i = 0; i < n_vertex; ++i) {
        vertex[i * 3 + x] *= scale_coef;
        vertex[i * 3 + y] *= scale_coef;
        vertex[i * 3 + z] *= scale_coef;
      }
    }
  }

  void move_figure(double x_factor, double y_factor, double z_factor) {
    fill_move_matrix(x_factor, y_factor, z_factor);
    move_();
  }

  void rotate_figure(double alpha_x, double alpha_y, double alpha_z) {
    alpha_x = alpha_x * M_PI / 180.0;
    alpha_y = alpha_y * M_PI / 180.0;
    alpha_z = alpha_z * M_PI / 180.0;
    fill_rotation_matrix_crd(alpha_x, x);
    rotate_(x);
    fill_rotation_matrix_crd(alpha_y, y);
    rotate_(y);
    fill_rotation_matrix_crd(alpha_z, z);
    rotate_(z);
  }

  void clear_figure() {
    vertex.clear();
    n_vertex = 0U;
    polygons.clear();
    n_polygons = 0U;
    n_polygon_edges = 0U;
    x_min = 0;
    y_min = 0;
    z_min = 0;
    x_max = 0;
    y_max = 0;
    z_max = 0;
    move_matrix.clear();
    rotation_matrix.clear();
  }

 private:
  Figure()
      : n_vertex(0U),
        n_polygons(0U),
        n_polygon_edges(0U),
        x_min(0),
        y_min(0),
        z_min(0),
        x_max(0),
        y_max(0),
        z_max(0),
        move_matrix(16, 0.0),
        rotation_matrix(9, 0.0) {};
  ~Figure() {};

  void fill_move_matrix(double x_factor, double y_factor, double z_factor) {
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        move_matrix[i * 4 + j] = i == j ? 1 : 0;
      }
    }
    move_matrix[12] = x_factor;
    move_matrix[13] = y_factor;
    move_matrix[14] = z_factor;
  }

  void move_() {
    for (size_t i = 0; i < n_vertex; ++i) {
      vertex[i * 3 + 0] = vertex[i * 3 + 0] * move_matrix[0] + move_matrix[12];
      vertex[i * 3 + 1] = vertex[i * 3 + 1] * move_matrix[5] + move_matrix[13];
      vertex[i * 3 + 2] = vertex[i * 3 + 2] * move_matrix[10] + move_matrix[14];
    }
  }

  void fill_rotation_matrix_crd(double alpha, int crd) {
    rotation_matrix[0] = crd == x ? 1.0 : cos(alpha);
    rotation_matrix[1] = crd == z ? -sin(alpha) : 0;
    rotation_matrix[2] = crd == y ? sin(alpha) : 0;
    rotation_matrix[3] = crd == z ? sin(alpha) : 0;
    rotation_matrix[4] = crd == y ? 1 : cos(alpha);
    rotation_matrix[5] = crd == x ? -sin(alpha) : 0;
    rotation_matrix[6] = crd == y ? -sin(alpha) : 0;
    rotation_matrix[7] = crd == x ? sin(alpha) : 0;
    rotation_matrix[8] = crd == z ? 1 : cos(alpha);
  }

  void rotate_(int crd) {
    for (size_t i = 0; i < n_vertex; ++i) {
      double tmp[3] = {0, 0, 0};
      for (size_t j = 0; j < 3; ++j) {
        for (size_t k = 0; k < 3; ++k) {
          double value = 0;
          if (crd == x) value = rotation_matrix[j * 3 + k];
          if (crd == y) value = rotation_matrix[j * 3 + k];
          if (crd == z) value = rotation_matrix[j * 3 + k];
          tmp[j] += value * vertex[i * 3 + k];
        }
      }
      for (int j = 0; j < 3; ++j) {
        vertex[i * 3 + j] = tmp[j];
      }
    }
  }

  vector<double> vertex;
  size_t n_vertex;

  vector<Polygon> polygons;
  size_t n_polygons;
  size_t n_polygon_edges;

  double x_min, y_min, z_min, x_max, y_max, z_max;

  vector<double> move_matrix;
  vector<double> rotation_matrix;
};

#endif