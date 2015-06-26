#ifndef _SCENE
#define _SCENE

#include "settings.h"
#include <string.h>
#include <stdio.h>

struct Player
{
    int x, y;
    int id;
    int texId;

    char info[BUFFER_SIZE];

    Player();
    Player(int cx, int cy, int ci, int ct);
    ~Player();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void refreshInfo();
    char* getInfo();
};

struct Scene
{
    Player *players[MAX_PLAYERS];
    int plNum;
    int currId;

    char info[BUFFER_SIZE];

    Scene();
    ~Scene();

    void addPlayer(int x, int y, int tId);
    void delPlayer(int id);
    void select_player(int id);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void concatToInfo(char *src);

    void refreshInfo();
    char* getInfo();
};

#endif
