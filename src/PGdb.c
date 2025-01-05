// PGdb.c
#include "../include/PGdb.h"
#include <stdio.h>
#include <stdlib.h>

PGdb* PGdb_connect(const char* conninfo) {
    PGdb* db = (PGdb*)malloc(sizeof(PGdb));
    if (!db) {
        fprintf(stderr, "Failed to allocate memory for PGdb structure.\n");
        return NULL;
    }

    db->conn = PQconnectdb(conninfo);
    if (PQstatus(db->conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(db->conn));
        PQfinish(db->conn);
        free(db);
        return NULL;
    }

    printf("Database connected successfully.\n");
    return db;
}

void PGdb_disconnect(PGdb* db) {
    if (db) {
        if (db->conn) {
            PQfinish(db->conn);
        }
        free(db);
        printf("Database connection closed.\n");
    }
}

PGresult* PGdb_query(PGdb* db, const char* query) {
    if (!db || !db->conn) {
        fprintf(stderr, "Database connection is not initialized.\n");
        return NULL;
    }

    PGresult* result = PQexec(db->conn, query);
    if (PQresultStatus(result) != PGRES_TUPLES_OK && PQresultStatus(result) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Query execution failed: %s\n", PQerrorMessage(db->conn));
        PQclear(result);
        return NULL;
    }

    return result;
}

void PGdb_freeResult(PGresult* result) {
    if (result) {
        PQclear(result);
    }
}
