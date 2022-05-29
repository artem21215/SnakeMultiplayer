//
// Created by artem on 21.05.2022.
//

#ifndef SNAKECLIENT_SCENE_H
#define SNAKECLIENT_SCENE_H
#include <string>
#include <vector>
#include "Snake.h"
#include "Dollar.h"
#include <iostream>
using namespace std;

class Scene{
    int n{};
    int m{};
    char simbolBorderVert='|';
    char simbolBorderGor = '_';
    vector<string> gameField;
public:
    Scene(int n,int m);

    void setSizeScene(int i_n, int i_m);


    void updateScene();

    pair<int,int> getSizeOfScene();

    void connectWithObjects(Snake& i_snake, Dollar& dollar);
};


#endif //SNAKECLIENT_SCENE_H
