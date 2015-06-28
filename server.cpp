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

//        server.mainLoop(&scene);
        while(true)
        {
            server.manageSelect();
            server.sendInfoToClients(&scene);
            server.manageNewConnections(&scene);
            const char* cmd = server.manageRecievedData(&scene);
            printf("recieved: %s\n", cmd);

            if (!strcmp(cmd, "up"))
                scene.moveUp();
            else if (!strcmp(cmd, "down"))
                scene.moveDown();
            else if (!strcmp(cmd, "right"))
                scene.moveRight();
            else if (!strcmp(cmd, "left"))
                scene.moveLeft();

            usleep(100);
        }


    }
    catch (const char* causer)
    {
        printf("Error: %s \n", causer);
    }

    return 0;
}
