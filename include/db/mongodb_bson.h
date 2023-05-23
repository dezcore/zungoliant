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
    VIDEO *elements;
    size_t length;
} VIDEO_ARRAY;

typedef struct _SEASON {
    char *title;
    char *date;
    char *summary;
    int number;
    VIDEO_ARRAY *videos;
} SEASON;

typedef struct _SEASON_ARRAY {
    SEASON *elements;
    size_t length;
} SEASON_ARRAY;
typedef struct _KEY_VALUE {
    char *key;
    char *value;
} KEY_VALUE;

typedef struct _KEY_VALUE_ARRAY {
    KEY_VALUE *elements;
    size_t length;
} KEY_VALUE_ARRAY;

typedef struct _SERIE {
    DIRECTOR *director;
    DIRECTOR *producer;
    //STUDIO *studio;
    //CAST *cats;
    //ARRAY *contentTag;
    KEY_VALUE_ARRAY *key_value_array;
    SEASON_ARRAY *seasons;
} SERIE;

int init_movie();
int free_serie(SERIE *serie);
int print_serie(SERIE *serie);
int init_video_struct(VIDEO *video);
int free_video_struct(VIDEO *video);
int free_director(DIRECTOR *director);
int free_season_struct(SEASON *season);
int free_key_value(KEY_VALUE *key_value);
int init_key_value(KEY_VALUE *key_value);
int print_video(VIDEO *video, char *tabs);
int set_video_url(VIDEO *video, char *url);
int json_tobson(char *json, bson_t **bson);
int init_director_struct(DIRECTOR *director);
int set_video_title(VIDEO *video, char *title);
int set_season_date(SEASON *season, char *date);
int free_video_array_struct(VIDEO_ARRAY *array);
int set_video_length(VIDEO *video, char *length);
int set_season_title(SEASON *season, char *title);
int free_season_array_struct(SEASON_ARRAY *array);
int set_video_summary(VIDEO *video, char *summary);
int serie_to_bson(bson_t **document, SERIE *serie);
int set_video_category(VIDEO *video, char *category);
int set_season_summary(SEASON *season, char *summary);
int free_key_value_array_struct(KEY_VALUE_ARRAY *array); 
int init_season_struct(SEASON *season, size_t videoLen);
int exist_serie(char *title, struct json_object **json);
int exist_season(char *title, struct json_object *serie);
int save_video(struct json_object *video, const char *title);
int set_video_censor_rating(VIDEO *video, char *censor_rating);
int init_video_array_struct(VIDEO_ARRAY *array, size_t length);
int set_key_value(KEY_VALUE *key_value, char *key, char *value);
int print_director(DIRECTOR *director, char *tabs, char *subtabs);
int print_array_video(VIDEO_ARRAY *array, char *tabs, char* subtabs);
int init_key_value_array_struct(KEY_VALUE_ARRAY *array, size_t length);
int print_key_value(KEY_VALUE *key_value, char *kv_tabs, char *kv_subtabs);
int init_season_array_struct(SEASON_ARRAY *array, size_t length, size_t videosLen);
int print_season(SEASON *season, char *tabs, char *videos_tabs, char *videos_subtabs);
int set_director(DIRECTOR *director, char *name, char *startYear, char *endYear, char *bithYear);
int print_array_key_value(KEY_VALUE_ARRAY *array, char *tabs, char* subtabs, char *kv_tabs, char *kv_subtabs);
int print_array_season(SEASON_ARRAY *array, char *tabs, char* subtabs, char *season_tabs, char *season_subtabs);
int init_serie_struct(SERIE *serie, size_t keys_values_size, size_t number_of_season, size_t number_of_episodes);
#endif