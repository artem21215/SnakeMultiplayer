//
// Created by artem on 21.05.2022.
//

#ifndef SNAKECLIENT_SNAKE_H
#define SNAKECLIENT_SNAKE_H
#include "HelpStructs.h"
#include "Network.h"
#include <deque>
#include <string>
using namespace std;

class Snake{
    int n;
    int m;
    deque<Vector2D> playerPosition;
    Vector2D head={};
    Vector2D tail={};

public:

    bool isInc=false;

    Side side = Side::LEFT;

    Snake(int n, int m, int posX, int posY);

    deque<Vector2D>& getPlayerPosition();

    void moveLeft();

    void moveRight();

    void moveTop();

    void moveDown();

    Vector2D getTail();

    Vector2D getHead();

    void updateTail();

};

bool runMoveSnake(Snake& snake);

#endif //SNAKECLIENT_SNAKE_H
