#include <stdio.h>
#include "../include/Middleware.h"

Middleware *create_middleware(int capacity) {
    Middleware *middleware = (Middleware*)malloc(sizeof(Middleware));
    middleware->capacity = capacity;
    middleware->count = 0;
    middleware->functions = malloc(sizeof(Middleware) * capacity);
    return middleware;
}

void free_middleware(Middleware *middleware) {
    free(middleware->functions);
    free(middleware);
}

int add_middleware(Middleware *middleware, MiddlewareFunc func){
    if (middleware->count >= middleware->capacity) {
        return -1;  
    }
    middleware->functions[middleware->count++] = func;
    return 0;
}

int execute_middleware(Middleware *middleware, Request *req, Response *res) {
    for (int i = 0; i < middleware->count; i++) {
        int result = middleware->functions[i](req, res);
        if (result != 0) {
            return result;  
        }
    }
    return 0;  
}



