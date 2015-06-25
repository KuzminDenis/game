#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "stdio.h"
#include <string>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class SDL_World;

SDL_Texture* loadImage(SDL_World *world, const char *file)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    loadedImage = SDL_LoadBMP(file);
    if (loadedImage != NULL)
    {
        texture = SDL_CreateTextureFromSurface(world->renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    else
        throw "SDL_LoadBMP";

    return texture;
}
class Scene 
{
    int x, y;
    SDL_Texture *player;
    SDL_World *world;
  public:
    Scene(){x = 0; y = 0; player = NULL;}
    Scene(SDL_World *p)
    {
        world = p;
        x = 0; y = 0; player = loadImage(world, "pics/pis.bmp");
    }
    ~Scene()
    {
        SDL_DestroyTexture(player);
    }


    void draw()
    {
        addTexture(x, y, player);
    }

    void moveUp() {y--;}
    void moveDown() {y++;}
    void moveLeft() {x--;}
    void moveRight() {x++;}
};


class SDL_World
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Scene *scene;

  public:
    SDL_World() 
    {
        window = createWindow();
        renderer = createRenderer();
        scene = new Scene(this);
    }
    ~SDL_World()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
};
 

void addTexture(SDL_World *world, int x, int y, SDL_Texture *tex)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(world->renderer, tex, NULL, &pos);
}

SDL_Window* createWindow()
{
    SDL_Window *window = SDL_CreateWindow("Suck my ass!", 
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 
                                          SCREEN_WIDTH, SCREEN_HEIGHT, 
                                          SDL_WINDOW_SHOWN);

    if (window == NULL)
        throw "SDL_CreateWindow"; 
    
    return window;
}

SDL_Renderer* createRenderer()
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
                                                SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        throw "SDL_CreateRenderer";

    return renderer;
}

void initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw "SDL_Init";
}
/*void mainLoop()
{
    SDL_Event event;
    bool done = false;
    while (!done)
    {

        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT: 
                done = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        scene.moveUp();
                        break;
                    case SDLK_DOWN:
                        scene.moveDown();
                        break;
                    case SDLK_RIGHT:
                        scene.moveRight();
                        break;
                    case SDLK_LEFT:
                        scene.moveLeft();
                        break;
                }
        }
        SDL_RenderClear(renderer);
        printf("huy");
        scene.draw();
        SDL_RenderPresent(renderer);
 
   }
}*/


int main(int argc, char **argv)
{
    try
    {
        initSDL();
//        mainLoop();

    SDL_Event event;
    bool done = false;
    SDL_World game;
//    Scene scene;
    while (!done)
    {

        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT: 
                done = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        game->scene.moveUp();
                        break;
                    case SDLK_DOWN:
                        game->scene.moveDown();
                        break;
                    case SDLK_RIGHT:
                        game->scene.moveRight();
                        break;
                    case SDLK_LEFT:
                        game->scene.moveLeft();
                        break;
                }
        }
        SDL_RenderClear(game.renderer);
        game->scene.draw();
        SDL_RenderPresent(game.renderer);
 
   }




        SDL_Quit();
    }
    catch (const char *causer)
    {
        const char *err = SDL_GetError();
        printf("%s error: %s \n", causer, err);
    }
    return 0;
}
