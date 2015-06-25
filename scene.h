#ifndef _SCENE
#define _SCENE

#include "settings.h"

struct Player
{
    int x, y;
    int id;
    int texId;

    Player();
    Player(int cx, int cy, int ci, int ct);
    ~Player();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};

struct Scene
{
    Player *players[MAX_PLAYERS];
    int plNum;
    int currId;

    Scene();
    ~Scene();

    void addPlayer(int x, int y, int tId);
    void delPlayer(int id);
    void select_player(int id);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};

#endif
