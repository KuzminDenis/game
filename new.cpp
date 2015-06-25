#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "stdio.h"

#include "settings.h"
#include "scene.h"

struct Engine
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture *plTextures[MAX_PLAYERS];

    bool done;

    Engine() {done = false; window = NULL; renderer = NULL;}
    ~Engine()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

    void initSDL()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            throw "SDL_Init";
    }

    void createWindow()
    {
        window = SDL_CreateWindow("My Game",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == NULL)
            throw "SDL_CreateWindow";
    }

    void createRenderer()
    {
        renderer = SDL_CreateRenderer(window, -1,
                                      SDL_RENDERER_ACCELERATED |
                                      SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL)
            throw "SDL_CreateRenderer";
    }

    void init()
    {
        initSDL();
        createWindow();
        createRenderer();

        plTextures[0] = IMG_LoadTexture(renderer, "pics/player0.png");
    }

    void addTexture(int x, int y, SDL_Texture *tex)
    {
        SDL_Rect pos;
        pos.x = x;
        pos.y = y;

        SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer, tex, NULL, &pos);
    }

    void drawScene(Scene *scene)
    {
        SDL_RenderClear(renderer);
        for (int i = 0; i < scene->plNum; i++)
        {
            addTexture(scene->players[i]->x, 
                       scene->players[i]->y, 
                       plTextures[scene->players[i]->texId]);
        }

        SDL_RenderPresent(renderer);
    }

    void manageEvent(SDL_Event event, Scene *scene)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        scene->moveUp();
                        break;
                    case SDLK_DOWN:
                        scene->moveDown();
                        break;
                    case SDLK_RIGHT:
                        scene->moveRight();
                        break;
                    case SDLK_LEFT:
                        scene->moveLeft();
                        break;
                    case SDLK_0:
                        scene->select_player(0);
                        break;
                    case SDLK_1:
                        scene->select_player(1);
                        break;
                }
                break;
        }
    }

    void mainLoop(Scene *scene)
    {
        SDL_Event event;
        while(!done)
        {
            SDL_WaitEvent(&event);
            manageEvent(event, scene);
            drawScene(scene);
        }
    }
};

int main(int argc, char **argv)
{
    Scene scene;
    scene.addPlayer(1,1,0);
    scene.addPlayer(100,100,0);

    Engine engine;
    engine.init();
    engine.mainLoop(&scene);

    return 0;
}
