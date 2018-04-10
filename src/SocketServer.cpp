//
// Created by GRUB on 29/03/2018.
//

#include <sys/socket.h>
#include <err.h>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include "../include/SocketServer.h"

SocketServer::SocketServer() {
    int one = 1;
    int port = 8080;

    this->sin_len = sizeof(this->cli_addr);

    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sock < 0)
        err(1, "Can't open the socket");

    setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

    this->svr_addr.sin_family = AF_INET;
    this->svr_addr.sin_addr.s_addr = INADDR_ANY;
    this->svr_addr.sin_port = htons(port);

    if (bind(this->sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
        close(this->sock);
        err(1, "Can't bind");
    }
    listen(this->sock, 5);

    lastModification = "";
}


void SocketServer::run() {
    std::string file = "./web/html/test.html";
    const char *response;// = (readFile("./web/html/test.html").c_str());
/*char response[] = "HTTP/1.1 200 OK\n\r"
      "Date: Tue, 15 Nov 1994 08:12:31 GMT\n\r"
                      "Content-Type: text/html; charset=UTF-8\n\r\n\r"
                      "<!DOCTYPE html><html><head><title>Zia BTTF SOLO MAMENE</title></head>"
                      "<body><h1>LOL</h1></body></html>";
*/
    int client_fd;

    while (true) {
        if (modificationCatcher(file) == true)
            response = (readFile("./web/html/test.html").c_str());
        client_fd = accept(this->sock, (struct sockaddr *) &(this->cli_addr), &(this->sin_len));

            if (client_fd == -1) {
                perror("Can't accept");
                continue;
            }
            std::cout << "oui" << std::endl;

            write(client_fd, response/*.c_str()*/, strlen(response));
            printConnection();
            close(client_fd);

    }
}

void SocketServer::printConnection() {
    std::cout << "Connection from IP "
              << ( ( ntohl(this->cli_addr.sin_addr.s_addr) >> 24) & 0xff ) << "."
              << ( ( ntohl(this->cli_addr.sin_addr.s_addr) >> 16) & 0xff ) << "."
              << ( ( ntohl(this->cli_addr.sin_addr.s_addr) >> 8) & 0xff )  << "."
              <<   ( ntohl(this->cli_addr.sin_addr.s_addr) & 0xff ) << ", port "
              << ntohs(this->cli_addr.sin_port);
}



std::string SocketServer::readFile(std::string file) {

    std::string line = "";
    std::string data = "";
    std::string header = "HTTP/1.1 200 OK\n\r"
                         "Content-Type: text/html; charset=UTF-8\n\r"
                         "\n\r";
    struct stat sb;

    if (stat(file.c_str(), &sb) == -1) {
        err(1, "Stats");
    }

    lastModification = ctime(&sb.st_mtime);
    std::ifstream myfile(file.c_str());


    if (myfile.is_open())
    {
        while (getline(myfile,line) )
        {
            data += line;
        }
        myfile.close();
        //header += std::to_string(data.length()) + "\n\r\n\r";
        data = header + data;
    }
    else
        std::cout << "Error while loading " + file << std::endl;
    return (data);
}

bool SocketServer::modificationCatcher(std::string file) {
    struct stat sb;

    if (stat(file.c_str(), &sb) == -1) {
        err(1, "Stats");
    }
    return strcmp(lastModification.c_str(), ctime(&sb.st_mtime)) != 0;

}

SocketServer::~SocketServer() {

}