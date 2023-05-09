#ifndef DB_H_
#define DB_H_
#include <mongoc/mongoc.h>
#include "./../include/utility.h"

int ping_mongodb(mongoc_client_t *client);
int free_mongo_client(mongoc_client_t *client);
int init_mongo_client(mongoc_client_t **client);
#endif