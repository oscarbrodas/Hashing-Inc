// Copyright Nathan Dejesus, 2022


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdio>
#include <vector>
#include "Interactions.h"

#ifndef FINALPROJECT_INTERFACE_H
#define FINALPROJECT_INTERFACE_H

class Interface {
private:
    const int SCREEN_WIDTH = 1080, SCREEN_HEIGHT = 720;

    SDL_Window* window = nullptr;

    SDL_Surface* window_surface = nullptr;
    SDL_Surface* text_surface = nullptr;
    SDL_Surface* image_loader = nullptr;

    SDL_Texture* bg_text = nullptr;
    SDL_Texture* map_text = nullptr;
    SDL_Texture* title_text = nullptr;
    SDL_Texture* menu_text = nullptr;
    SDL_Texture* table_text = nullptr;

    std::vector<coordinate_button> coordinate_buttons;
    std::vector<data_structure_button> data_structure_buttons;

    SDL_Renderer* renderer = nullptr;

    SDL_Rect ani_rect1, ani_rect2, map_rect, text_rect, title_rect, table_rect;

    SDL_Event event;


public:

    Interface();
    ~Interface();

    bool pollForEvent();
    SDL_Event* getEvent();
    SDL_Renderer*& getRenderer();
    std::vector<data_structure_button> getDSB();
    std::vector<coordinate_button> getCB();

    void loadImages();
    void loadButtons();
    void updateSurface();

    void renderBackground();
    void renderTable();
    void renderButtons();



    bool isOpen();

    void close();

};

#endif //FINALPROJECT_INTERFACE_H
