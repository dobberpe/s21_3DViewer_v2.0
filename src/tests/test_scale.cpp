#include "test_run.hpp"

TEST(Suite_scale, test_1) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  figure.align_to_center();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  EXPECT_NEAR(array[x], 2.71272, 1e-5);
  EXPECT_NEAR(array[y], -2.39876, 1e-5);
  EXPECT_NEAR(array[z], -2.49264, 1e-5);
}

TEST(Suite_scale, test_2) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/al.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();
  figure.align_to_center();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  EXPECT_NEAR(array[x], 0.786019, 1e-6);
  EXPECT_NEAR(array[y], -2.580399, 1e-6);
  EXPECT_NEAR(array[z], 0.601628, 1e-6);
}

TEST(Suite_scale, test_3) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  double check_x = array[x];
  double check_y = array[y];
  double check_z = array[z];
  double scale = 1.0;
  figure.scale_figure(scale);

  EXPECT_NEAR(array[x], check_x * scale, 1e-5);
  EXPECT_NEAR(array[y], check_y * scale, 1e-5);
  EXPECT_NEAR(array[z], check_z * scale, 1e-5);
}

TEST(Suite_scale, test_4) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  double check_x = array[x];
  double check_y = array[y];
  double check_z = array[z];
  double scale = 1.1;
  figure.scale_figure(scale);

  EXPECT_NEAR(array[x], check_x * scale, 1e-5);
  EXPECT_NEAR(array[y], check_y * scale, 1e-5);
  EXPECT_NEAR(array[z], check_z * scale, 1e-5);
}

TEST(Suite_scale, test_5) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  double check_x = array[x];
  double check_y = array[y];
  double check_z = array[z];
  double scale = 3.5;
  figure.scale_figure(scale);

  EXPECT_NEAR(array[x], check_x * scale, 1e-5);
  EXPECT_NEAR(array[y], check_y * scale, 1e-5);
  EXPECT_NEAR(array[z], check_z * scale, 1e-5);
}

TEST(Suite_scale, test_6) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  double check_x = array[x];
  double check_y = array[y];
  double check_z = array[z];
  double scale = 0.98;
  figure.scale_figure(scale);

  EXPECT_NEAR(array[x], check_x * scale, 1e-5);
  EXPECT_NEAR(array[y], check_y * scale, 1e-5);
  EXPECT_NEAR(array[z], check_z * scale, 1e-5);
}

TEST(Suite_scale, test_7) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  double check_x = array[x];
  double check_y = array[y];
  double check_z = array[z];
  double scale = -0.5;
  figure.scale_figure(scale);

  EXPECT_NEAR(array[x], check_x, 1e-5);
  EXPECT_NEAR(array[y], check_y, 1e-5);
  EXPECT_NEAR(array[z], check_z, 1e-5);
}