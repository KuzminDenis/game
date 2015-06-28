#include "client_engine.h"

ClientEngine::ClientEngine() { port = 1488; }
ClientEngine::~ClientEngine()
{
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}

void ClientEngine::manageConnection(const char* ip)
{
     if (0 >= (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
        throw "socket()";

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (!inet_aton(ip, &(addr.sin_addr)))
        throw "inet_aton()";

    if (0 != connect(sockfd, (struct sockaddr *) &addr, sizeof(addr)))
        throw "connect()";

    tv.tv_sec = 1;
    tv.tv_usec = 0;
}

void ClientEngine::fillSet()
{
    FD_ZERO(&readfds);

//       FD_SET(0, &readfds);
    FD_SET(sockfd, &readfds);
}

const char* ClientEngine::refreshInfo()
{
    int rd;
//    char buff[BUFFER_SIZE];


    fillSet();
    int res = select(sockfd+1, &readfds, NULL, NULL, NULL);
    if (res < 1)
    {
//          throw "select()";
        printf("no msg\n");
        return "NULL";
    }

    if (FD_ISSET(sockfd, &readfds))
    {
//        rd = read(sockfd, buff, sizeof(buff)-1);
//        buff[rd] = '\0';

          srvmsg = buff.get_string(sockfd);

        printf("from server: %s\n", srvmsg);
        return srvmsg;
    }
    return "NULL\n";
}

void ClientEngine::sendMessage(const char* msg)
{
    write(sockfd, msg, strlen(msg)+1);
}
