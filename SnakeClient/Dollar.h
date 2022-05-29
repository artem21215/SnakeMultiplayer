//
// Created by artem on 21.05.2022.
//

#ifndef SNAKECLIENT_DOLLAR_H
#define SNAKECLIENT_DOLLAR_H
#include "HelpStructs.h"
#include "stdlib.h"

class Dollar{
public:
    int n{};
    int m{};
    Vector2D dollarPosition;
    Dollar(int n, int m);
    void updatePosition();
};


#endif //SNAKECLIENT_DOLLAR_H
