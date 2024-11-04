// HttpServer.h

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <netinet/in.h>

typedef struct {
    int server_fd;  
    struct sockaddr_in address;
    int addrlen;
} HttpServer;

HttpServer* HttpServer_init(int port);

void HttpServer_start(HttpServer* server);

void HttpServer_stop(HttpServer* server);

void HttpServer_handleClient(HttpServer* server);

#endif // HTTPSERVER_H
