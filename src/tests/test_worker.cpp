#include "test_run.hpp"

TEST(Suite_worker, test_parser) {
  Worker worker;

  bool res = true;
  worker.parse_file("obj_files/test.obj");
  EXPECT_EQ(res, true);

  const double* array;
  size_t n;
  std::tie(array, n) = worker.get_vertex_array();
  EXPECT_EQ(n, 190U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = worker.get_polygon_array();
  EXPECT_EQ(n_p, 123U);

  Figure& figure = Figure::get_instance();
  EXPECT_EQ(figure.get_x_max_(), 1430);
  EXPECT_EQ(figure.get_y_max_(), 250);
  EXPECT_EQ(figure.get_z_max_(), 0);
  EXPECT_EQ(figure.get_x_min_(), 70);
  EXPECT_EQ(figure.get_y_min_(), 50);
  EXPECT_EQ(figure.get_z_min_(), -50);
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

  EXPECT_NEAR(worker.get_x_max(), 8.11417, 1e-5);
  EXPECT_NEAR(worker.get_y_max(), 2.39878, 1e-5);
  EXPECT_NEAR(worker.get_z_max(), 2.83968, 1e-5);
  EXPECT_NEAR(worker.get_x_min(), -8.11417, 1e-5);
  EXPECT_NEAR(worker.get_y_min(), -2.39878, 1e-5);
  EXPECT_NEAR(worker.get_z_min(), -2.83968, 1e-5);
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

  EXPECT_NEAR(array[x], 3.379726, 1e-5);
  EXPECT_NEAR(array[y], -10.398764, 1e-5);
  EXPECT_NEAR(array[z], 0.10736, 1e-5);

  EXPECT_NEAR(array[(n - 1) * 3 + x], -5.361662, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + y], -6.36023, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + z], 3.964798, 1e-5);
}

TEST(Suite_worker, test_rotate) {
  Worker worker;

  bool res = true;
  worker.parse_file("obj_files/airboat.obj");
  EXPECT_EQ(res, true);

  const double* array;
  size_t n;
  std::tie(array, n) = worker.get_vertex_array();

  worker.rotate_figure(-274, 216, -164);

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