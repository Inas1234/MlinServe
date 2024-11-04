// HttpParser.c

#include "../include/HttpParser.h"
#include <string.h>
#include <stdio.h>

Request* HttpParser_parseRequest(const char *raw_request) {
    Request *request = (Request*)malloc(sizeof(Request));
    if (!request) {
        perror("Failed to allocate memory for Request");
        return NULL;
    }

    request->headers = NULL;
    request->body = NULL;

    sscanf(raw_request, "%s %s %s", request->method, request->path, request->http_version);

    char *header_start = strstr(raw_request, "\r\n") + 2;
    char *body_start = strstr(header_start, "\r\n\r\n");

    if (body_start) {
        size_t header_length = body_start - header_start;
        request->headers = (char*)malloc(header_length + 1);
        strncpy(request->headers, header_start, header_length);
        request->headers[header_length] = '\0';

        request->body = strdup(body_start + 4); 
    } else {
        request->headers = strdup(header_start);
    }

    return request;
}

void HttpParser_freeRequest(Request *request) {
    if (request) {
        if (request->headers) free(request->headers);
        if (request->body) free(request->body);
        free(request);
    }
}
