// HttpParser.c

#include "../include/HttpParser.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

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

Response* Response_init(int client_socket) {
    Response *response = malloc(sizeof(Response));
    response->client_socket = client_socket;
    response->status_code = 200; 
    response->headers = strdup("Content-Type: text/plain\r\n"); 
    response->body = NULL;
    return response;
}

void Response_setStatus(Response *response, int status_code) {
    response->status_code = status_code;
}

void Response_addHeader(Response *response, const char *header) {
    size_t old_len = response->headers ? strlen(response->headers) : 0;
    size_t new_len = old_len + strlen(header) + 2; 
    response->headers = realloc(response->headers, new_len + 1);
    strcat(response->headers, header);
    strcat(response->headers, "\r\n");
}

void Response_setBody(Response *response, const char *body) {
    response->body = strdup(body);
}

void Response_send(Response *response) {
    char buffer[1024];
    int length = snprintf(buffer, sizeof(buffer),
                          "HTTP/1.1 %d OK\r\n%s\r\n%s",
                          response->status_code, response->headers,
                          response->body ? response->body : "");

    send(response->client_socket, buffer, length, 0);
    close(response->client_socket); 
}

void Response_free(Response *response) {
    if (response->headers) free(response->headers);
    if (response->body) free(response->body);
    free(response);
}

