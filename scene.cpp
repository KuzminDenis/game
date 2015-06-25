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
