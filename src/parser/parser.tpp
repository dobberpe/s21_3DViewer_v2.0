#ifndef PARSER_TPP
#define PARSER_TPP

namespace s21 {

/// @brief Parser constructor, takes a figure instance
inline Parser::Parser() : figure(Figure::get_instance()) {}

/// @brief Reads a file and parses it into a figure
/// @param filePath path to file
/// @return true in case file exists, false otherwise
inline bool Parser::parse_file_to_figure(const string& filePath) {
  locale::global(locale::classic());
  Logger::instance().log("parse_file_to_figure");
  bool success = true;
  figure.clear_figure();
  ifstream file(filePath);
  string line;

  if (file.is_open()) {
    Logger::instance().log("file opens");
    while (getline(file, line)) {
      line = strip_comment(line);
      if (line.compare(0, 2, "v ") == 0) {
        read_vertex_line(line.erase(0, 2));
      } else if (line.compare(0, 2, "f ") == 0) {
        read_polygon_line(line.erase(0, 2));
      }
    }
    file.close();
  } else {
    cerr << "Unable to open file: " << filePath << endl;
    success = false;
  }
  return success;
}

/// @brief Strips comments from line
/// @param line
/// @return striped line
inline string Parser::strip_comment(string& line) {
  size_t commentPos = line.find('#');
  if (commentPos != string::npos) {
    line = line.substr(0, commentPos);
  }
  return line;
}

/// @brief Reads a line that contains a vertex
/// @param line
inline void Parser::read_vertex_line(const string& line) {
  Logger::instance().log("read_vertex_line");
  vector<double> coords;
  size_t start = 0;
  size_t end = line.find(' ');

  size_t count = 0;
  string token;
  bool valid = true;
  char* check;

  while (end != string_view::npos && valid && count < 5) {
    token = line.substr(start, end - start);

    if (!token.empty()) {
      coords.push_back(strtod(token.c_str(), &check));
      ++count;
      if (*check != '\0') valid = false;
    }

    start = end + 1;
    end = line.find(' ', start);
  }
  Logger::instance().log(valid ? "after cycle valid = true"
                               : "after cycle valid = false");

  if (valid) {
    token = line.substr(start);
    if (!token.empty()) {
      coords.push_back(strtod(token.c_str(), &check));
      ++count;
      if (*check != '\0') valid = false;
    }
  }
  if (valid && (count == 3 || count == 4)) {
    figure.add_vertex(coords[0], coords[1], coords[2]);
  } else
    Logger::instance().log(valid ? "count != 3 && count != 4" : "!valid");
}

/// @brief Reads a polygon token
/// @param token string like 1/1/1 1//1 1/1 1
/// @return true if token is valid
inline bool Parser::read_polygon_token(const string& token) {
  size_t start_sub = 0, end_sub = token.find('/');
  string sub_token;
  sub_line.clear();
  bool valid = true;
  num_slash = 0;
  pattern_size = 0;

  while (end_sub != string_view::npos && valid) {
    ++num_slash;
    sub_token = token.substr(start_sub, end_sub - start_sub);
    if (!sub_token.empty()) {
      v = strtol(sub_token.c_str(), &check, 10);
      if (*check != '\0' || v < 1)
        valid = false;
      else
        sub_line.push_back(v);
      ++pattern_size;
    }
    start_sub = end_sub + 1;
    end_sub = token.find('/', start_sub);
  }

  if (valid) {
    sub_token = token.substr(start_sub);
    if (!sub_token.empty()) {
      v = strtol(sub_token.c_str(), &check, 10);
      if (*check != '\0' || v < 1)
        valid = false;
      else
        sub_line.push_back(v);
      ++pattern_size;
    }

    if (!polygon_line.empty() &&
        (prev_num_slash != num_slash || prev_pattern_size != pattern_size)) {
      valid = false;
    }
    if (valid && !sub_line.empty()) {
      if (!polygon_line.empty()) {
        polygon_line.pop_back();
        polygon_line.push_back(sub_line[0] - 1);
        polygon_line.push_back(sub_line[0] - 1);
      } else {
        polygon_line.push_back(sub_line[0] - 1);
      }
      polygon_line.push_back(polygon_line[0]);
    }
    prev_num_slash = num_slash;
    prev_pattern_size = pattern_size;
  }
  return valid;
}

/// @brief Reads polygon line
/// @param line
inline void Parser::read_polygon_line(const string& line) {
  Logger::instance().log("read_polygon_line");
  size_t start = 0, end = line.find(' ');
  string token;
  bool valid = true;
  v = 0;
  prev_num_slash = prev_pattern_size = 0;
  polygon_line.clear();

  while (end != string_view::npos && valid) {
    token = line.substr(start, end - start);
    if (!token.empty()) valid = read_polygon_token(token);
    start = end + 1;
    end = line.find(' ', start);
  }

  if (valid) {
    token = line.substr(start);
    if (!token.empty()) valid = read_polygon_token(token);
  }

  if (valid && !polygon_line.empty()) {
    Polygon polygon(polygon_line);
    figure.add_polygon(polygon);
  }
}

};  // namespace s21

#endif  // PARSER_TPP
