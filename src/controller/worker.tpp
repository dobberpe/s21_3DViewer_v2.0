#ifndef WORKER_TPP
#define WORKER_TPP

namespace s21 {

/// @brief Worker constructor. Gets a figure instance.
inline Worker::Worker() : figure(Figure::get_instance()) {}

/// @brief Read and parse a file to figure.
/// @param file_path
/// @return true if file exists
inline bool Worker::parse_file(const string& file_path) {
  Logger::instance().log("parse " + QString::fromStdString(file_path));
  Parser parser;
  bool res = false;
  res = parser.parse_file_to_figure(file_path);
  figure.align_to_center();
  return res;
}

/// @brief Get vertex array.
/// @return tuple of vertex array and size
inline tuple<const double*, size_t> Worker::get_vertex_array() {
  return figure.get_vertex();
}

/// @brief Get polygon array.
/// @return tuple of polygon array and size
inline tuple<const Polygon*, size_t> Worker::get_polygon_array() {
  return figure.get_polygon();
}

/// @brief Scales a figure.
/// @param scale_coef in case of scaling up 1.__ in case of scaling down 0.__
/// e.g. 1.1 and 0.9
inline void Worker::scale(double scale_coef) {
  figure.scale_figure(scale_coef);
}

/// @brief Moves a figure by a factor.
/// @param x_factor
/// @param y_factor
/// @param z_factor
inline void Worker::move_figure(double x_factor, double y_factor,
                                double z_factor) {
  figure.move_figure(x_factor, y_factor, z_factor);
}

/// @brief Rotates a figure by an angle.
/// @param x_angle
/// @param y_angle
/// @param z_angle
inline void Worker::rotate_figure(double x_angle, double y_angle,
                                  double z_angle, bool undo) {
  figure.rotate_figure(x_angle, y_angle, z_angle, undo);
}

inline size_t Worker::get_n_vertices() const { return figure.get_n_vertex(); }
inline size_t Worker::get_n_polygons() const { return figure.get_n_polygons(); }

/// @brief Returns amount of edges
/// @return amount of edges
inline size_t Worker::get_n_polygons_edges() const {
  return figure.get_n_polygons_edges();
}

/// @brief Move coefficient: max(x, y, z) - min(x, y, z)
/// @return coefficient
inline double Worker::get_move_coeff() const { return figure.get_move_coeff(); }

};  // namespace s21

#endif  // WORKER_TPP
