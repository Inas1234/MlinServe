#include "../include/HttpServer.h"
#include "../include/Route.h"
#include "../include/Cors.h"
#include <string.h>
#include <stdio.h>

CorsConfig* globalCorsConfig;

int logRequestMiddleware(Request* req, Response* res) {
    printf("Request received: %s %s\n", req->method, req->path);
    return 0;  
}

route(GET, "/login", hello, add_middleware(middleware, logRequestMiddleware));
void hello(Request* req, Response* res) {
    SEND_TEXT_RESPONSE(res, 200, "DRUZEE");
}


int corsMiddlewareWrapper(Request* req, Response* res) {
    return corsMiddleware(req, res, globalCorsConfig);
}


int main() {
    HttpServer* server = HttpServer_init(8080);
    Middleware* middleware = create_middleware(10); 


    globalCorsConfig = CorsConfig_init("*", "GET, POST, OPTIONS", "Content-Type, Authorization", 1);
    add_middleware(middleware, corsMiddlewareWrapper);


    HttpServer_start(server);

    CorseConfig_free(globalCorsConfig);
    free_middleware(middleware);
    Route_cleanup();
    HttpServer_stop(server);

    return 0;
}
