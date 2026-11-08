#ifndef RENDERER_C
#define RENDERER_C

#include <SDL2/SDL.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const char* title;

int rendererInit();

int createWindow(SDL_Window *window);

int createRenderer(SDL_Renderer* renderer, SDL_Window* window);

#endif