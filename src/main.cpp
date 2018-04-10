#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
#include "../include/SocketServer.h"

/*char response[] = "HTTP/1.1 200 OK\r"
                  "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                  "<!DOCTYPE html>
                  <html>
                  <head>
                  <title>Zia BTTF SOLO MAMENE</title>
                  </head>"
                  "<body><h1>LOL</h1></body></html>\r\n";
*/

int main()
{
    SocketServer server;
    std::cout<< "lool" << std::endl;
    server.run();
}
