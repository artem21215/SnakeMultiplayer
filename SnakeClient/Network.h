//
// Created by artem on 21.05.2022.
//

#ifndef SNAKECLIENT_NETWORK_H
#define SNAKECLIENT_NETWORK_H
#include <iostream>
#include <cstdio>
//#include <WinSock2.h>
//#include <WS2tcpip.h>
#include <Windows.h>
#include "Snake.h"
#include <string>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
class Network{
    int sockfd;
public:
    int setNet(int argc,char** argv);

    void close() const;

    static string readDataFromSocket(const unsigned i_socket);

    static void writeDataToSocket(const unsigned i_socket,const string& i_message);

    inline int getSock(){
        return sockfd;
    }
};

#endif //SNAKECLIENT_NETWORK_H
