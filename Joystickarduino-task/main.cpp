#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SDL_Init(SDL_INIT_JOYSTICK);
    Dialog w;
    w.show();
    return a.exec();
}
