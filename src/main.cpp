#include <iostream>
#include <SDL.h>
#include "Interface.h"

using namespace std;



int main(int argc, char* args[]) {

    Interface display;

    if (!display.isOpen())
        cout << "Failed to create window. Error: " << SDL_GetError() << endl;

    bool closed = false;
    SDL_Event* e = nullptr;
    while (!closed) {
        display.updateSurface();

        while (display.pollForEvent()) {

                if  (display.getEvent()->type == SDL_QUIT) {
                    closed = true;
                    break;
                }

                for (auto b : display.getCB())
                    b.handle_event(display.getEvent(), display.getRenderer());

                for (auto b : display.getDSB())
                    b.handle_event(display.getEvent());





        }

    }

    display.close();

    return 0;
}


