#include "test_run.hpp"

TEST(Suite_move, test_1) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  figure.move_figure(10.0, 2.0, 1.5);

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  EXPECT_NEAR(array[x], 164.996, 1e-3);
  EXPECT_NEAR(array[y], 30.0579, 1e-4);
  EXPECT_NEAR(array[z], 21.8499, 1e-4);

  EXPECT_NEAR(array[(n - 1) * 3 + x], 156.255, 1e-3);
  EXPECT_NEAR(array[(n - 1) * 3 + y], 34.0965, 1e-4);
  EXPECT_NEAR(array[(n - 1) * 3 + z], 25.7073, 1e-4);
}

TEST(Suite_move, test_2) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();
  figure.move_figure(0.667, -8.0, 2.6);

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  EXPECT_NEAR(array[x], 13.537, 1e-3);
  EXPECT_NEAR(array[y], -132.225, 1e-3);
  EXPECT_NEAR(array[z], 39.701, 1e-3);

  EXPECT_NEAR(array[(n - 1) * 3 + x], 4.79564, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + y], -128.187, 1e-3);
  EXPECT_NEAR(array[(n - 1) * 3 + z], 43.5585, 1e-4);
}

TEST(Suite_move, test_3) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();
  figure.move_figure(-3.0, -10.333, -0.25);

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  EXPECT_NEAR(array[x], -45.9723, 1e-4);
  EXPECT_NEAR(array[y], -170.086, 1e-3);
  EXPECT_NEAR(array[z], -6.54973, 1e-5);

  EXPECT_NEAR(array[(n - 1) * 3 + x], -54.7137, 1e-4);
  EXPECT_NEAR(array[(n - 1) * 3 + y], -166.048, 1e-3);
  EXPECT_NEAR(array[(n - 1) * 3 + z], -2.69229, 1e-5);
}