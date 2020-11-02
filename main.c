#include <stdlib.h>
#include <stdio.h>

#include "SDL.h"


int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    /* Initialize SDL */
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
        return 1;
    }

    if(SDL_InitSubSystem(SDL_INIT_JOYSTICK) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_InitSubSystem fail : %s\n", SDL_GetError());
        return 1;
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Base path : %s\n", SDL_GetBasePath());
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Pref path : %s\n", SDL_GetPrefPath("pigs","sdl2demo"));


    /* Create window and renderer for given surface */

    window = SDL_CreateWindow("Chess Board", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 544, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(!window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n",SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n",SDL_GetError());
        return 1;
    }

    /* Clear the rendering surface with the specified color */
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    SDL_Surface* surface = SDL_LoadBMP("app0:/piglet.bmp");
    if (!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cant load image : %s\n",SDL_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cant create texture : %s\n",SDL_GetError());
    }
    SDL_FreeSurface(surface);


    SDL_Rect rectum;
    rectum.x = 100;
    rectum.y = 100;
    rectum.w = 100;
    rectum.h = 100;

    SDL_Rect pig_rectum;
    pig_rectum.x = 0;
    pig_rectum.y = 0;
    pig_rectum.w = 32;
    pig_rectum.h = 32;

    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);

        SDL_RenderFillRect(renderer, &rectum);

        SDL_RenderCopy(renderer, texture, NULL, &pig_rectum);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

