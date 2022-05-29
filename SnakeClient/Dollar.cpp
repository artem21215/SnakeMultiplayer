//
// Created by artem on 21.05.2022.
//
#include "Dollar.h"
    Vector2D dollarPosition{};
    Dollar::Dollar(int n, int m):n(n),m(m){
        dollarPosition.x=rand()%(m-2)+1;
        dollarPosition.y=rand()%(n-2)+1;
    }
    void Dollar::updatePosition(){
        dollarPosition.x=rand()%(m-2)+1;
        dollarPosition.y=rand()%(n-2)+1;
    }