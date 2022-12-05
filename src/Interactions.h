// Copyright Nathan Dejesus, 2022

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include "datapoint.h"

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
    bool HASH = true;
    int lg = 0, lat = 0;

    SDL_Texture* texture = nullptr;

    coordinate_button(int x, int y, int w, int h, int lg, int lat, SDL_Renderer*& renderer);

    void set_position(int x, int y) override;
    pair<int, int> handle_event(SDL_Event* e, SDL_Renderer*&);
    void render(SDL_Renderer*& renderer) override;
    SDL_Rect getBox();

};

class data_structure_button : button {
public:
    SDL_Texture* texture = nullptr;

    data_structure_button(int x, int y, int w, int h, SDL_Renderer*& renderer);

    void set_position(int x, int y) override;
    void handle_event(SDL_Event* e, bool& HASH);
    void render(SDL_Renderer*& renderer) override;

};

class dynamic_table {
private:
    TTF_Font* font = nullptr;
    std::vector<double> dist, temp;
    std::vector<int> humidity, vis;
    std::vector<std::string> weather;

    SDL_Texture* texture;
    SDL_Rect d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;
    SDL_Rect t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    SDL_Rect h1, h2, h3, h4, h5, h6, h7, h8, h9, h10;
    SDL_Rect v1, v2, v3, v4, v5, v6, v7, v8, v9, v10;
    SDL_Rect w1, w2, w3, w4, w5, w6, w7, w8, w9, w10;

public:
    dynamic_table();

    void loadFont(TTF_Font* font);

    void write_table(SDL_Renderer*& renderer, SDL_Surface*& text_surface);

    void update_values(vector<vector<double>> dataNumeric, vector<string> dataString);

};


#endif //FINALPROJECT_INTERACTIONS_H
