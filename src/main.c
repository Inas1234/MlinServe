#include "../include/HttpServer.h"
#include "../include/Route.h"
#include <string.h>
#include <stdio.h>

int logRequestMiddleware(Request* req, Response* res) {
    printf("Request received: %s %s\n", req->method, req->path);
    return 0;  
}

route(GET, "/login", hello, add_middleware(middleware, logRequestMiddleware));
void hello(Request* req, Response* res) {
    SEND_TEXT_RESPONSE(res, 200, "DRUZEE");
}


int main() {
    HttpServer* server = HttpServer_init(8080);
    HttpServer_start(server);

    Route_cleanup();
    HttpServer_stop(server);

    return 0;
}
