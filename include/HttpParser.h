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
    int status_code;
    char *headers;
    char *body;
} Response;


#define SEND_TEXT_RESPONSE(res, status_code, body_content) \
    Response_setStatus(res, status_code);                  \
    Response_addHeader(res, "Content-Type: text/plain");   \
    Response_setBody(res, body_content);                   \
    Response_send(res);                                    \
    Response_free(res);

#define SEND_JSON_RESPONSE(res, status_code, json_content)    \
    Response_setStatus(res, status_code);                     \
    Response_addHeader(res, "Content-Type: application/json");\
    Response_setBody(res, json_content);                      \
    Response_send(res);                                       \
    Response_free(res);


Request* HttpParser_parseRequest(const char *raw_request);

void HttpParser_freeRequest(Request *request);

Response* Response_init(int client_socket);

void Response_setStatus(Response *response, int status_code);

void Response_addHeader(Response *response, const char *header);

void Response_setBody(Response *response, const char *body);

void Response_send(Response *response);

void Response_free(Response *response);

#endif 
