#include "server_engine.h"
#include <stdio.h>

#include "scene.h"

int main(int argc, char **argv)
{
    try
    {
        ServerEngine server; 
        server.init();

        Scene scene;
//        scene.addPlayer(1,1,0);

        printf("%s\n", scene.getInfo());


//        scene.addPlayer(100,100,0);

        printf("%s\n", scene.getInfo());

        server.mainLoop(&scene);
    }
    catch (const char* causer)
    {
        printf("Error: %s \n", causer);
    }

    return 0;
}
