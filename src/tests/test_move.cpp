#include "test_run.hpp"

TEST(Suite_move, test_1) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  figure.move_figure(10.0, 2.0, 1.5);

  EXPECT_NEAR(array[x], 12.712726, 1e-5);
  EXPECT_NEAR(array[y], -0.398764, 1e-5);
  EXPECT_NEAR(array[z], -0.99264, 1e-5);

  EXPECT_NEAR(array[(n - 1) * 3 + x], 3.971338, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + y], 3.63977, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + z], 2.864798, 1e-5);
}

TEST(Suite_move, test_2) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  figure.move_figure(0.667, -8.0, 2.6);

  EXPECT_NEAR(array[x], 3.379726, 1e-5);
  EXPECT_NEAR(array[y], -10.398764, 1e-5);
  EXPECT_NEAR(array[z], 0.10736, 1e-5);

  EXPECT_NEAR(array[(n - 1) * 3 + x], -5.361662, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + y], -6.36023, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + z], 3.964798, 1e-5);
}

TEST(Suite_move, test_3) {
  Parser parser;
  bool res = true;
  res = parser.parse_file_to_figure("obj_files/airboat.obj");

  EXPECT_EQ(res, true);

  Figure& figure = Figure::get_instance();

  const double* array;
  size_t n;
  std::tie(array, n) = figure.get_vertex();

  figure.move_figure(-3.0, -10.333, -0.25);

  EXPECT_NEAR(array[x], -0.287274, 1e-5);
  EXPECT_NEAR(array[y], -12.731764, 1e-5);
  EXPECT_NEAR(array[z], -2.74264, 1e-5);

  EXPECT_NEAR(array[(n - 1) * 3 + x], -9.028662, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + y], -8.69323, 1e-5);
  EXPECT_NEAR(array[(n - 1) * 3 + z], 1.114798, 1e-5);
}