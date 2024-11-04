// Route.h

#ifndef ROUTE_H
#define ROUTE_H

#include "HttpParser.h"

// Route handler function pointer type
typedef void (*RouteHandler)(Request* req, Response* res);

typedef struct {
    char method[8];
    char path[256];
    RouteHandler handler;
} Route;

// Macro to define a route and allow the handler function to follow directly
#define route(method, path, func) \
    void func(Request* req, Response* res); \
    __attribute__((constructor)) \
    static void register_##func(void) { \
        Route_register(#method, path, func); \
    } \
    void func(Request* req, Response* res)

void Route_register(const char* method, const char* path, RouteHandler handler);
RouteHandler Route_findHandler(const char* method, const char* path);
void Route_init();
void Route_cleanup();

#endif // ROUTE_H
