#ifndef MONGODBBSON_H_
#define MONGODBBSON_H_

#include <stdio.h>
#include <stdlib.h>
#include <bson/bson.h>

int init_movie();
int init_serie(bson_t **document);
int josn_tobson(char *json, bson_t **bson);
#endif