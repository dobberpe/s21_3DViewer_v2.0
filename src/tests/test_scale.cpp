#include "test_run.hpp"

TEST(Suite_scale, test_1) {
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

  double x_center = (figure.get_x_min_() + figure.get_x_max_()) / 2.0;
  double y_center = (figure.get_y_min_() + figure.get_y_max_()) / 2.0;
  double z_center = (figure.get_z_min_() + figure.get_z_max_()) / 2.0;

  figure.align_to_center();

  EXPECT_EQ(array[x], check_x - x_center);
  EXPECT_EQ(array[y], check_y - y_center);
  EXPECT_EQ(array[z], check_z - z_center);
}

TEST(Suite_scale, test_2) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/al.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  double check_x = array[x];
  double check_y = array[y];
  double check_z = array[z];

  double x_center = (figure.get_x_min_() + figure.get_x_max_()) / 2.0;
  double y_center = (figure.get_y_min_() + figure.get_y_max_()) / 2.0;
  double z_center = (figure.get_z_min_() + figure.get_z_max_()) / 2.0;

  figure.align_to_center();

  EXPECT_EQ(array[x], check_x - x_center);
  EXPECT_EQ(array[y], check_y - y_center);
  EXPECT_EQ(array[z], check_z - z_center);
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