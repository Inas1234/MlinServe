#include "../include/HttpServer.h"
#include "../include/Route.h"
#include "../include/Cors.h"
#include "../include/Env.h"
#include <string.h>
#include <stdio.h>

CorsConfig* globalCorsConfig;

int logRequestMiddleware(Request* req, Response* res) {
    printf("Request received: %s %s\n", req->method, req->path);
    return 0;  
}

route(GET, "/login", hello, add_middleware(middleware, logRequestMiddleware));
void hello(Request* req, Response* res) {
    if (!req->headers || !strstr(req->headers, "Authorization")) {
        SEND_ERROR_RESPONSE(res, 401, "Unauthorized: Missing Authorization Header");
        return;
    }

    SEND_TEXT_RESPONSE(res, HTTP_OK, "DRUZEE");
}




int corsMiddlewareWrapper(Request* req, Response* res) {
    return corsMiddleware(req, res, globalCorsConfig);
}


int main() {
    load_env();

    const char* port_str = get_env("SERVER_PORT", "8080");

    HttpServer* server = HttpServer_init(atoi(port_str));
    Middleware* middleware = create_middleware(10); 


    globalCorsConfig = CorsConfig_init("*", "GET, POST, OPTIONS", "Content-Type, Authorization", 1);
    add_middleware(middleware, corsMiddlewareWrapper);

    add_middleware(middleware, errorHandlerMiddleware);
    HttpServer_start(server);

    CorseConfig_free(globalCorsConfig);
    free_middleware(middleware);
    Route_cleanup();
    HttpServer_stop(server);

    return 0;
}
