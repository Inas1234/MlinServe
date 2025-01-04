#ifndef CORS_H
#define CORS_H

#include "HttpParser.h"

typedef struct
{
    const char* allowOrigin;
    const char* allowMethods;
    const char* allowHeaders;
    int allowCredentials;
} CorsConfig;


CorsConfig* CorsConfig_init(const char* allowOrigin, const char* allowMethods, const char* allowHeaders, int allowCredentials);
void CorseConfig_free(CorsConfig* config);

int corsMiddleware(Request* req, Response* res, CorsConfig* config);

#endif