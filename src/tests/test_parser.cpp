#include "test_run.hpp"

TEST(Suite_parser, test_1) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/3dviewer.obj");

  EXPECT_EQ(res, true);

  const Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 190U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 123U);

  EXPECT_EQ(figure.get_move_coeff(), 1480);
}

TEST(Suite_parser, test_2) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  const Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 5797U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 6273U);

  EXPECT_NEAR(figure.get_move_coeff(), 16.2283, 1e-4);
}

TEST(Suite_parser, test_3) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/hawk.obj");

  EXPECT_EQ(res, true);

  const Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 45031U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 85246U);

  EXPECT_NEAR(figure.get_move_coeff(), 238.790, 1e-3);
}

TEST(Suite_parser, wrong_test_1) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_1.obj");

  EXPECT_EQ(res, true);

  const Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 0U);

  EXPECT_EQ(figure.get_move_coeff(), 0);
}

TEST(Suite_parser, wrong_test_2) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_2.obj");

  EXPECT_EQ(res, true);

  const Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 0U);

  EXPECT_EQ(figure.get_move_coeff(), 0);
}

TEST(Suite_parser, wrong_test_3) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_3.obj");

  EXPECT_EQ(res, true);

  const Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 0U);

  EXPECT_EQ(figure.get_move_coeff(), 0);
}

TEST(Suite_parser, wrong_test_4) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_4.obj");

  EXPECT_EQ(res, true);

  const Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 0U);

  EXPECT_EQ(figure.get_move_coeff(), 0);
}

TEST(Suite_parser, wrong_test_5) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_5.obj");

  EXPECT_EQ(res, true);

  const Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 2U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 2U);

  EXPECT_EQ(figure.get_move_coeff(), 5);
}

TEST(Suite_parser, wrong_test_6) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_6.obj");

  EXPECT_EQ(res, true);

  const Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 9U);

  EXPECT_EQ(figure.get_move_coeff(), 0);
}

TEST(Suite_parser, wrong_test_7) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/tests_only/wr_test_7.obj");

  EXPECT_EQ(res, true);

  const Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 3U);

  EXPECT_EQ(figure.get_move_coeff(), 0);
}

TEST(Suite_parser, wrong_test_missing_file) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/random_missing_file.obj");

  EXPECT_EQ(res, false);

  const Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();
  EXPECT_EQ(n, 0U);

  const Polygon* polygon;
  size_t n_p;
  std::tie(polygon, n_p) = figure.get_polygon();
  EXPECT_EQ(n_p, 0U);

  EXPECT_EQ(figure.get_move_coeff(), 0);
}