#ifndef DB_H_
#define DB_H_

#include <mongoc/mongoc.h>
#include "./mongodb_bson.h"
//#include <libmongoc-1.0/mongoc.h>
//#include "./../include/utility.h"

int print_bson(bson_t *bson);
int print_cursor(mongoc_cursor_t *cursor);
int ping_mongodb(mongoc_client_t *client);
int free_mongo_client(mongoc_client_t *client);
int init_mongo_client(mongoc_client_t **client);
int get_collection(mongoc_client_t *client, char *dbName, char *collection);
int create_collection(mongoc_client_t *client, char *dbName, char *collectionName);
int delete_document(mongoc_client_t *client, char *dbName, char *collectionName, bson_t *doc);
int insert_document(mongoc_client_t *client, char *dbName, char *collection, bson_t *to_insert);
int update_document(mongoc_client_t *client, char *dbName, char *collection, bson_t *selector, bson_t *update);
int find_document(mongoc_client_t *client, char *dbName, char *collection, bson_t *selector,  mongoc_cursor_t **cursor);
#endif