// Copyright Nathan Dejesus, 2022

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <cstdio>
#include <iostream>
#include "Interface.h"


Interface::Interface() {

    // Establishes window
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow("Hashing Inc.",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    window_surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    loadImages();

    // Loads rectangles
    ani_rect1.x = 0; ani_rect1.y = 0; ani_rect1.w = SCREEN_WIDTH; ani_rect1.h = SCREEN_HEIGHT;
    ani_rect2.x = 0; ani_rect2.y = -SCREEN_HEIGHT; ani_rect2.w = SCREEN_WIDTH; ani_rect2.h = SCREEN_HEIGHT;
    map_rect.x = 100; map_rect.y = 125; map_rect.w = 495; map_rect.h = 421;
    text_rect.x = 100; text_rect.y = 270; text_rect.w = 235; text_rect.h = 70;
    title_rect.x = 265; title_rect.y = 5; title_rect.w = 550; title_rect.h = 100;
    table_rect1.x = 650; table_rect1.y = 100; table_rect1.w = 425; table_rect1.h = 600;
    table_rect2.x = 670; table_rect2.y = 175; table_rect2.w = 375; table_rect2.h = 25;
    button_rect.x = 120; button_rect.y = 625; button_rect.w = 235; button_rect.h = 70;
    time_rect.x = 150; time_rect.y = 650; time_rect.w = 110; time_rect.h = 25;


    // Load all buttons
    loadButtons();

}

void Interface::updateSurface() {

    SDL_RenderClear(renderer);

    renderBackground();
    renderTable();
    renderButtons();
    renderText();

    SDL_RenderPresent(renderer);

}

void Interface::loadImages() {

    image_loader = SDL_LoadBMP("../Textures/Ocean.bmp");
    image_loader = SDL_ConvertSurface(image_loader, window_surface->format, 0);
    bg_text = SDL_CreateTextureFromSurface(renderer, image_loader);
    SDL_FreeSurface(image_loader);

    image_loader = IMG_Load("../Textures/Florida.png");
    map_text = SDL_CreateTextureFromSurface(renderer, image_loader);
    SDL_FreeSurface(image_loader);

    image_loader = IMG_Load("../Textures/menu1.png");
    menu_text = SDL_CreateTextureFromSurface(renderer, image_loader);
    SDL_FreeSurface(image_loader);

    image_loader = IMG_Load("../Textures/button.png");
    box_text = SDL_CreateTextureFromSurface(renderer, image_loader);
    SDL_FreeSurface(image_loader);

    font = TTF_OpenFont("../Textures/font/Montserrat-Regular.ttf",24);
    image_loader = TTF_RenderText_Solid(font, "Time:     ms", {255,255,255});
    time_text = SDL_CreateTextureFromSurface(renderer, image_loader);
    SDL_FreeSurface(image_loader);

    image_loader = IMG_Load("../Textures/title.png");
    title_text = SDL_CreateTextureFromSurface(renderer, image_loader);
    SDL_FreeSurface(image_loader);

    image_loader = IMG_Load("../Textures/Table.png");
    table_text1 = SDL_CreateTextureFromSurface(renderer, image_loader);

    SDL_FreeSurface(image_loader);
    image_loader = nullptr;

}

void Interface::loadButtons() {

    // Creates Coordinate Boxes --- I'm actually sorry. There has to be a more efficient way to do this but idk.
    coordinate_button c2481(470, 525, 70, 70, 24, 81, renderer); coordinate_buttons.push_back(c2481);
    coordinate_button c2580(540, 455, 70, 70, 25, 80, renderer); coordinate_buttons.push_back(c2580);
    coordinate_button c2581(470, 455, 70, 70, 25, 81, renderer); coordinate_buttons.push_back(c2581);
    coordinate_button c2680(540, 385, 70, 70, 26, 80, renderer); coordinate_buttons.push_back(c2680);
    coordinate_button c2681(470, 385, 70, 70, 26, 81, renderer); coordinate_buttons.push_back(c2681);
    coordinate_button c2682(400, 385, 70, 70, 26, 82, renderer); coordinate_buttons.push_back(c2682);
    coordinate_button c2780(540, 315, 70, 70, 27, 80, renderer); coordinate_buttons.push_back(c2780);
    coordinate_button c2781(470, 315, 70, 70, 27, 81, renderer); coordinate_buttons.push_back(c2781);
    coordinate_button c2782(400, 315, 70, 70, 27, 82, renderer); coordinate_buttons.push_back(c2782);
    coordinate_button c2880(540, 245, 70, 70, 28, 80, renderer); coordinate_buttons.push_back(c2880);
    coordinate_button c2881(470, 245, 70, 70, 28, 81, renderer); coordinate_buttons.push_back(c2881);
    coordinate_button c2882(400, 245, 70, 70, 28, 82, renderer); coordinate_buttons.push_back(c2882);
    coordinate_button c2981(470, 175, 70, 70, 29, 81, renderer); coordinate_buttons.push_back(c2981);
    coordinate_button c2982(400, 175, 70, 70, 29, 82, renderer); coordinate_buttons.push_back(c2982);
    coordinate_button c2983(330, 175, 70, 70, 29, 83, renderer); coordinate_buttons.push_back(c2983);
    coordinate_button c2984(260, 175, 70, 70, 29, 84, renderer); coordinate_buttons.push_back(c2984);
    coordinate_button c2985(190, 175, 70, 70, 29, 85, renderer); coordinate_buttons.push_back(c2985);
    coordinate_button c3081(470, 105, 70, 70, 30, 81, renderer); coordinate_buttons.push_back(c3081);
    coordinate_button c3082(400, 105, 70, 70, 30, 82, renderer); coordinate_buttons.push_back(c3082);
    coordinate_button c3083(330, 105, 70, 70, 30, 83, renderer); coordinate_buttons.push_back(c3083);
    coordinate_button c3084(260, 105, 70, 70, 30, 84, renderer); coordinate_buttons.push_back(c3084);
    coordinate_button c3085(190, 105, 70, 70, 30, 85, renderer); coordinate_buttons.push_back(c3085);
    coordinate_button c3086(120, 105, 70, 70, 30, 86, renderer); coordinate_buttons.push_back(c3086);
    coordinate_button c3087(50, 105, 70, 70, 30, 87, renderer); coordinate_buttons.push_back(c3087);


    // Creates DS Buttons
    data_structure_button DSB1(15, 550, 235, 70, renderer);
    data_structure_button DSB2(235, 550, 235, 70, renderer);
    data_structure_buttons.push_back(DSB1);
    data_structure_buttons.push_back(DSB2);

}



void Interface::renderBackground() {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);

    int w,h;
    SDL_QueryTexture(bg_text, nullptr, nullptr, &w, &h);
    SDL_Delay(25);

    ani_rect1.y++;
    if(ani_rect1.y > SCREEN_HEIGHT - 1) ani_rect1.y = -SCREEN_HEIGHT;
    ani_rect2.y++;
    if(ani_rect2.y > SCREEN_HEIGHT - 1) ani_rect2.y = -SCREEN_HEIGHT ;

    // Scrolls up and down
    SDL_SetTextureBlendMode(bg_text, SDL_BLENDMODE_NONE);
    SDL_RenderCopy(renderer, bg_text, nullptr, &ani_rect1);
    SDL_RenderCopy(renderer, bg_text, nullptr, &ani_rect2);

    // Renders map
    SDL_RenderCopy(renderer, map_text, nullptr, &map_rect);

    // Writes text box, title box, and time box
    SDL_RenderCopy(renderer, menu_text, nullptr, &text_rect);
    SDL_RenderCopy(renderer, title_text, nullptr, &title_rect);
    SDL_RenderCopy(renderer, box_text, nullptr, &button_rect);

}

