#include <QApplication>

#include "main_window/main_window.hpp"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
