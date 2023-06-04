#ifndef MONGODBBSON_H_
#define MONGODBBSON_H_

#include <stdio.h>
#include <stdlib.h>
#include <json.h>

#include <bson/bson.h>

#include "db.h"
#include "../utility.h"

typedef struct _CAST {
    STR_ARRAY *actors;
    STR_ARRAY *awards;
} CAST;

typedef struct _STUDIO {
    char *name;
    char * city;
    char *country;
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
    char *year;
    DIRECTOR *director;
    DIRECTOR *producer;
    STUDIO *studio;
    //CAST *cats;
    STR_ARRAY *contentTag;
    KEY_VALUE_ARRAY *key_value_array;
    SEASON_ARRAY *seasons;
} SERIE;

int init_movie();
int free_str(STR *str);
int free_serie(SERIE *serie);
int print_serie(SERIE *serie);
int free_studio(STUDIO *studio);
int init_video_struct(VIDEO *video);
int free_video_struct(VIDEO *video);
int free_director(DIRECTOR *director);
int free_season_struct(SEASON *season);
int init_studio_struct(STUDIO *studio);
int free_key_value(KEY_VALUE *key_value);
int init_key_value(KEY_VALUE *key_value);
int print_video(VIDEO *video, char *tabs);
int set_video_url(VIDEO *video, char *url);
int json_tobson(char *json, bson_t **bson);
int set_serie_year(SERIE *serie, char *year);
int init_director_struct(DIRECTOR *director);
int set_video_title(VIDEO *video, char *title);
int set_season_date(SEASON *season, char *date);
int free_video_array_struct(VIDEO_ARRAY *array);
int init_serie_default_parameters(SERIE *serie);
int set_video_length(VIDEO *video, char *length);
int set_season_title(SEASON *season, char *title);
int free_season_array_struct(SEASON_ARRAY *array);
int bson_to_serie(SERIE *serie, bson_t *document);
int set_video_summary(VIDEO *video, char *summary);
int serie_to_bson(bson_t **document, SERIE *serie);
int set_video_category(VIDEO *video, char *category);
int set_season_summary(SEASON *season, char *summary);
int serie_to_set_bson(bson_t **document, SERIE *serie);
int free_key_value_array_struct(KEY_VALUE_ARRAY *array); 
int init_season_struct(SEASON *season, size_t videoLen);
int exist_season(char *title, struct json_object *serie);
int set_key_value_value(KEY_VALUE *key_value, char *value);
int print_studio(STUDIO *studio, char *tabs, char *subtabs);
int save_video(struct json_object *video, const char *title);
int set_video_censor_rating(VIDEO *video, char *censor_rating);
int init_video_array_struct(VIDEO_ARRAY *array, size_t length);
int set_key_value(KEY_VALUE *key_value, char *key, char *value);
int resize_video_array_struct(VIDEO_ARRAY *array, size_t length);
int print_director(DIRECTOR *director, char *tabs, char *subtabs);
int print_array_video(VIDEO_ARRAY *array, char *tabs, char* subtabs);
int init_key_value_array_struct(KEY_VALUE_ARRAY *array, size_t length);
int resize_key_value_array_struct(KEY_VALUE_ARRAY *array, size_t length);
int print_key_value(KEY_VALUE *key_value, char *kv_tabs, char *kv_subtabs);
int init_season_array_struct(SEASON_ARRAY *array, size_t length, size_t videosLen);
int resize_season_array_struct(SEASON_ARRAY *array, size_t length,  size_t videoLen);
int print_season(SEASON *season, char *tabs, char *videos_tabs, char *videos_subtabs);
int set_seson(SEASON *season, char *title, char *date, char *summary, VIDEO_ARRAY *videos);
int set_director(DIRECTOR *director, char *name, char *startYear, char *endYear, char *bithYear);
int set_serie_default_parameters(SERIE *serie, int numb_of_keys,  int seasons,  int episodes, int tags);
int exist_serie(mongoc_client_t *client, bson_t *selector, char *dbName, char *documentName, SERIE *serie);
int print_array_key_value(KEY_VALUE_ARRAY *array, char *tabs, char* subtabs, char *kv_tabs, char *kv_subtabs);
int print_array_season(SEASON_ARRAY *array, char *tabs, char* subtabs, char *season_tabs, char *season_subtabs);
int set_video(VIDEO *video, char *title, char *category, char *summary, char *url, char *length, char *censor_rating);
int init_serie_struct(SERIE *serie, size_t keys_values_size, size_t number_of_season, size_t number_of_episodes, int content_tags);
int set_studio(STUDIO *studio, char *name, char *country, char *city, char *fonder, char *startYear, char *endYear, char *bithYear);
#endif