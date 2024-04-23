#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <math.h>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void drawRotatingLine(SDL_Renderer* renderer, int centerX, int centerY, int length, double angle, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int thickness) {
    Uint8 originalR, originalG, originalB, originalA;
    SDL_GetRenderDrawColor(renderer, &originalR, &originalG, &originalB, &originalA);

    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    double radians = angle * M_PI / 180.0;
    int endX = centerX + length * cos(radians);
    int endY = centerY + length * sin(radians);

    thickLineRGBA(renderer, centerX, centerY, endX, endY, thickness, r, g, b, a);

    SDL_SetRenderDrawColor(renderer, originalR, originalG, originalB, originalA);
}

void playBackgroundMusic() {
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    } else {
        Mix_Music *backgroundMusic = Mix_LoadMUS("background_music.mp3");
        if (backgroundMusic == NULL) {
            printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
        } else {
            Mix_PlayMusic(backgroundMusic, -1);
        }
    }
}


int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Radar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface* surface = IMG_Load("background.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    bool quit = false;
    SDL_Event event;

    double angle = 0; 
    double angleSpeed = 2;
    int lineLength = 300;
    int centerX = WINDOW_WIDTH / 2;
    int centerY = WINDOW_HEIGHT / 2;

    int numShadowPositions = 10;
    double prevAngles[numShadowPositions];
    memset(prevAngles, 0, sizeof(prevAngles));

    playBackgroundMusic();

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        for (int i = 0; i < numShadowPositions; ++i) {
            double shadowAngle = prevAngles[i];
            Uint8 shadowAlpha = (Uint8)(255 - i * 255 / numShadowPositions); 
            drawRotatingLine(renderer, centerX, centerY, lineLength, shadowAngle, 255, 0, 0, shadowAlpha, 4);
        }

        drawRotatingLine(renderer, centerX, centerY, lineLength, angle, 255, 0, 0, 255, 4);

        angle += angleSpeed;

        if (angle >= 360) {
            angle -= 360;
        }

        for (int i = numShadowPositions - 1; i > 0; --i) {
            prevAngles[i] = prevAngles[i - 1];
        }
        prevAngles[0] = angle;

        SDL_RenderPresent(renderer);

        SDL_Delay(20); 

    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
