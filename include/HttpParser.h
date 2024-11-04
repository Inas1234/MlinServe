// HttpParser.h

#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <stdlib.h>

typedef struct {
    char method[8];
    char path[256];
    char http_version[16];
    char *headers;
    char *body;
} Request;

typedef struct {
    int client_socket;
} Response;

// Parse the HTTP request from a raw string
Request* HttpParser_parseRequest(const char *raw_request);

// Free the allocated memory for an HttpRequest
void HttpParser_freeRequest(Request *request);

#endif // HTTPPARSER_H
