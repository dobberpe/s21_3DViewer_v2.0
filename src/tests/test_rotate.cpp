#include "test_run.hpp"

TEST(Suite_rotate, test_1) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  figure.rotate_figure(20, 0, 0, false);

  EXPECT_NEAR(array[x], 2.712726, 1e-5);
  EXPECT_NEAR(array[y], -1.40156774, 1e-5);
  EXPECT_NEAR(array[z], -3.16274102, 1e-5);

  EXPECT_NEAR(array[(n - 1) * 3 + x], -6.028662, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + y], 1.074091, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + z], 1.843325, 1e-5);
}

TEST(Suite_rotate, test_2) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  figure.rotate_figure(0, 50, 0, false);

  EXPECT_NEAR(array[x], -0.165766, 1e-5);
  EXPECT_NEAR(array[y], -2.398764, 1e-5);
  EXPECT_NEAR(array[z], -3.680306, 1e-5);

  EXPECT_NEAR(array[(n - 1) * 3 + x], -2.829653, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + y], 1.63977, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + z], 5.495498, 1e-5);
}

TEST(Suite_rotate, test_3) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  figure.rotate_figure(0, 0, 185, false);

  EXPECT_NEAR(array[x], -2.911469, 1e-5);
  EXPECT_NEAR(array[y], 2.153206, 1e-5);
  EXPECT_NEAR(array[z], -2.49264, 1e-5);

  EXPECT_NEAR(array[(n - 1) * 3 + x], 6.148636, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + y], -1.108097, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + z], 1.364798, 1e-5);
}

TEST(Suite_rotate, test_4) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  figure.rotate_figure(-274, 216, -164, false);

  EXPECT_NEAR(array[x], 1.298613, 1e-5);
  EXPECT_NEAR(array[y], -2.040332, 1e-5);
  EXPECT_NEAR(array[z], 3.671084, 1e-5);

  EXPECT_NEAR(array[(n - 1) * 3 + x], -4.054066, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + y], 0.134861, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + z], -4.94395, 1e-5);
}