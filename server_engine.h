#ifndef _SERVER_ENGINE
#define _SERVER_ENGINE

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>


#include "settings.h"
#include "scene.h"

struct ServerEngine
{
    int ls; // listening socket
    struct sockaddr_in addr;
    socklen_t addrlen;
    fd_set readfds;

    int port;

    int descr_array[MAX_PLAYERS];
    int descr_number;
    int max_descr;

    ServerEngine();
    ~ServerEngine();

    void init();
    void prepareListeningSocket();
    void fillSet();
    void manageConnection(Scene *scene);
    void manageData(Scene *scene);
    void mainLoop(Scene *scene);
};

#endif
