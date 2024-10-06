#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QDebug>
#include <QFile>
#include <QMutex>
#include <QTextStream>

namespace s21 {
class Logger {
 public:
  Logger(const Logger&) = delete;
  void operator=(const Logger&) = delete;

  static Logger& instance();
  void log(const QString& message);
  void clearLog();

 private:
  Logger();
  ~Logger();

  QFile file;
  QTextStream* out;
  QMutex mutex;
};
}  // namespace s21

#endif
