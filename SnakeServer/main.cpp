#include <iostream>
#include <fstream>
#include <cstdio>
#include <process.h>
#include <thread>
#include <mutex>
#include <time.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>
#include <string>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

//MUST EQUAL SIZE OF CLIENT MAP
#define N 30
#define M 70

#define BUFLEN 255
constexpr int cntPlayers = 2;
int curCnt =0;
bool gameEnded = false;
bool isGameProcessing = false;
bool isPositionsSetted = false;
std::mutex g_pages_mutex;
//pthread_mutex_t globalMutex;

struct Coord{
    int x{};
    int y{};
};
using SockId = int;
vector<pair<SockId,Coord>> dataPlayers;

double gameTimeStart=0;
double curTime = 0;
double waitTime = 0;

void waitForPlayers(const int* id){
    while (curCnt<cntPlayers)
    {
    }
    isGameProcessing = true;
    while (!isPositionsSetted);
    gameTimeStart=(double)clock()/CLOCKS_PER_SEC;

    cout << "Send start " << dataPlayers[*id].first << endl;
    send(dataPlayers[*id].first, "start", strlen("start"), 0);
    int debCnt = 0;
    while (!gameEnded){
        cout << "#step " << debCnt << " of snake: " << *id << endl;
        char in_buf[BUFLEN];
        size_t msgLength = 0;
        memset((char *)&in_buf, 0, sizeof(in_buf));

        if ((msgLength = recv(dataPlayers[*id].first, in_buf, BUFLEN, 0)) < 0)
        {
            perror("bad recv of this thread.");
            closesocket(dataPlayers[*id].first);
            exit(1);
        }
        cout << "#step " << debCnt << " of snake: " << *id << " msgLen= " << in_buf << endl;
        string messageToAll = to_string(dataPlayers[*id].first);
        messageToAll+=' ';
        messageToAll+=in_buf[0];
        messageToAll+=in_buf[1];
        cout << messageToAll << ' ' << " # " << endl;
        for (auto &v:dataPlayers){
            //"socket l/r/t/d"
            if (v.first==dataPlayers[*id].first)
                continue;
            cout << v.first << ' ' << messageToAll << ' ' << strlen(messageToAll.c_str()) << ' ' << dataPlayers.size() << endl;
            send(v.first, messageToAll.c_str(), strlen(messageToAll.c_str()), 0);
            cout << "#step " << debCnt << " of snake: " << *id << " msgtoAll= " << messageToAll << endl;
            waitTime=curTime+0.2;
            while (abs(waitTime-curTime)>0.01){}
            cout << curTime << endl;

        }
        //Sleep(20000);
        debCnt++;
    }
}

int main()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cerr << "WSAStartup failed: " << result << "\n";
        return result;
    }
    int sockMain, length;

    if ((sockMain = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("server cant open main socket.");
        exit(1);
    }

    struct sockaddr_in servAddr{};
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = 0;

    //pthread_mutex_init(&globalMutex, nullptr);
    if (bind(sockMain, (struct sockaddr *)&servAddr, sizeof(servAddr)))
    {
        perror("bind server failed.");
        exit(1);
    }

    length = sizeof(servAddr);
    if (getsockname(sockMain, (struct sockaddr *)&servAddr, (socklen_t *__restrict)&length))
    {
        perror("call getsockname failed.");
        exit(1);
    }

    char string_buff[BUFLEN];
    inet_ntop(AF_INET, &servAddr.sin_addr, string_buff, BUFLEN);
    printf("Server:\n");
    printf("\tIP:%s:%d\n\n", string_buff, ntohs(servAddr.sin_port));

    listen(sockMain, SOMAXCONN);

    bool isNeedSetStartPosition = true;
    while (true)
    {
        ///Set start positions
        if (isGameProcessing && isNeedSetStartPosition){
            cout << "StartPosition setting" << endl;
            for (auto to:dataPlayers){
                for (auto from:dataPlayers){
                    if (to.first==from.first)
                        continue;
                    string messageStartPosition = to_string(from.first)+' '+to_string(from.second.x)+' '+to_string(from.second.y);

                    ///timer there
                    //waitTime=curTime+2.0;
                    //while (abs(waitTime-curTime)>0.02){}

                    send(to.first, messageStartPosition.c_str(), strlen(messageStartPosition.c_str()), 0);
                    cout << endl << messageStartPosition << endl;
                }
            }
            Sleep(2000);
            isNeedSetStartPosition = false;
            isPositionsSetted = true;
            cout << "Start position setted" << endl;
        }


        if (isGameProcessing){
            curTime = (double )clock()/CLOCKS_PER_SEC;
            continue;
            //cout << curTime << endl;
        }
        int *socketClient = new int(0);
        if (!isGameProcessing && (*socketClient = accept(sockMain, 0, 0)) < 0)
        {
            perror("failed socket for client.");
            exit(1);
        }



        if (!isGameProcessing && *socketClient>0){
            cout << "Player" << ' ' << *socketClient << ' ' << "connected" << endl;
            curCnt++;
            dataPlayers.push_back({*socketClient,{rand()%N,rand()%M}});
            string message = to_string(dataPlayers[curCnt-1].second.x)+' '+to_string(dataPlayers[curCnt-1].second.y);
            //1)random coords current snake "x y"
            send(*socketClient, message.c_str(), strlen(message.c_str()), 0);
            cout <<socketClient << ' ' << message << endl;
            int* ind = new int(dataPlayers.end()-dataPlayers.begin()-1);
            thread threadSnakes(waitForPlayers,ind);
            threadSnakes.detach();
        }

    }

    return 0;
}