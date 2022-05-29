//
// Created by artem on 21.05.2022.
//

#ifndef SNAKECLIENT_HELPSTRUCTS_H
#define SNAKECLIENT_HELPSTRUCTS_H
#include <Windows.h>

class Vector2D{
public:
    bool operator==(const Vector2D& other) const;

    bool operator!=(const Vector2D& other) const;

    int x{};
    int y{};
};

enum class Side{
    LEFT,
    RIGHT,
    TOP,
    DOWN

};

#endif //SNAKECLIENT_HELPSTRUCTS_H
