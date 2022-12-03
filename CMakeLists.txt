cmake_minimum_required(VERSION 3.22)
project(FinalProject)
set(CMAKE_CXX_STANDARD 14)

# list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
 # set(SDL2_PATH "../SDL2-2.26.0/x86_64-w64-mingw32")
 # set(SDL2_IMAGE_PATH "../SDL_image-2.6.2/x86_64-w64-mingw32")

set(SDL2_INCLUDE_DIR C:/libs/SDL2-2.26.1/include)
set(SDL2_LIB_DIR C:/libs/SDL2-2.26.1/lib/x64)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})


set(SDL2_IMAGE_INCLUDE_DIR C:/libs/SDL2_image-2.6.2/include)
set(SDL2_IMAGE_LIB_DIR C:/libs/SDL2_image-2.6.2/lib/x64)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

set(SDL2_TTF_INCLUDE_DIR C:/libs/SDL2_ttf-2.20.1/include)
set(SDL2_TTF_LIB_DIR C:/libs/SDL2_ttf-2.20.1/lib/x64)
include_directories(${SDL2_TTF_INCLUDE_DIR})
link_directories(${SDL2_TTF_LIB_DIR})

add_executable(
        FinalProject src/main.cpp
        src/Interface.cpp
        src/Interface.h
        src/Interactions.h
        src/Interactions.cpp
        )




target_link_libraries(FinalProject SDL2Main SDL2 SDL2_image SDL2_ttf)

