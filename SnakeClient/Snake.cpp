//
// Created by artem on 21.05.2022.
//

#include "Snake.h"

Snake::Snake(int n, int m, int posX, int posY):n(n),m(m){
        head.x=posX;
        head.y =posY;
        tail.x = head.x;
        tail.y = head.y;
        playerPosition.push_back(head);
}
deque<Vector2D>& Snake::getPlayerPosition(){
    return playerPosition;
};

void Snake::moveLeft(){
    if (head.x<=0)
        return;
    side=Side::LEFT;
    playerPosition.push_front({head.x-1,head.y});
    tail={-1,-1};
    head = playerPosition.front();
}

void Snake::moveRight(){
    if (head.x>=m-1)
        return;
    side=Side::RIGHT;
    playerPosition.push_front({head.x+1,head.y});
    tail={-1,-1};
    head = playerPosition.front();
}

void Snake::moveTop(){
    if (head.y>=n-1)
        return;
    side=Side::TOP;
    playerPosition.push_front({head.x,head.y+1});
    tail={-1,-1};
    head = playerPosition.front();
}

    void Snake::moveDown(){
    if (head.y<=0)
        return;
    side=Side::DOWN;
    playerPosition.push_front({head.x,head.y-1});
    tail={-1,-1};
    head = playerPosition.front();
}

Vector2D Snake::getTail(){
    return tail;
}

Vector2D Snake::getHead(){
    return head;
}

void Snake::updateTail(){
    tail=playerPosition.back();
}


bool KEY[256];
static void GetKEY()
{
    int i = 0;
    while(i < 256)
    {
        if(GetAsyncKeyState(i))
            KEY[i] = true;
        else KEY[i] = false;
        i++;
    }
}

bool runMoveSnake(Snake& snake){
    GetKEY();
    if (KEY[0x25])
        snake.side=Side::LEFT;
    if (KEY[0x26])
        snake.side=Side::DOWN;
    if (KEY[0x27])
        snake.side=Side::RIGHT;
    if (KEY[0x28])
        snake.side=Side::TOP;
    if (KEY[0x1B])
        return true;

    switch (snake.side) {
        case Side::LEFT:
            snake.side=Side::LEFT;
            break;
        case Side::RIGHT:
            snake.side=Side::RIGHT;
            break;
        case Side::TOP:
            snake.side=Side::TOP;
            break;
        case Side::DOWN:
            snake.side=Side::DOWN;
            break;
    }
    return false;
}
