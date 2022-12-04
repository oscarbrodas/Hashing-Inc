// Copyright Nathan Dejesus, 2022

#include <SDL.h>

#ifndef FINALPROJECT_INTERACTIONS_H
#define FINALPROJECT_INTERACTIONS_H


enum button_sprite {
    button_mouse_out = 0,
    button_motion_over = 1,
    button_mouse_down = 2,
    button_mouse_up = 3,
};

class button {
public:
    button(int x, int y, int w, int h);

    SDL_Surface* loaded_image = nullptr;

    SDL_Rect box {};

    SDL_Point mouse_position {};
    button_sprite sprite;

    virtual void set_position(int x, int y) ;
    virtual void handle_event(SDL_Event* e);
    virtual void render(SDL_Renderer*& renderer) {};


};

class coordinate_button : button {
public:
    int lg = 0, lat = 0;

    SDL_Texture* texture = nullptr;

    coordinate_button(int x, int y, int w, int h, int lg, int lat, SDL_Renderer*& renderer);

    void set_position(int x, int y) override;
    void handle_event(SDL_Event* e, SDL_Renderer*& renderer);
    void render(SDL_Renderer*& renderer) override;
    SDL_Rect getBox();

};

class data_structure_button : button {
public:
    SDL_Texture* texture = nullptr;

    data_structure_button(int x, int y, int w, int h, SDL_Renderer*& renderer);

    void set_position(int x, int y) override;
    void handle_event(SDL_Event* e) override;
    void render(SDL_Renderer*& renderer) override;

};




#endif //FINALPROJECT_INTERACTIONS_H
