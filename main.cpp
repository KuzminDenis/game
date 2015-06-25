#include "stdio.h"

#include "scene.h"
#include "engine.h"


int main(int argc, char **argv)
{
    Scene scene;
    Engine engine;
 
    scene.addPlayer(1,1,0);
    scene.addPlayer(100,100,0);

    engine.init();
    engine.mainLoop(&scene);

    return 0;
}
