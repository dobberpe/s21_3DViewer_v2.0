#include "test_run.hpp"

TEST(Suite_parser, test_1) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/test.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 190U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 123U);

  EXPECT_EQ(figure.get_x_max_(), 1430);
  EXPECT_EQ(figure.get_y_max_(), 250);
  EXPECT_EQ(figure.get_z_max_(), 0);
  EXPECT_EQ(figure.get_x_min_(), 70);
  EXPECT_EQ(figure.get_y_min_(), 50);
  EXPECT_EQ(figure.get_z_min_(), -50);
}

TEST(Suite_parser, test_2) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 5797U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 6273U);

  EXPECT_NEAR(figure.get_x_max_(), 8.11417, 1e-5);
  EXPECT_NEAR(figure.get_y_max_(), 2.39878, 1e-5);
  EXPECT_NEAR(figure.get_z_max_(), 2.83968, 1e-5);
  EXPECT_NEAR(figure.get_x_min_(), -8.11417, 1e-5);
  EXPECT_NEAR(figure.get_y_min_(), -2.39878, 1e-5);
  EXPECT_NEAR(figure.get_z_min_(), -2.83968, 1e-5);
}

TEST(Suite_parser, test_3) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/hawk.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 45031U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 85246U);

  EXPECT_NEAR(figure.get_x_max_(), 95.0126, 1e-3);
  EXPECT_NEAR(figure.get_y_max_(), 65.3929, 1e-3);
  EXPECT_NEAR(figure.get_z_max_(), 120.318, 1e-3);
  EXPECT_NEAR(figure.get_x_min_(), -95.0126, 1e-3);
  EXPECT_NEAR(figure.get_y_min_(), -1.87582, 1e-3);
  EXPECT_NEAR(figure.get_z_min_(), -118.473, 1e-3);
}

TEST(Suite_parser, wrong_test_1) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_1.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 0U);

  EXPECT_EQ(figure.get_x_max_(), 0);
  EXPECT_EQ(figure.get_y_max_(), 0);
  EXPECT_EQ(figure.get_z_max_(), 0);
  EXPECT_EQ(figure.get_x_min_(), 0);
  EXPECT_EQ(figure.get_y_min_(), 0);
  EXPECT_EQ(figure.get_z_min_(), 0);
}

TEST(Suite_parser, wrong_test_2) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_2.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 0U);

  EXPECT_EQ(figure.get_x_max_(), 0);
  EXPECT_EQ(figure.get_y_max_(), 0);
  EXPECT_EQ(figure.get_z_max_(), 0);
  EXPECT_EQ(figure.get_x_min_(), 0);
  EXPECT_EQ(figure.get_y_min_(), 0);
  EXPECT_EQ(figure.get_z_min_(), 0);
}

TEST(Suite_parser, wrong_test_3) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_3.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 0U);

  EXPECT_EQ(figure.get_x_max_(), 0);
  EXPECT_EQ(figure.get_y_max_(), 0);
  EXPECT_EQ(figure.get_z_max_(), 0);
  EXPECT_EQ(figure.get_x_min_(), 0);
  EXPECT_EQ(figure.get_y_min_(), 0);
  EXPECT_EQ(figure.get_z_min_(), 0);
}

TEST(Suite_parser, wrong_test_4) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_4.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 0U);

  EXPECT_EQ(figure.get_x_max_(), 0);
  EXPECT_EQ(figure.get_y_max_(), 0);
  EXPECT_EQ(figure.get_z_max_(), 0);
  EXPECT_EQ(figure.get_x_min_(), 0);
  EXPECT_EQ(figure.get_y_min_(), 0);
  EXPECT_EQ(figure.get_z_min_(), 0);
}

TEST(Suite_parser, wrong_test_5) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_5.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 4U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 2U);

  EXPECT_EQ(figure.get_x_max_(), 4);
  EXPECT_EQ(figure.get_y_max_(), 6);
  EXPECT_EQ(figure.get_z_max_(), 3);
  EXPECT_EQ(figure.get_x_min_(), 1);
  EXPECT_EQ(figure.get_y_min_(), -2);
  EXPECT_EQ(figure.get_z_min_(), -3);
}

TEST(Suite_parser, wrong_test_6) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_6.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 9U);

  EXPECT_EQ(figure.get_x_max_(), 0);
  EXPECT_EQ(figure.get_y_max_(), 0);
  EXPECT_EQ(figure.get_z_max_(), 0);
  EXPECT_EQ(figure.get_x_min_(), 0);
  EXPECT_EQ(figure.get_y_min_(), 0);
  EXPECT_EQ(figure.get_z_min_(), 0);
}

TEST(Suite_parser, wrong_test_7) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_7.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 3U);

  EXPECT_EQ(figure.get_x_max_(), 0);
  EXPECT_EQ(figure.get_y_max_(), 0);
  EXPECT_EQ(figure.get_z_max_(), 0);
  EXPECT_EQ(figure.get_x_min_(), 0);
  EXPECT_EQ(figure.get_y_min_(), 0);
  EXPECT_EQ(figure.get_z_min_(), 0);
}

TEST(Suite_parser, wrong_test_missing_file) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/random_missing_file.obj");

  EXPECT_EQ(res, false);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 0U);

  EXPECT_EQ(figure.get_x_max_(), 0);
  EXPECT_EQ(figure.get_y_max_(), 0);
  EXPECT_EQ(figure.get_z_max_(), 0);
  EXPECT_EQ(figure.get_x_min_(), 0);
  EXPECT_EQ(figure.get_y_min_(), 0);
  EXPECT_EQ(figure.get_z_min_(), 0);
}