#include "buffer.h"

Buffer::Buffer() { buff[0] = '\0'; }
char* Buffer::get_buff() { return buff; }

bool Buffer::search_end()
{
    int i = 0;
    while (buff[i])
    {
        if (buff[i] == '\n')
            return true;
        i++;
    }
    return false;
}

int Buffer::ending_length()
{
    int i = 0;
    while (buff[i])
    {
        if (buff[i] == '\n') 
            return i;
        i++;
    }
    return -1;
}

char* Buffer::cut_ending()
{
    int i, length = ending_length();
    char *tmp = new char[length + 1];

    for (i = 0; i < length; i++)
        tmp[i] = buff[i];
    tmp[i] = '\0';

    int rest_len = strlen(buff) - length - 1;
    for (i = 0; i < rest_len; i++)
        buff[i] = buff[length + 1 + i];
    buff[rest_len] = '\0';

    return tmp;
}

char* Buffer::add_string(char* dest, char* src)
{
    int dest_len = strlen(dest), src_len = strlen(src), i = 0;
    char* tmp = new char[dest_len + src_len + 1];

    for (i = 0; i < dest_len; i++)
        tmp[i] = dest[i];
    for (i = 0; i < src_len; i++)
        tmp[dest_len + i] = src[i];
    tmp[dest_len + src_len] = '\0';

    delete[] dest;
    return tmp;
}

char* Buffer::get_string(int sockfd)
{
    bool eol = 0;
    int rd;
    char* tmp;

    if (search_end())
    {
        tmp = cut_ending();
//        if (tmp[0] == '@')
            return tmp;
//        else 
//            return get_string(sockfd);
    }

    tmp = new char[1];
//    tmp[0] = '@';
//    tmp[1] = ' ';
    tmp[0] = '\0';
    tmp = add_string(tmp, buff);
    while (0 != (rd = read(sockfd, buff, BUFFER_SIZE - 1)))
    {
        buff[rd] = '\0';
        eol = search_end();
 
        if (!eol)
            tmp = add_string(tmp, buff);
        else
        {
            char* ending = cut_ending();
            tmp = add_string(tmp, ending);
            delete[] ending;
//            if (tmp[0] == '@')
                return tmp;
//           else
//                return get_string(sockfd);
        }
        buff[0] = '\0';
    }
    // EXCEPTION 
} 
