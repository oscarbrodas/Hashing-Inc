// Copyright Nathan Dejesus, 2022

#include <SDL_image.h>
#include "Interactions.h"
#include <iostream>

// ---------- Interaction Functions ---------- //
/*
 *  These are the functions for the buttons events for the interface
 */

// Button Functions
button::button(int x, int y, int w, int h) {
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    mouse_position.x = 0;
    mouse_position.y = 0;
    sprite = button_mouse_out;
}

void button::set_position(int x, int y) {
    mouse_position.x = x;
    mouse_position.y = y;
}

void button::handle_event(SDL_Event* e) {
    int x, y;
    bool inside = true;

    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {

        SDL_GetMouseState(&x, &y);

        if (x < mouse_position.x || x > mouse_position.x + box.w || y < mouse_position.y || y > mouse_position.y + box.h)
            inside = false;

        if (!inside)
            sprite = button_mouse_out;
        else {
            switch (e->type) {
                case SDL_MOUSEMOTION:
                    sprite = button_motion_over;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    sprite = button_mouse_down;
                    break;

                case SDL_MOUSEBUTTONUP:
                    sprite = button_mouse_up;
                    break;
                default:
                    break;
            }

        }

    }
}



coordinate_button::coordinate_button(int x, int y, int w, int h, int lg, int lat, SDL_Renderer*& renderer) : button(x, y, w, h) {

    coordinate_button::set_position(x, y);
    this->lat = lat;
    this->lg = lg;

    loaded_image = IMG_Load("../Textures/coordinate.png");
    texture = SDL_CreateTextureFromSurface(renderer, loaded_image);
    SDL_FreeSurface(loaded_image);
    loaded_image = nullptr;

}

void coordinate_button::handle_event(SDL_Event* e, SDL_Renderer*& renderer) {
    button::handle_event(e);

    if (sprite == button_mouse_down) {
        std::cout << "Clicked coordinate.\n";

    }


}

void coordinate_button::render(SDL_Renderer*& renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &box);
}

void coordinate_button::set_position(int x, int y) {
    button::set_position(x, y);
}

SDL_Rect coordinate_button::getBox() {
    return box;
}


data_structure_button::data_structure_button(int x, int y, int w, int h, SDL_Renderer*& renderer) : button(x, y, w, h) {
    data_structure_button::set_position(x, y);

    loaded_image = IMG_Load("../Textures/button.png");
    texture = SDL_CreateTextureFromSurface(renderer, loaded_image);
    SDL_FreeSurface(loaded_image);
    loaded_image = nullptr;

}

void data_structure_button::render(SDL_Renderer*& renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &box);
}

void data_structure_button::handle_event(SDL_Event* e) {
    button::handle_event(e);

    if (sprite == button_mouse_down) {
        std::cout << "Clicked Hash Button.\n";

    }



}

void data_structure_button::set_position(int x, int y) {
    button::set_position(x, y);
}



