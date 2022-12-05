// Copyright Nathan Dejesus, 2022

#include <SDL_image.h>
#include "Interface.h"
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


// Coordinate Button Functions
coordinate_button::coordinate_button(int x, int y, int w, int h, int lg, int lat, SDL_Renderer*& renderer) : button(x, y, w, h) {

    coordinate_button::set_position(x, y);
    this->lat = lat;
    this->lg = lg;

    loaded_image = IMG_Load("../Textures/coordinate.png");
    texture = SDL_CreateTextureFromSurface(renderer, loaded_image);
    SDL_FreeSurface(loaded_image);
    loaded_image = nullptr;

}

pair<int, int> coordinate_button::handle_event(SDL_Event* e, SDL_Renderer*& renderer) {
    button::handle_event(e);

    // Return coordinates of button pressed
    if (sprite == button_mouse_down)
        return pair<int, int> {this->lg, this->lat};
    else
        return pair<int,int> {0,0};

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


// Data Structure Button Functions
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

void data_structure_button::handle_event(SDL_Event* e, bool& HASH) {
    button::handle_event(e);

    int x, y;
    SDL_GetMouseState(&x, &y);

    // Changes hash based on which button clicked
    if (sprite == button_mouse_down) {

        if (sprite == button_mouse_down) {

            if (x >= 15 && x <= 250) HASH = true;
            else if (x >= 250 && x <= 470) HASH = false;


        }
    }
}

void data_structure_button::set_position(int x, int y) {
    button::set_position(x, y);
}

// =========== Table Functions ========== //
/*
 * These functions are for the table for the interface.
 * Much of these lines are repeated code for
 * the 50 boxes and updating values.
 */
dynamic_table::dynamic_table() {

    for (int i = 0; i < 10; i++) {
        dist.push_back(0);
        temp.push_back(70.00);
        humidity.push_back(100);
        vis.push_back(10);
        weather.emplace_back("N/A");
    }

    // Loads 50 Boxes
    d1.x = 670; d1.y = 175; d1.w = 65; d1.h = 25;
    d2.x = 670; d2.y = 225; d2.w = 65; d2.h = 25;
    d3.x = 670; d3.y = 275; d3.w = 65; d3.h = 25;
    d4.x = 670; d4.y = 325; d4.w = 65; d4.h = 25;
    d5.x = 670; d5.y = 375; d5.w = 65; d5.h = 25;
    d6.x = 670; d6.y = 425; d6.w = 65; d6.h = 25;
    d7.x = 670; d7.y = 475; d7.w = 65; d7.h = 25;
    d8.x = 670; d8.y = 525; d8.w = 65; d8.h = 25;
    d9.x = 670; d9.y = 575; d9.w = 65; d9.h = 25;
    d10.x = 670; d10.y = 625; d10.w = 65; d10.h = 25;

    h1.x = 760; h1.y = 175; h1.w = 30; h1.h = 25;
    h2.x = 760; h2.y = 225; h2.w = 30; h2.h = 25;
    h3.x = 760; h3.y = 275; h3.w = 30; h3.h = 25;
    h4.x = 760; h4.y = 325; h4.w = 30; h4.h = 25;
    h5.x = 760; h5.y = 375; h5.w = 30; h5.h = 25;
    h6.x = 760; h6.y = 425; h6.w = 30; h6.h = 25;
    h7.x = 760; h7.y = 475; h7.w = 30; h7.h = 25;
    h8.x = 760; h8.y = 525; h8.w = 30; h8.h = 25;
    h9.x = 760; h9.y = 575; h9.w = 30; h9.h = 25;
    h10.x = 760; h10.y = 625; h10.w = 30; h10.h = 25;

    t1.x = 820; t1.y = 175; t1.w = 65; t1.h = 25;
    t2.x = 820; t2.y = 225; t2.w = 65; t2.h = 25;
    t3.x = 820; t3.y = 275; t3.w = 65; t3.h = 25;
    t4.x = 820; t4.y = 325; t4.w = 65; t4.h = 25;
    t5.x = 820; t5.y = 375; t5.w = 65; t5.h = 25;
    t6.x = 820; t6.y = 425; t6.w = 65; t6.h = 25;
    t7.x = 820; t7.y = 475; t7.w = 65; t7.h = 25;
    t8.x = 820; t8.y = 525; t8.w = 65; t8.h = 25;
    t9.x = 820; t9.y = 575; t9.w = 65; t9.h = 25;
    t10.x = 820; t10.y = 625; t10.w = 65; t10.h = 25;

    v1.x = 920; v1.y = 175; v1.w = 30; v1.h = 25;
    v2.x = 920; v2.y = 225; v2.w = 30; v2.h = 25;
    v3.x = 920; v3.y = 275; v3.w = 30; v3.h = 25;
    v4.x = 920; v4.y = 325; v4.w = 30; v4.h = 25;
    v5.x = 920; v5.y = 375; v5.w = 30; v5.h = 25;
    v6.x = 920; v6.y = 425; v6.w = 30; v6.h = 25;
    v7.x = 920; v7.y = 475; v7.w = 30; v7.h = 25;
    v8.x = 920; v8.y = 525; v8.w = 30; v8.h = 25;
    v9.x = 920; v9.y = 575; v9.w = 30; v9.h = 25;
    v10.x = 920; v10.y = 625; v10.w = 30; v10.h = 25;

    w1.x = 975; w1.y = 175; w1.w = 65; w1.h = 25;
    w2.x = 975; w2.y = 225; w2.w = 65; w2.h = 25;
    w3.x = 975; w3.y = 275; w3.w = 65; w3.h = 25;
    w4.x = 975; w4.y = 325; w4.w = 65; w4.h = 25;
    w5.x = 975; w5.y = 375; w5.w = 65; w5.h = 25;
    w6.x = 975; w6.y = 425; w6.w = 65; w6.h = 25;
    w7.x = 975; w7.y = 475; w7.w = 65; w7.h = 25;
    w8.x = 975; w8.y = 525; w8.w = 65; w8.h = 25;
    w9.x = 975; w9.y = 575; w9.w = 65; w9.h = 25;
    w10.x = 975; w10.y = 625; w10.w = 65; w10.h = 25;

}

void dynamic_table::loadFont(TTF_Font* font) {
    this->font = font;
}

// Renders all table values to screen
void dynamic_table::write_table(SDL_Renderer*& renderer, SDL_Surface*& text_surface) {

    // Makes 50 boxes

    text_surface = TTF_RenderText_Solid(font, std::to_string(dist.at(0)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &d1);

    text_surface = TTF_RenderText_Solid(font, std::to_string(dist.at(1)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &d2);

    text_surface = TTF_RenderText_Solid(font, std::to_string(dist.at(2)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &d3);

    text_surface = TTF_RenderText_Solid(font, std::to_string(dist.at(3)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &d4);

    text_surface = TTF_RenderText_Solid(font, std::to_string(dist.at(4)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &d5);

    text_surface = TTF_RenderText_Solid(font, std::to_string(dist.at(5)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &d6);

    text_surface = TTF_RenderText_Solid(font, std::to_string(dist.at(6)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &d7);

    text_surface = TTF_RenderText_Solid(font, std::to_string(dist.at(7)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &d8);

    text_surface = TTF_RenderText_Solid(font, std::to_string(dist.at(8)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &d9);

    text_surface = TTF_RenderText_Solid(font, std::to_string(dist.at(9)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &d10);



    text_surface = TTF_RenderText_Solid(font, std::to_string(temp.at(0)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &t1);

    text_surface = TTF_RenderText_Solid(font, std::to_string(temp.at(1)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &t2);

    text_surface = TTF_RenderText_Solid(font, std::to_string(temp.at(2)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &t3);

    text_surface = TTF_RenderText_Solid(font, std::to_string(temp.at(3)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &t4);

    text_surface = TTF_RenderText_Solid(font, std::to_string(temp.at(4)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &t5);

    text_surface = TTF_RenderText_Solid(font, std::to_string(temp.at(5)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &t6);

    text_surface = TTF_RenderText_Solid(font, std::to_string(temp.at(6)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &t7);

    text_surface = TTF_RenderText_Solid(font, std::to_string(temp.at(7)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &t8);

    text_surface = TTF_RenderText_Solid(font, std::to_string(temp.at(8)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &t9);

    text_surface = TTF_RenderText_Solid(font, std::to_string(temp.at(9)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &t10);



    text_surface = TTF_RenderText_Solid(font, std::to_string(humidity.at(0)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &h1);

    text_surface = TTF_RenderText_Solid(font, std::to_string(humidity.at(1)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &h2);

    text_surface = TTF_RenderText_Solid(font, std::to_string(humidity.at(2)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &h3);

    text_surface = TTF_RenderText_Solid(font, std::to_string(humidity.at(3)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &h4);

    text_surface = TTF_RenderText_Solid(font, std::to_string(humidity.at(4)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &h5);

    text_surface = TTF_RenderText_Solid(font, std::to_string(humidity.at(5)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &h6);

    text_surface = TTF_RenderText_Solid(font, std::to_string(humidity.at(6)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &h7);

    text_surface = TTF_RenderText_Solid(font, std::to_string(humidity.at(7)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &h8);

    text_surface = TTF_RenderText_Solid(font, std::to_string(humidity.at(8)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &h9);

    text_surface = TTF_RenderText_Solid(font, std::to_string(humidity.at(9)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &h10);



    text_surface = TTF_RenderText_Solid(font, std::to_string(vis.at(0)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &v1);

    text_surface = TTF_RenderText_Solid(font, std::to_string(vis.at(1)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &v2);

    text_surface = TTF_RenderText_Solid(font, std::to_string(vis.at(2)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &v3);

    text_surface = TTF_RenderText_Solid(font, std::to_string(vis.at(3)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &v4);

    text_surface = TTF_RenderText_Solid(font, std::to_string(vis.at(4)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &v5);

    text_surface = TTF_RenderText_Solid(font, std::to_string(vis.at(5)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &v6);

    text_surface = TTF_RenderText_Solid(font, std::to_string(vis.at(6)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &v7);

    text_surface = TTF_RenderText_Solid(font, std::to_string(vis.at(7)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &v8);

    text_surface = TTF_RenderText_Solid(font, std::to_string(vis.at(8)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &v9);

    text_surface = TTF_RenderText_Solid(font, std::to_string(vis.at(9)).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &v10);



    text_surface = TTF_RenderText_Solid(font, weather.at(0).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &w1);

    text_surface = TTF_RenderText_Solid(font, weather.at(1).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &w2);

    text_surface = TTF_RenderText_Solid(font, weather.at(2).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &w3);

    text_surface = TTF_RenderText_Solid(font, weather.at(3).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &w4);

    text_surface = TTF_RenderText_Solid(font, weather.at(4).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &w5);

    text_surface = TTF_RenderText_Solid(font, weather.at(5).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &w6);

    text_surface = TTF_RenderText_Solid(font, weather.at(6).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &w7);

    text_surface = TTF_RenderText_Solid(font, weather.at(7).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &w8);

    text_surface = TTF_RenderText_Solid(font, weather.at(8).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &w9);

    text_surface = TTF_RenderText_Solid(font, weather.at(9).c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, texture, nullptr, &w10);

}

void dynamic_table::update_values(vector<vector<double>> dataNumeric, vector<string> dataString) {

    dist.clear();
    for (auto i : dataNumeric[0])
        dist.push_back(i);
    while (dist.size() < 10) dist.push_back(0);

    temp.clear();
    for (auto i : dataNumeric[1])
        temp.push_back(i);
    while (temp.size() < 10) temp.push_back(0);

    humidity.clear();
    for (auto i : dataNumeric[2])
        humidity.push_back(i);
    while (humidity.size() < 10) humidity.push_back(0);

    vis.clear();
    for (auto i : dataNumeric[3])
        vis.push_back(i);
    while (vis.size() < 10) vis.push_back(0);

    weather.clear();
    for (auto i : dataString)
        weather.push_back(i);
    while (weather.size() < 10) weather.emplace_back("N/A");


}


