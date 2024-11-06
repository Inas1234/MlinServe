#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#include "HttpParser.h"

// Define a type for middleware functions
typedef int (*MiddlewareFunc)(Request *req, Response *res);

// Define the Middleware struct to hold middleware functions
typedef struct Middleware {
    MiddlewareFunc *functions;
    int count;
    int capacity;
} Middleware;

// Function declarations
Middleware *create_middleware(int capacity);
void free_middleware(Middleware *middleware);
int add_middleware(Middleware *middleware, MiddlewareFunc func);
int execute_middleware(Middleware *middleware, Request *req, Response *res);

#endif
