#ifndef __parser_HPP__
#define __parser_HPP__
#include <fstream>
#include <iostream>
#include <string>

#include "../figure/figure.hpp"
using namespace s21;

namespace s21 {
class Parser {
 public:
  Parser();

  bool parse_file_to_figure(const string& filePath);

 private:
  Figure& figure;
  long v = 0;
  vector<unsigned int> polygon_line;
  vector<unsigned int> sub_line;

  int num_slash = 0, prev_num_slash = 0;
  int pattern_size = 0, prev_pattern_size = 0;

  char* check;

  string strip_comment(string& line);

  void read_vertex_line(const string& line);

  bool read_polygon_token(const string& token);

  void read_polygon_line(const string& line);
};

};  // namespace s21

#include "parser.tpp"

#endif