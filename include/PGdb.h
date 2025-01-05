#ifndef PGDB_H
#define PGDB_H

#include <libpq-fe.h>

typedef struct {
    PGconn* conn; 
} PGdb;

PGdb* PGdb_connect(const char* conninfo); 
void PGdb_disconnect(PGdb* db);          
PGresult* PGdb_query(PGdb* db, const char* query); 
void PGdb_freeResult(PGresult* result); 
#endif