void Interface::renderTable() {

    SDL_RenderCopy(renderer, table_text1, nullptr, &table_rect1);

    // Renders table values


    SDL_FreeSurface(image_loader);

}

void Interface::renderButtons() {

    int x, y;
    SDL_GetMouseState(&x, &y);

    // Render coordinates based on mouse hovering over
    for (auto& b : coordinate_buttons)
        if (x >= b.getBox().x && x <= b.getBox().x + b.getBox().w && y >= b.getBox().y && y <= b.getBox().y + b.getBox().h)
            b.render(renderer);

    // Renders 4 lower left buttons
    for (auto& b : data_structure_buttons)
        b.render(renderer);

}

void Interface::renderText() {

    SDL_RenderCopy(renderer, box_text, nullptr, &button_rect);
    SDL_RenderCopy(renderer, time_text, nullptr, &time_rect);

}




bool Interface::pollForEvent() {
    return SDL_PollEvent(&event);
}


SDL_Event* Interface::getEvent() {
    return &event;
}

std::vector<data_structure_button> Interface::getDSButtons() {
    return data_structure_buttons;
}

std::vector<coordinate_button> Interface::getCButtons() {
    return coordinate_buttons;
}

SDL_Renderer*& Interface::getRenderer() {
    return renderer;
}

bool Interface::isOpen() {
    return window;
}

Interface::~Interface() {
    close();
}

void Interface::close() {

    // Deallocate surfaces
    SDL_FreeSurface(window_surface);
    SDL_FreeSurface(image_loader);
    window_surface = nullptr;
    image_loader = nullptr;

    // Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
}


