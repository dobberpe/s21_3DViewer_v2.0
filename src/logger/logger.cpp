#include "logger.hpp"

s21::Logger &s21::Logger::instance() {
  static Logger logger;
  return logger;
}

void s21::Logger::log(const QString &message) {
  QMutexLocker locker(&mutex);

  if (out) {
    (*out) << message << "\n";
    out->flush();
  }
}

void s21::Logger::clearLog() {
  QMutexLocker locker(&mutex);
  if (file.isOpen()) file.close();

  file.open(QIODevice::WriteOnly | QIODevice::Truncate);
  out = new QTextStream(&file);
  file.close();
}

s21::Logger::Logger() {
  file.setFileName("build/log.txt");
  clearLog();
  if (!file.open(QIODevice::Append | QIODevice::Text)) {
    qWarning() << "Cannot open log file for writing";
  }

  out = new QTextStream(&file);
}

s21::Logger::~Logger() {
  if (file.isOpen()) {
    file.close();
  }

  delete out;
}
