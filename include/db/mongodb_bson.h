#ifndef MONGODBBSON_H_
#define MONGODBBSON_H_

#include <stdio.h>
#include <stdlib.h>
#include <bson/bson.h>
#include "../array.h"

typedef struct _CAST {
    ARRAY *actors;
    ARRAY *awards;
} CAST;

typedef struct _STUDIO {
    char *name;
    char * city;
    char *startYear;
    char *endYear;
    char *bithYear;
    char *fonder;
} STUDIO;

typedef struct _DIRECTOR {
    char *name;
    char * startYear;
    char *endYear;
    char *bithYear;
} DIRECTOR;

typedef struct _SERIE {
    ARRAY *keys;
    ARRAY *values;
    DIRECTOR *director;
    DIRECTOR *pproducer;
    STUDIO *studio;
    CAST *cats;
    ARRAY *contentTag;

} SERIE;

int init_movie();
int free_serie(SERIE *serie);
int print_serie(SERIE *serie);
int json_tobson(char *json, bson_t **bson);
int serie_to_bson(bson_t **document, SERIE *serie);
int init_serie_struct(SERIE *serie, size_t array_size);
#endif