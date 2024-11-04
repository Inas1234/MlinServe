// Route.c

#include "../include/Route.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ROUTES 100

static Route routes[MAX_ROUTES];
static int route_count = 0;

void Route_register(const char* method, const char* path, RouteHandler handler) {
    if (route_count < MAX_ROUTES) {
        strncpy(routes[route_count].method, method, sizeof(routes[route_count].method) - 1);
        strncpy(routes[route_count].path, path, sizeof(routes[route_count].path) - 1);
        routes[route_count].handler = handler;
        route_count++;
    } else {
        fprintf(stderr, "Max routes reached. Cannot register route: %s %s\n", method, path);
    }
}

RouteHandler Route_findHandler(const char* method, const char* path) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].method, method) == 0 && strcmp(routes[i].path, path) == 0) {
            return routes[i].handler;
        }
    }
    return NULL; // No matching route found
}

void Route_init() {
    route_count = 0;
}

void Route_cleanup() {
    route_count = 0;
}
