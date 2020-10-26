#ifndef THREADEVENT_H
#define THREADEVENT_H

#include <QThread>
#include <QObject>
#include<SDL.h>
#include "dialog.h"

class threadevent : public QThread
{
    Q_OBJECT
public:
    explicit threadevent(QObject *parent=0);
    bool running=true;
signals:
    void SDL_Joybuttondown();
protected:
    void run();
private:
    SDL_Event event;

};

#endif // THREADEVENT_H
