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
#include "buffer.h"

struct ClientEngine
{
    struct sockaddr_in addr;
    fd_set readfds;

    int port;
    int sockfd;

//    char buff[BUFFER_SIZE];

    Buffer buff;
    char* srvmsg;


    timeval tv;

    ClientEngine();
    ~ClientEngine();

    void manageConnection(const char* ip);
    void fillSet();
    const char* refreshInfo();
    void sendMessage(const char* msg);
};

#endif
