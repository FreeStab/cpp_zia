//
// Created by GRUB on 29/03/2018.
//

#ifndef CPP_ZIA_SERVER_H
#define CPP_ZIA_SERVER_H


class SocketServer{

public:
    SocketServer();
    ~SocketServer();

    int sock;
    struct sockaddr_in svr_addr;
    struct sockaddr_in cli_addr;
    socklen_t sin_len;

    void printConnection();
    std::string readFile(std::string);

    bool modificationCatcher(std::string);

    void run();

    std::string lastModification;

};
#endif //CPP_ZIA_SERVER_H
