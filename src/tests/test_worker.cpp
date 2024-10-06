#include "test_run.hpp"

TEST(Suite_worker, test_parser) {
  Worker worker;

  bool res = true;
  worker.parse_file("obj_files/3dviewer.obj");
  EXPECT_EQ(res, true);

  const double* array;
  size_t n;
  std::tie(array, n) = worker.get_vertex_array();
  EXPECT_EQ(n, 190U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = worker.get_polygon_array();
  EXPECT_EQ(n_p, 123U);

  const Figure& figure = Figure::get_instance();
  EXPECT_EQ(figure.get_move_coeff(), 1360);
}

TEST(Suite_worker, test_parser_2) {
  Worker worker;

  bool res = true;
  worker.parse_file("obj_files/airboat.obj");
  EXPECT_EQ(res, true);

  const double* array;
  size_t n;
  std::tie(array, n) = worker.get_vertex_array();
  EXPECT_EQ(n, 5797U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = worker.get_polygon_array();
  EXPECT_EQ(n_p, 6273U);

  EXPECT_NEAR(worker.get_move_coeff(), 16.2283, 1e-4);
}

TEST(Suite_worker, test_scale) {
  Worker worker;

  bool res = true;
  worker.parse_file("obj_files/airboat.obj");
  EXPECT_EQ(res, true);

  const double* array;
  size_t n;
  std::tie(array, n) = worker.get_vertex_array();

  double check_x = array[x];
  double check_y = array[y];
  double check_z = array[z];

  double scale = 1.1;
  worker.scale(scale);

  EXPECT_NEAR(array[x], check_x * scale, 1e-5);
  EXPECT_NEAR(array[y], check_y * scale, 1e-5);
  EXPECT_NEAR(array[z], check_z * scale, 1e-5);
}

TEST(Suite_worker, test_move) {
  Worker worker;

  bool res = true;
  worker.parse_file("obj_files/airboat.obj");
  EXPECT_EQ(res, true);

  const double* array;
  size_t n;
  std::tie(array, n) = worker.get_vertex_array();

  worker.move_figure(0.667, -8.0, 2.6);

  EXPECT_NEAR(array[x], 13.537, 1e-3);
  EXPECT_NEAR(array[y], -132.225, 1e-3);
  EXPECT_NEAR(array[z], 39.701, 1e-3);

  EXPECT_NEAR(array[(n - 1) * 3 + x], 4.79564, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + y], -128.187, 1e-3);
  EXPECT_NEAR(array[(n - 1) * 3 + z], 43.5585, 1e-4);
}

TEST(Suite_worker, test_rotate) {
  Worker worker;

  bool res = true;
  worker.parse_file("obj_files/airboat.obj");
  EXPECT_EQ(res, true);

  const double* array;
  size_t n;
  std::tie(array, n) = worker.get_vertex_array();

  worker.rotate_figure(-274, 216, -164, false);

  EXPECT_NEAR(array[x], 1.298613, 1e-5);
  EXPECT_NEAR(array[y], -2.040332, 1e-5);
  EXPECT_NEAR(array[z], 3.671084, 1e-5);

  EXPECT_NEAR(array[(n - 1) * 3 + x], -4.054066, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + y], 0.134861, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + z], -4.94395, 1e-5);
}

TEST(Suite_worker, test_get_n) {
  Worker worker;

  bool res = true;
  worker.parse_file("obj_files/airboat.obj");
  EXPECT_EQ(res, true);

  EXPECT_EQ(worker.get_n_vertices(), 5797U);
  EXPECT_EQ(worker.get_n_polygons(), 6273U);
  EXPECT_EQ(worker.get_n_polygons_edges(), 24112U);
}