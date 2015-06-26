#include "scene.h"
   
Player::Player() {x = 0; y = 0; id = -1; texId = 0;}
Player::Player(int cx, int cy, int ci, int ct)
{
    x = cx;
    y = cy;
    id = ci;

    if (ct < MAX_PLAYERS)
        texId = ct;
    else
        texId = 0;
}

Player::~Player() { }

void Player::moveUp() {y-=2;}
void Player::moveDown() {y+=2;}
void Player::moveLeft() {x-=2;}
void Player::moveRight() {x+=2;}

void Player::refreshInfo()
{
    int n = sprintf(info, "%d %d %d ", x, y, texId);
    if (n < 0) 
        throw "sprintf()";
}

char* Player::getInfo()
{
    refreshInfo();
    return info;
}
        

Scene::Scene() {plNum = 0; currId = 0;}
Scene::~Scene()
{
    for (int i = 0; i < plNum; i++)
        delete players[i];
}

void Scene::addPlayer(int x, int y, int tId)
{
    players[plNum] = new Player(x, y, plNum, tId);
    plNum++;
}

void Scene::delPlayer(int id)
{
    delete players[id];
    for (int i = id; i < (plNum-1); i++)
        players[i] = players[i+1];
    plNum--;
}

void Scene::select_player(int id) 
{
    if (id < plNum)
        currId = id;
}

void Scene::moveUp()    {players[currId]->moveUp();}
void Scene::moveDown()  {players[currId]->moveDown();}
void Scene::moveLeft()  {players[currId]->moveLeft();}
void Scene::moveRight() {players[currId]->moveRight();}

void Scene::concatToInfo(char* src)
{
    int i = 0;
    while (info[i] != '\0')
        i++;
    
    int j = 0;
    while (src[j] != '\0')
    {
        info[i] = src[j];
        i++;
        j++;
    }

    info[i] = '\0';
}


void Scene::refreshInfo()
{
    int n = sprintf(info, "%d ", plNum);
    if (n < 0)
        throw "sprintf()";

    for (int i = 0; i < plNum; i++)
         concatToInfo(players[i]->getInfo());
}

char* Scene::getInfo()
{
    refreshInfo();
    return info;
}









