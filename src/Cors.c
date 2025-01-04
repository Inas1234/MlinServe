#include "../include/Cors.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

CorsConfig* CorsConfig_init(const char* allowOrigin, const char* allowMethods, const char* allowHeaders, int allowCredentials) {
    CorsConfig* config = (CorsConfig*)malloc(sizeof(CorsConfig));
    if (config == NULL) {
        return NULL;
    }

    config->allowOrigin = allowOrigin;
    config->allowMethods = allowMethods;
    config->allowHeaders = allowHeaders;
    config->allowCredentials = allowCredentials;

    return config;
}


void CorseConfig_free(CorsConfig* config) {
    if (config != NULL){
        free(config);
    }
}

int corsMiddleware(Request* req, Response* res, CorsConfig* config) {
    if (!config){
        return 0;
    }
    Response_addHeader(res, "Access-Control-Allow-Origin: *");
    if (config->allowMethods){
        char methodHeader[256];
        snprintf(methodHeader, sizeof(methodHeader), "Access-Control-Allow-Methods: %s", config->allowMethods);
        Response_addHeader(res, methodHeader);
    }
    if (config->allowHeaders) {
        char headersHeader[256];
        snprintf(headersHeader, sizeof(headersHeader), "Access-Control-Allow-Headers: %s", config->allowHeaders);
        Response_addHeader(res, headersHeader);
    }
    if (config->allowCredentials) {
        Response_addHeader(res, "Access-Control-Allow-Credentials: true");
    }

    if (strcmp(req->method, "OPTIONS") == 0) {
        Response_setStatus(res, 200);
        Response_setBody(res, "");
        Response_send(res);
        return 1; 
    }


    return 0;


}