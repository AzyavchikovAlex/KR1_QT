#include <iostream>
#include "Controllers/controller.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  Controller controller;
  controller.setWindowTitle("Duolingo");
  controller.setWindowIcon(QIcon(QPixmap("../Resources/Images/Icon.jpg")));
  controller.show();
  controller.resize(500, 500);
  return QApplication::exec();
}

