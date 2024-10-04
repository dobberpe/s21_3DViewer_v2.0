#include <QApplication>

#include "main_window/main_window.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  main_window w;
  w.show();
  return a.exec();
}
