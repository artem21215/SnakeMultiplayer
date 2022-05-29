//
// Created by artem on 21.05.2022.
//

#include "HelpStructs.h"
bool Vector2D::operator==(const Vector2D& other)const{
    if (this->x==other.x && this->y==other.y)
        return true;
    return false;
}

bool Vector2D::operator!=(const Vector2D& other)const{
    if (this->x==other.x && this->y==other.y)
        return false;
    return true;
}