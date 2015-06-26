#ifndef _BUFFER
#define _BUFFER

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "settings.h"

class Buffer
{
    char buff[BUFFER_SIZE];
    
  public:
 
    Buffer();
    char* get_buff();

    bool search_end();
    int ending_length();

    char* cut_ending();
    char* add_string(char* dest, char* src);
    
    char* get_string(int sockfd);
};

#endif
