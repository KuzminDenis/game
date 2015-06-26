#include "engine.h"

Engine::Engine() {done = false; window = NULL; renderer = NULL;}
Engine::~Engine()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Engine::initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw "SDL_Init";
}

void Engine::createWindow()
{
    window = SDL_CreateWindow("My Game",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == NULL)
        throw "SDL_CreateWindow";
}

void Engine::createRenderer()
{
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        throw "SDL_CreateRenderer";
}

void Engine::init()
{
    initSDL();
    createWindow();
    createRenderer();

    plTextures[0] = IMG_LoadTexture(renderer, "pics/player0.png");

}

void Engine::addTexture(int x, int y, SDL_Texture *tex)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(renderer, tex, NULL, &pos);
}

void Engine::drawScene(Scene *scene)
{
    SDL_RenderClear(renderer);
    for (int i = 0; i < scene->plNum; i++)
    {
        addTexture(scene->players[i]->x, 
                   scene->players[i]->y, 0);
                   //plTextures[scene->players[i]->texId]);
    }

    SDL_RenderPresent(renderer);
}

const char* Engine::manageEvent(SDL_Event event, Scene *scene)
{
    switch (event.type)
    {
        case SDL_QUIT:
            done = true;
            return "disconnect\n";
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    scene->moveUp();
                    return "up\n";
                    break;
                case SDLK_DOWN:
                    scene->moveDown();
                    return "down\n";
                    break;
                case SDLK_RIGHT:
                    scene->moveRight();
                    return "right\n";
                    break;
                case SDLK_LEFT:
                    scene->moveLeft();
                    return "left\n";
                    break;
                case SDLK_0:
                    scene->select_player(0);
                    return "0\n";
                    break;
                case SDLK_1:
                    scene->select_player(1);
                    return "1\n";
                    break;
            }
            break;
    }

    return "NULL\n";
}

const char* Engine::processSDL(Scene *scene)
{

    SDL_Event event;
    SDL_WaitEvent(&event);
    const char *res = manageEvent(event, scene);
    drawScene(scene);
    return res;
}


void Engine::mainLoop(Scene *scene)
{
    SDL_Event event;
    while(!done)
    {
        SDL_WaitEvent(&event);
        manageEvent(event, scene);
        drawScene(scene);
    }
}
