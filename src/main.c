#include "../include/HttpServer.h"
#include "../include/Route.h"
#include "../include/Cors.h"
#include "../include/Env.h"
#include "../include/PGdb.h"
#include <string.h>
#include <stdio.h>


CorsConfig* globalCorsConfig;
PGdb* db;

int logRequestMiddleware(Request* req, Response* res) {
    printf("Request received: %s %s\n", req->method, req->path);
    return 0;  
}

route(GET, "/login", hello, add_middleware(middleware, logRequestMiddleware));
void hello(Request* req, Response* res) {
    const char* query = "SELECT * FROM users;";
    PGresult* result  = PGdb_query(db, query);
    if (!result) {
        SEND_ERROR_RESPONSE(res, 500, "Database query failed");
        return;
    }

    int rows = PQntuples(result);
    char response_body[1024] = "Users:\n";
    for (int i = 0; i < rows; i++) {
        char row[128];
        snprintf(row, sizeof(row), "ID: %s, Name: %s\n", PQgetvalue(result, i, 0), PQgetvalue(result, i, 1));
        strncat(response_body, row, sizeof(response_body) - strlen(response_body) - 1);
    }

    PGdb_freeResult(result);

    SEND_TEXT_RESPONSE(res, 200, response_body);
}




int corsMiddlewareWrapper(Request* req, Response* res) {
    return corsMiddleware(req, res, globalCorsConfig);
}


int main() {
    load_env();

    const char* port_str = get_env("SERVER_PORT", "8080");
    const char* conninfo = get_env("DB_CONN", "host=localhost dbname=test user=postgres password=secret");
    db = PGdb_connect(conninfo);
    if (!db) {
        fprintf(stderr, "Failed to connect to the database. Exiting.\n");
        return 1;
    }

    HttpServer* server = HttpServer_init(atoi(port_str));
    Middleware* middleware = create_middleware(10); 


    globalCorsConfig = CorsConfig_init("*", "GET, POST, OPTIONS", "Content-Type, Authorization", 1);
    add_middleware(middleware, corsMiddlewareWrapper);

    add_middleware(middleware, errorHandlerMiddleware);
    HttpServer_start(server);

    CorseConfig_free(globalCorsConfig);
    PGdb_disconnect(db);
    free_middleware(middleware);
    Route_cleanup();
    HttpServer_stop(server);

    return 0;
}
