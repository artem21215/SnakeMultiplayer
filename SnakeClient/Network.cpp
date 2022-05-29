//
// Created by artem on 21.05.2022.
//

#include "Network.h"

using namespace std;
int Network::setNet(int argc,char** argv){
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cerr << "WSAStartup failed: " << result << "\n";
        return result;
    }



    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("server cant open main socket.");
        return 1;
    }

    struct sockaddr_in addr = {};
    struct sockaddr_in servAddr = {};
    servAddr.sin_family = AF_INET;
    auto hp = gethostbyname(argv[1]);
    memmove(&servAddr.sin_addr, hp->h_addr, hp->h_length);
    servAddr.sin_port = htons(atoi(argv[2]));
    memset((void* ) &addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd,(const struct sockaddr*)&addr, sizeof(addr)))
    {
        perror("bind client failed");
        return 1;
    }

    //socklen_t addr_len = sizeof(struct sockaddr_in);
    if(connect(sockfd, (const struct sockaddr *)&servAddr,sizeof(servAddr)))
    {
        perror("Connect client with server failed");
        return 1;
    }
    return 0;
}

void Network::close() const{
    closesocket(sockfd);
}

constexpr int buffLen=255;
char in_buf[buffLen];
string Network::readDataFromSocket(const unsigned i_socket){
    size_t msgLength = 0;
    memset((char *)&in_buf, 0, sizeof(in_buf));

    std::string message;
    if ((msgLength = recv(i_socket, in_buf, buffLen, 0)) < 0)
    {
        perror("bad recv of this thread.");
        closesocket(i_socket);
        exit(1);
    }

    for (int i=0;i<10;++i)
        cout << (int)in_buf[i] << ' ';
    cout << endl;
    if (in_buf[0]=='s' && in_buf[1]=='t')
        return "start";

    string temp;
    for (int i=0;i<buffLen;++i){
        if ((int)(in_buf[i])>='0' && (int)(in_buf[i])<='9' || in_buf[i]=='l' || in_buf[i]=='r' || in_buf[i]=='t' || in_buf[i]=='d') {
            temp+=in_buf[i];
        }
        else{
                if (!temp.empty()) {
                    temp+=' ';
                    message+=temp;
                    temp.clear();
                }
        }
    }
    return message;
}

void Network::writeDataToSocket(const unsigned i_socket,const string& i_message){
    send(i_socket, i_message.c_str(), strlen(i_message.c_str()), 0);
}