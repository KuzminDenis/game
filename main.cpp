#include <SDL2/SDL.h>
#include "stdio.h"

int main(int argc, char **argv)
{
    printf("test\n");

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        const char *err = SDL_GetError();
        printf("SDL_Init Error: %s \n", err);
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Suck my ass!", 
                                       100, 100, 640, 480,
                                       SDL_WINDOW_SHOWN);

    if (win == NULL)
    {
        const char *err = SDL_GetError();
        printf("SDL_CreateWindow Error: %s \n", err);
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED |
                                                    SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL)
    {
        const char *err = SDL_GetError();
        printf("SDL_CreateRenderer Error: %s \n", err);
        return 1;
    }
    
    SDL_Surface *bmp = SDL_LoadBMP("pics/pis.bmp");
    if (bmp == NULL)
    {
        const char *err = SDL_GetError();
        printf("SDL_LoadBMP Error: %s \n", err);
        return 1;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);

    if (tex == NULL)
    {
        const char *err = SDL_GetError();
        printf("SDL_CreateTexture Error: %s \n", err);
        return 1;
    }

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);

    SDL_Delay(2000);

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
