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

#define BUFFER_SIZE 128

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

    ServerEngine() 
    {port = 1488; }
    ~ServerEngine() 
    {
        shutdown(ls, SHUT_RDWR);
        close(ls);
    }

    void prepareListeningSocket()
    {

        ls = socket(AF_INET, SOCK_STREAM, 0);
        if (ls == -1)
            throw "socket()";

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (0 != bind(ls, (struct sockaddr *) &addr, sizeof(addr)))
            throw "bind()";

        if (-1 == listen(ls, 5))
            throw "listen()";

        max_descr = ls;
        descr_number = 0;

    }

    void fillSet()
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

    void manageConnection()
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
    void manageData()
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
            }
        }
    }

    void mainLoop()
    {
        while (true)
        {
            fillSet();

            int res = select(max_descr+1, &readfds, NULL, NULL, NULL);
            if (res < 1)
                throw "select()";

            manageConnection();
            manageData();
        }
    }
};



int main(int argc, char **argv)
{
    try
    {
        ServerEngine server; 
        server.prepareListeningSocket();

        server.mainLoop();
    }
    catch (const char* causer)
    {
        printf("Error: %s \n", causer);
    }

    return 0;
}
