#include <stdio.h>
#include "../lib/physic/physic.h"
#include "../lib/renderer/renderer.h"

int main() {
    SDL_Window* window;
    SDL_Renderer* renderer;
    if (createRenderer(renderer, window) == -1) {
        return 1;
    }


}

// SpaceObject Earth;
//     initSpaceObjects(&Earth, "Earth", 50, 100, 600, 600);
//     SpaceObject Sun;
//     initSpaceObjects(&Sun, "Sun", 1000, 20, -500, -600);
    
//     int n = 2;
//     SpaceObject* systemElements[] = {&Earth, &Sun};

//     unsigned int N;
//     do {
//         printf("N = "); scanf_s("%u", &N);
//     } while (N < 1);
//     for (unsigned int step = 0; step < N; step++) {
//         simulateStep(systemElements, n);
//         checkCollision(systemElements, n);
//         printf("[------------------[%-9d]------------------]\n", step+1);
//         for (int i = 0; i < n; i++) {
//             printf("[%s]: ", systemElements[i]->name);
//             printf("(%.2f;%.2f), ", systemElements[i]->position.x, systemElements[i]->position.y);
//             printf("v = %.3f, ", getVectorModule(systemElements[i]->velocity));
//             printf("a = %.6f|\n", getVectorModule(systemElements[i]->accelerate));
//         }
//     }