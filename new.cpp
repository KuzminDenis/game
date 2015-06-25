#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "stdio.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define MAX_PLAYERS 5

struct Player
{
    int x, y;
    int id;
    int texId;
    
    Player() {x = 0; y = 0; id = -1; texId = 0;}
    Player(int cx, int cy, int ci, int ct)
    {
        x = cx;
        y = cy;
        id = ci;
        texId = ct;
    }
    ~Player() { }

    void moveUp() {y-=2;}
    void moveDown() {y+=2;}
    void moveLeft() {x-=2;}
    void moveRight() {x+=2;}
};

struct Scene
{
    Player *players[MAX_PLAYERS];
    int plNum;
    int currId;

    Scene() {plNum = 0; currId = 0;}
    ~Scene()
    {
        for (int i = 0; i < plNum; i++)
            delete players[i];
    }
    
    void addPlayer(int x, int y, int tId)
    {
        players[plNum] = new Player(x, y, plNum, tId);
        plNum++;
    }
    void delPlayer(int id)
    {
        delete players[id];
        for (int i = id; i < (plNum-1); i++)
            players[i] = players[i+1];
        plNum--;
    }

    void select_player(int id) 
    {
        if (id < plNum)
            currId = id;
    }

    void moveUp() {players[currId]->moveUp();}
    void moveDown() {players[currId]->moveDown();}
    void moveLeft() {players[currId]->moveLeft();}
    void moveRight() {players[currId]->moveRight();}

};

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
