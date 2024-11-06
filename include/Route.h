// Route.h

#ifndef ROUTE_H
#define ROUTE_H

#include "HttpParser.h"
#include "Middleware.h"

// Route handler function pointer type
typedef void (*RouteHandler)(Request* req, Response* res);

typedef struct {
    char method[8];
    char path[256];
    RouteHandler handler;
    Middleware* middleware;
} Route;

// Macro to define a route and allow the handler function to follow directly
#define route(method, path, func, ...) \
    void func(Request* req, Response* res); \
    __attribute__((constructor)) \
    static void register_##func(void) { \
        Middleware *middleware = NULL; \
        if (sizeof((int[]){__VA_ARGS__}) / sizeof(int) > 0) { \
            middleware = create_middleware(10); \
            __VA_ARGS__; \
        } \
        Route_register(#method, path, func, middleware); \
    } \
    void func(Request* req, Response* res)


void Route_register(const char* method, const char* path, RouteHandler handler, Middleware* middleware);
RouteHandler Route_findHandler(const char* method, const char* path, Request *req, Response *res);
void Route_init();
void Route_cleanup();

#endif // ROUTE_H
