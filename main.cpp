#include "stdio.h"

#include "scene.h"
#include "engine.h"

#include "client_engine.h"

int main(int argc, char **argv)
{
    try
    {
        Scene scene;
        Engine engine;
        
        ClientEngine client;
        client.manageConnection("127.0.0.1");
 
//        scene.addPlayer(1,1,0);
//        scene.addPlayer(100,100,0);

//        scene.parseInfo("2 1 1 0 100 100 0");

        engine.init();
//        engine.mainLoop(&scene);

        const char *serv;        
        while(!engine.done)
        {
            serv = client.refreshInfo();
            if (strcmp(serv, "NULL"))
                scene.parseInfo(serv);
           const char* msg = engine.processSDL(&scene);
          printf("%s", msg); 
        }
    }
    catch (const char* causer)
    {
        printf("%s error: %s \n", causer, SDL_GetError());
    }

    return 0;
}
