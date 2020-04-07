#include "snake.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Snake window;
    window.setWindowTitle("GAME SNAKE");
    window.show();
    return app.exec();
}
