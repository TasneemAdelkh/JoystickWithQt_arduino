#include "threadevent.h"
#include "dialog.h"
threadevent::threadevent(QObject *parent):
        QThread(parent)
{
    SDL_JoystickOpen(0);

}
void threadevent::run()
{
    while(running)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type==SDL_JOYBUTTONDOWN)
            {
                emit SDL_Joybuttondown();
            }


        }

    }
}
