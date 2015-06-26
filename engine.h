#ifndef _ENGINE
#define _ENGINE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "settings.h"
#include "scene.h"

struct Engine
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture *plTextures[MAX_PLAYERS];

    bool done;

    Engine();
    ~Engine();

    void initSDL();
    void createWindow();
    void createRenderer();
    void init();
    void addTexture(int x, int y, SDL_Texture *tex);
    void drawScene(Scene *scene);
    const char*  manageEvent(SDL_Event event, Scene *scene);
    const char* processSDL(Scene *scene);
    void mainLoop(Scene *scene);
};

#endif
