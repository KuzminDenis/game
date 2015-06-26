#include "server_engine.h"

ServerEngine::ServerEngine() { }

ServerEngine::~ServerEngine() 
{
    shutdown(ls, SHUT_RDWR);
    close(ls);
}

void ServerEngine::init()
{
    port = 1488;
    prepareListeningSocket();
    fillSet();
}

void ServerEngine::prepareListeningSocket()
{
    ls = socket(AF_INET, SOCK_STREAM, 0);
    if (ls == -1)
        throw "socket()";

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    setsockopt(ls, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (0 != bind(ls, (struct sockaddr *) &addr, sizeof(addr)))
        throw "bind()";

    if (-1 == listen(ls, 5))
        throw "listen()";

    max_descr = ls;
    descr_number = 0;

}

void ServerEngine::fillSet()
{
    FD_ZERO(&readfds); // clear set
    FD_SET(ls, &readfds); // add listening descriptor to set
    
    int fd;
    for (int i = 0; i < descr_number; i++)
    {
        fd = descr_array[i];
        FD_SET(fd, &readfds);
        if (fd > max_descr)
            max_descr = fd;
    }
}

void ServerEngine::manageConnection(Scene *scene)
{
    int fd;
    if (FD_ISSET(ls, &readfds)) // new connection request
    {
        socklen_t addrlen = sizeof(addr);
        fd = accept(ls, (struct sockaddr *) &addr, &addrlen);
        if (fd == -1)
            throw "accept()";

        if (descr_number < MAX_PLAYERS)
        {
            descr_array[descr_number] = fd;
            descr_number++;

            printf("New client [%d] \n", fd);

            scene->addPlayer(100, 100, 0);
        }
        else
        {
            const char messFull[] = "server full\n";
            write(fd, messFull, strlen(messFull)+1);
            shutdown(fd, SHUT_RDWR);
            printf("attempt\n");
        }
    }
}

void ServerEngine::manageData(Scene *scene)
{
    int fd, rd;
    char buff[BUFFER_SIZE];
    for (int i = 0; i < descr_number; i++)
    {
        fd = descr_array[i];
        if (FD_ISSET(fd, &readfds)) // incoming data from client
        {
            rd = read(fd, buff, sizeof(buff)-1);
            buff[rd] = '\0';

            printf("income:%s\n", buff);

            write(fd, scene->getInfo(), strlen(scene->getInfo())+1);
        }
    }
}

void ServerEngine::mainLoop(Scene *scene)
{
    timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 30000;

    while (true)
    {
        fillSet();

        int res = select(max_descr+1, &readfds, NULL, NULL, &tv);
//        if (res < 1)
//            throw "select()";

        int fd;
        for (int i = 0; i < descr_number; i++)
        {
            fd = descr_array[i];
            write(fd, scene->getInfo(), strlen(scene->getInfo())+1);
        }
        

        manageConnection(scene);
        manageData(scene);

        sleep(1);
    }
}


