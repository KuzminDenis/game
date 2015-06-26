#include "client_engine.h"

int main(int argc, char **argv)
{
    try
    {
        ClientEngine client;
        client.manageConnection("127.0.0.1");
        while(true)
        {
           printf("xuy*\n");
           client.refreshInfo();
           client.sendMessage("ass\n");
        }
    }
    catch (const char* causer)
    {
        printf("Error: %s\n", causer);
    }
    return 0;
}
