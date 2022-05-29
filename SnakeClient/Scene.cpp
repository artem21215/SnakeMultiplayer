//
// Created by artem on 21.05.2022.
//

#include "Scene.h"
Scene::Scene(int n,int m):n(n),m(m){
    gameField.resize(n);
    for (int i=0;i<n;++i){
        gameField[i].assign(m,' ');
    }
}

void Scene::setSizeScene(int i_n, int i_m){
    n = i_n;
    m=i_m;
}


void Scene::updateScene(){
    system("cls");
    cout << string().assign(m,simbolBorderGor) << endl;
    for (auto& v:gameField) {
        cout << simbolBorderVert;
        cout << v;
        cout << simbolBorderVert << endl;
    }
    cout << string().assign(m,simbolBorderGor) << endl;
}
pair<int,int> Scene::getSizeOfScene(){
    return {n,m};
}

void Scene::connectWithObjects(Snake& i_snake, Dollar& dollar){
    auto& snakePos = i_snake.getPlayerPosition();
    if (snakePos.back()!=i_snake.getTail()) {
        gameField[snakePos.back().y][snakePos.back().x]=' ';
        if (!i_snake.isInc) {
            snakePos.pop_back();
        }
        else {
            gameField[dollar.dollarPosition.y][dollar.dollarPosition.x]=' ';
            dollar.updatePosition();
        }
        i_snake.isInc=false;
        i_snake.updateTail();
    }

    gameField[dollar.dollarPosition.y][dollar.dollarPosition.x]='$';
    bool isFirst = false;
    for (auto v:snakePos){
        auto[first,second]=v;
        if (!isFirst) {
            gameField[second][first] = 'g';
            isFirst = true;
            continue;
        }
        gameField[second][first]='*';
    }
}