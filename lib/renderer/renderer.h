#ifndef RENDERER_C
#define RENDERER_C

#include "lib/renderer/renderer.h"
#include <stdio.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const char *title = "CosmoEngine";

int renderInit();

int createWindow(SDL_Window *window);

int createRenderer(SDL_Renderer* renderer, SDL_Window* window);

#endif