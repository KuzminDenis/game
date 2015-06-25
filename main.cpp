#include "stdio.h"

#include "scene.h"
#include "engine.h"

int main(int argc, char **argv)
{
    try
    {
        Scene scene;
        Engine engine;
     
        scene.addPlayer(1,1,0);
        scene.addPlayer(100,100,0);

        engine.init();
        engine.mainLoop(&scene);
    }
    catch (const char* causer)
    {
        printf("%s error: %s \n", causer, SDL_GetError());
    }

    return 0;
}
