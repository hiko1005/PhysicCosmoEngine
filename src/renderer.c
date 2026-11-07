#include <SDL2/SDL.h>
#include <stdio.h>
#include "lib/renderer/renderer.h"

int rendererInit() {
    if (SDL_INIT_EVERYTHING != 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
}

int createWindow(SDL_Window *window) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
}

int createRenderer(SDL_Renderer* renderer, SDL_Window* window) {
    renderer = SDL_CreateRenderer(window, -1, NULL);

    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
}