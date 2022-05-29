#include <iostream>
#include <vector>
#include <Windows.h>
#include "HelpStructs.h"
#include "Dollar.h"
#include <time.h>
#include "Snake.h"
#include "Scene.h"
#include "Network.h"
using namespace std;
bool isBlock=true;
constexpr int cntPlayers = 2;
Network net{};
/// i think that with small amount of players std::vector better than std::map
vector<pair<int,Snake>> allSnakes;
vector<char> sideOtherSnake(cntPlayers,'l');
static int calc(string& i_message){
    int ans=0;
    for (auto& v:i_message){
        if (v=='_')
            continue;
        if (v==' ') {
            v='_';
            break;
        }
        ans*=10;
        ans+=v-'0';
        v='_';
    }
    return ans;
}

void lobby(int n, int m){
    cout << "cnt use" << endl;
    for (int i=0;i<cntPlayers-1;++i){
        string messageStartPosition = Network::readDataFromSocket(net.getSock());
        /// NOT CHANGE X AND Y!!!
        cout << messageStartPosition << endl;
        int socketForSnake = calc(messageStartPosition);
        int posYOther = calc(messageStartPosition);
        int posXOther = calc(messageStartPosition);
        cout << socketForSnake << ' ' << posXOther << ' ' << posYOther << endl;
        //cout << posXOther << ' ' << posYOther << endl;
        allSnakes.emplace_back(socketForSnake,Snake(n,m,posXOther,posYOther));
    }
    cout << "Wait message start" << endl;
    auto tmp = Network::readDataFromSocket(net.getSock());
    //cout << net.getSock();
    //cout << tmp << endl;
    isBlock=false;
}
void runGame(int n, int m,int posX, int posY){
    Scene scene(n,m);
    Snake snake(n,m,posY,posX);
    Dollar dollar(n,m);
    //scene.connectWithObjects(snake,dollar);
    //scene.updateScene();
    int debCnt = 0;
    while (true){
        if (isBlock){
            lobby(n,m);
            isBlock=false;
        }

        scene.connectWithObjects(snake,dollar);
        for (auto& v:allSnakes) {
            if (v.first==net.getSock())
                continue;
            scene.connectWithObjects(v.second, dollar);
        }
        scene.updateScene();
        cout << "Num step: " << debCnt << ' ' << net.getSock() << endl;
        bool isExit = runMoveSnake(snake);
        string messageAboutYourself;
        if (snake.getHead()==dollar.dollarPosition) {
            snake.isInc = true;
            messageAboutYourself+='1';
        }
        else
            messageAboutYourself+='0';
        switch (snake.side) {
            case Side::LEFT:
                messageAboutYourself+='l';
                Network::writeDataToSocket(net.getSock(),messageAboutYourself);
                snake.moveLeft();
                cout << net.getSock() << ' ' << 'l' << endl;
                break;
            case Side::RIGHT:
                messageAboutYourself+='r';
                Network::writeDataToSocket(net.getSock(),messageAboutYourself);
                cout << net.getSock() << ' ' << 'r' << endl;
                snake.moveRight();
                break;
            case Side::TOP:
                messageAboutYourself+='t';
                Network::writeDataToSocket(net.getSock(),messageAboutYourself);
                cout << net.getSock() << ' ' << 't' << endl;
                snake.moveTop();
                break;
            case Side::DOWN:
                messageAboutYourself+='d';
                Network::writeDataToSocket(net.getSock(),messageAboutYourself);
                cout << net.getSock() << ' ' << 'd' << endl;
                snake.moveDown();
                break;
        }

        //Cnt person may configure yaml file and i lazy, sorry, and want to sleep)
        cout << "RunLoadSide" << endl;
        //Sleep(1000);
        for (int i=0;i<cntPlayers-1;++i){
            if (net.getSock()==allSnakes[i].first)
                continue;
            string msgSide = Network::readDataFromSocket(net.getSock());
            cout << allSnakes[i].first << ' ' << msgSide << endl;
            //thereis was sideOtherSnake[calc(msgSide)]=msgSide[0];
            sideOtherSnake[0]=msgSide[5];
            if (msgSide[4]=='1')
                allSnakes[i].second.isInc=true;

            switch (msgSide[5]) {
                case 'l':
                    allSnakes[i].second.moveLeft();
                    break;
                case 'r':
                    allSnakes[i].second.moveRight();
                    break;
                case 'd':
                    allSnakes[i].second.moveDown();
                    break;
                case 't':
                    allSnakes[i].second.moveTop();
                    break;
            }
        }
        //Sleep(20000);

        if (isExit)
            break;
        Sleep(100);
        ++debCnt;
    }
    net.close();

}

int main(int argc, char** argv) {
    srand(time(0));
    constexpr int n = 30;
    constexpr int m = 70;
    allSnakes.reserve(cntPlayers);
    if (net.setNet(argc, argv)) {
        cout << "Error is appeared(" << endl;
    }
    string sizeSceneMessage = Network::readDataFromSocket(net.getSock());
    const int posX = calc(sizeSceneMessage);
    const int posY = calc(sizeSceneMessage);
    runGame(n,m,posX,posY);

    net.close();
    return 0;
}