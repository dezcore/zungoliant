#ifndef MONGODBBSON_H_
#define MONGODBBSON_H_

#include <stdio.h>
#include <stdlib.h>
#include <json.h>

#include <bson/bson.h>
//#include "./db.h"
//#include "../array.h"
//#include "../yfields.h"
#include "../utility.h"

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
typedef struct _VIDEO {
    char *title;
    char *category;
    char *url;
    char *summary;
    char *length;
    char *censor_rating;
    //char *created_at;
    //char *upDated_at;
} VIDEO;

typedef struct _VIDEO_ARRAY {
    VIDEO **elements;
    size_t length;
} VIDEO_ARRAY;

typedef struct _SEASON {
    char *title;
    char *date;
    char *summary;
    int number;
    //List<Video> videos;
} SEASON;

typedef struct _SEASON_ARRAY {
    SEASON **elements;
    size_t length;
} SEASON_ARRAY;

typedef struct _SERIE {
    ARRAY *keys;
    ARRAY *values;
    DIRECTOR *director;
    DIRECTOR *pproducer;
    STUDIO *studio;
    CAST *cats;
    ARRAY *contentTag;
    //List<Season> seasons;
} SERIE;

int init_movie();
int free_serie(SERIE *serie);
int print_serie(SERIE *serie);
int print_video(VIDEO *video);
int init_video_struct(VIDEO *video);
int free_video_struct(VIDEO *video);
int set_video_url(VIDEO *video, char *url);
int json_tobson(char *json, bson_t **bson);
int set_video_title(VIDEO *video, char *title);
int free_video_array_struct(VIDEO_ARRAY *array);
int set_video_length(VIDEO *video, char *length);
int set_video_summary(VIDEO *video, char *summary);
int serie_to_bson(bson_t **document, SERIE *serie);
int set_video_category(VIDEO *video, char *category);
int init_serie_struct(SERIE *serie, size_t array_size);
int exist_serie(char *title, struct json_object **json);
int exist_season(char *title, struct json_object *serie);
int save_video(struct json_object *video, const char *title);
int set_video_censor_rating(VIDEO *video, char *censor_rating);
int init_video_array_struct(VIDEO_ARRAY *array, size_t length);
#endif