// HttpServer.c
#include "../include/HttpServer.h"
#include "../include/HttpParser.h"
#include "../include/Route.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

HttpServer* HttpServer_init(int port) {
    HttpServer* server = (HttpServer*)malloc(sizeof(HttpServer));
    if (!server) {
        perror("Failed to allocate memory for server");
        exit(EXIT_FAILURE);
    }

    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_fd == 0) {
        perror("Socket creation failed");
        free(server);
        exit(EXIT_FAILURE);
    }

    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(port);
    server->addrlen = sizeof(server->address);

    if (bind(server->server_fd, (struct sockaddr *)&server->address, sizeof(server->address)) < 0) {
        perror("Binding failed");
        close(server->server_fd);
        free(server);
        exit(EXIT_FAILURE);
    }

    return server;
}

void HttpServer_start(HttpServer* server) {
    if (listen(server->server_fd, 3) < 0) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }
    printf("HttpServer started on port %d\n", ntohs(server->address.sin_port));

    while (1) {
        HttpServer_handleClient(server);
    }
}

void HttpServer_stop(HttpServer* server) {
    close(server->server_fd);
    free(server);
    printf("HttpServer stopped.\n");
}

void HttpServer_handleClient(HttpServer* server) {
    int new_socket = accept(server->server_fd, (struct sockaddr *)&server->address, (socklen_t*)&server->addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        return;
    }

    char buffer[1024] = {0};
    read(new_socket, buffer, 1024);

    Request *request = HttpParser_parseRequest(buffer);
    if (request) {
        Response *res = Response_init(new_socket);
        
        RouteHandler handler = Route_findHandler(request->method, request->path);
        if (handler) {
            handler(request, res);  
        } else {
            const char *not_found = "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\n404 Not Found";
            send(new_socket, not_found, strlen(not_found), 0);
        }
        HttpParser_freeRequest(request);
    }
    close(new_socket);
}
