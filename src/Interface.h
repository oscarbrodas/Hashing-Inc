// Copyright Nathan Dejesus, 2022


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdio>
#include <vector>
#include "Interactions.h"
#include "datapoint.h"

#ifndef FINALPROJECT_INTERFACE_H
#define FINALPROJECT_INTERFACE_H

class Interface {
private:
    const int SCREEN_WIDTH = 1080, SCREEN_HEIGHT = 720;
    dynamic_table* table = new dynamic_table();
    float time = 0.00f;

    SDL_Window* window = nullptr;

    SDL_Surface* window_surface = nullptr;
    SDL_Surface* text_surface = nullptr;
    SDL_Surface* image_loader = nullptr;

    SDL_Texture* bg_text = nullptr;
    SDL_Texture* map_text = nullptr;
    SDL_Texture* title_text = nullptr;
    SDL_Texture* menu_text = nullptr;
    SDL_Texture* table_text1 = nullptr;
    SDL_Texture* box_text = nullptr;
    SDL_Texture* time_text = nullptr;

    TTF_Font* font = nullptr;

    std::vector<coordinate_button> coordinate_buttons;
    std::vector<data_structure_button> data_structure_buttons;

    SDL_Renderer* renderer = nullptr;

    SDL_Rect ani_rect1, ani_rect2, map_rect, text_rect, title_rect;
    SDL_Rect table_rect1, time_rect, button_rect;


    SDL_Event event;

    void renderBackground();
    void renderTable();
    void renderButtons();
    void renderText();

public:

    Interface();
    ~Interface();

    // Accessors
    bool pollForEvent();
    SDL_Event* getEvent();
    SDL_Renderer*& getRenderer();
    TTF_Font* getFont();
    std::vector<data_structure_button> getDSButtons();
    std::vector<coordinate_button> getCButtons();

    // Loading Functions
    void loadImages();
    void loadButtons();
    void updateWindow();
    void updateTable(vector<vector<double>>& dataNumeric, vector<string>& dataString);

    bool isOpen();
    void close();

};

#endif //FINALPROJECT_INTERFACE_H
