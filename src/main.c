#include "../include/HttpServer.h"
#include "../include/Route.h"
#include <string.h>
#include <stdio.h>

route(GET, "/login", hello);
void hello(Request* req, Response* res) {
    const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 15\r\n\r\nHello from login!";
    send(res->client_socket, response, strlen(response), 0);
}

route(POST, "/submit", submitForm);
void submitForm(Request* req, Response* res) {
    SEND_TEXT_RESPONSE(res, 200, "yo yo yo")
}

int main() {
    HttpServer* server = HttpServer_init(8080);
    HttpServer_start(server);

    Route_cleanup();
    HttpServer_stop(server);

    return 0;
}
