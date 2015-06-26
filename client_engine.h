#ifndef _CLIENT_ENGINE
#define _CLIENT_ENGINE

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

struct ClientEngine
{
    struct sockaddr_in addr;
    fd_set readfds;

    int port;
    int sockfd;

    timeval tv;

    ClientEngine();
    ~ClientEngine();

    void manageConnection(const char* ip);
    void fillSet();
    void refreshInfo();
    void sendMessage(const char* msg);
};

#endif
