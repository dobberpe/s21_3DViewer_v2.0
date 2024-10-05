#ifndef FIGURE_TPP
#define FIGURE_TPP

namespace s21 {

/// @brief Figure constructor
inline Figure::Figure()
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
      rotation_matrix(9, 0.0),
      move_coefficient(0) {};

/// @brief Creates an instance of Figure in case the figure is empty
/// @return an instance of Figure
inline Figure& Figure::get_instance() {
  static Figure instance;
  return instance;
}

/// @brief adds a vertex to the figure
/// @param x_
/// @param y_
/// @param z_
inline void Figure::add_vertex(double x_, double y_, double z_) {
  Logger::instance().log("add_vertex " + QString::number(x_) + " " +
                         QString::number(y_) + " " + QString::number(z_));
  if (!n_vertex) {
    x_max = x_;
    y_max = y_;
    z_max = z_;
    x_min = x_;
    y_min = y_;
    z_min = z_;
  } else {
    if (x_ > x_max) x_max = x_;
    if (y_ > y_max) y_max = y_;
    if (z_ > z_max) z_max = z_;
    if (x_ < x_min) x_min = x_;
    if (y_ < y_min) y_min = y_;
    if (z_ < z_min) z_min = z_;
  }
  vertex.push_back(x_);
  vertex.push_back(y_);
  vertex.push_back(z_);
  ++n_vertex;
  Logger::instance().log("n_vertex " + QString::number(n_vertex));
}

inline size_t Figure::get_n_vertex() const { return n_vertex; }

inline size_t Figure::get_n_polygons() const { return n_polygons; }

inline size_t Figure::get_n_polygons_edges() const { return n_polygon_edges; }

inline tuple<const double*, size_t> Figure::get_vertex() const {
  return make_tuple(vertex.data(), n_vertex);
}

inline tuple<const Polygon*, size_t> Figure::get_polygon() const {
  return make_tuple(polygons.data(), n_polygons);
}

/// @brief adds a polygon to the figure
/// @param polygon
inline void Figure::add_polygon(const Polygon& polygon) {
  polygons.push_back(polygon);
  ++n_polygons;
  Logger::instance().log("n_polygons " + QString::number(n_polygons));
  n_polygon_edges += polygon.n_points / 2;
}

inline void Figure::move_figure(double x_factor, double y_factor,
                                double z_factor) {
  fill_move_matrix(move_coefficient * x_factor, move_coefficient * y_factor, move_coefficient * z_factor);
  move_();
}

/// @brief Alignes the figure to the center so the center of the figure is 0,0,0
inline void Figure::align_to_center() {
  double x_center = (x_min + x_max) / 2.0;
  double y_center = (y_min + y_max) / 2.0;
  double z_center = (z_min + z_max) / 2.0;
  for (size_t i = 0; i < n_vertex; ++i) {
    vertex[i * 3 + x] = (vertex[i * 3 + x] - x_center);
    vertex[i * 3 + y] = (vertex[i * 3 + y] - y_center);
    vertex[i * 3 + z] = (vertex[i * 3 + z] - z_center);
    calc_min_max(i);
  }
}

/// @brief Scales the figure by a factor
/// @param scale_coef
inline void Figure::scale_figure(double scale_coef) {
  if (scale_coef > 1e-6) {
    for (size_t i = 0; i < n_vertex; ++i) {
      vertex[i * 3 + x] *= scale_coef;
      vertex[i * 3 + y] *= scale_coef;
      vertex[i * 3 + z] *= scale_coef;
      // calc_min_max(i);
    }
  }
}

/// @brief Calculates min max values of the figure
/// @param index
inline void Figure::calc_min_max(size_t index) {
  if (vertex[index * 3 + x] > x_max) x_max = vertex[index * 3 + x];
  if (vertex[index * 3 + y] > y_max) y_max = vertex[index * 3 + y];
  if (vertex[index * 3 + z] > z_max) z_max = vertex[index * 3 + z];
  if (vertex[index * 3 + x] < x_min) x_min = vertex[index * 3 + x];
  if (vertex[index * 3 + y] < y_min) y_min = vertex[index * 3 + y];
  if (vertex[index * 3 + z] < z_min) z_min = vertex[index * 3 + z];
  move_coefficient =
      max(max(x_max, y_max), z_max) - min(min(x_min, y_min), z_min);
}

/// @brief Rotates a figure by an angle in each axis
/// @param alpha_x
/// @param alpha_y
/// @param alpha_z
inline void Figure::rotate_figure(double alpha_x, double alpha_y,
                                  double alpha_z, bool undo) {
  alpha_x = alpha_x * M_PI / 180.0;
  alpha_y = alpha_y * M_PI / 180.0;
  alpha_z = alpha_z * M_PI / 180.0;
  if (undo) {
    Logger::instance().log("undo = true");
    fill_rotation_matrix_crd(alpha_z, z);
    rotate_(z);
    fill_rotation_matrix_crd(alpha_y, y);
    rotate_(y);
    fill_rotation_matrix_crd(alpha_x, x);
    rotate_(x);
  } else {
    Logger::instance().log("undo = false");
    fill_rotation_matrix_crd(alpha_x, x);
    rotate_(x);
    fill_rotation_matrix_crd(alpha_y, y);
    rotate_(y);
    fill_rotation_matrix_crd(alpha_z, z);
    rotate_(z);
  }
}

/// @brief Clears all attributes of the figure
inline void Figure::clear_figure() {
  Logger::instance().log("clear_figure");
  vertex.clear();
  n_vertex = 0U;
  Logger::instance().log("vertex cleared, n_vertex 0");
  polygons.clear();
  n_polygons = 0U;
  n_polygon_edges = 0U;
  Logger::instance().log("polygons cleared, n_polygons 0, n_polygon_edges");
  x_min = 0;
  y_min = 0;
  z_min = 0;
  x_max = 0;
  y_max = 0;
  z_max = 0;
  move_coefficient = 0;
  Logger::instance().log("x y z min max 0");
  move_matrix.clear();
  Logger::instance().log("move matrix clear");
  rotation_matrix.clear();
  Logger::instance().log("rotation matrix clear");
}

/// @brief Fills a move matrix 4x4, matrix is transposed by default
/// @param x_factor
/// @param y_factor
/// @param z_factor
inline void Figure::fill_move_matrix(double x_factor, double y_factor,
                                     double z_factor) {
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      move_matrix[i * 4 + j] = i == j ? 1 : 0;
    }
  }
  move_matrix[12] = x_factor;
  move_matrix[13] = y_factor;
  move_matrix[14] = z_factor;
}

/// @brief Actually moves a figure by the move matrix
inline void Figure::move_() {
  for (size_t i = 0; i < n_vertex; ++i) {
    vertex[i * 3 + x] = vertex[i * 3 + x] * move_matrix[0] + move_matrix[12];
    vertex[i * 3 + y] = vertex[i * 3 + y] * move_matrix[5] + move_matrix[13];
    vertex[i * 3 + z] = vertex[i * 3 + z] * move_matrix[10] + move_matrix[14];
    // calc_min_max(i);
  }
}

/// @brief Fills rotation matrix 3x3
/// @param alpha
/// @param crd x or y or z
inline void Figure::fill_rotation_matrix_crd(double alpha, int crd) {
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

/// @brief Actually rotates a figure by the rotation matrix
/// @param crd x or y or z
inline void Figure::rotate_(int crd) {
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
    // calc_min_max(i);
  }
}

};  // namespace s21

#endif  // FIGURE_TPP
