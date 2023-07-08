#ifndef JSON_H_
#define JSON_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

struct json_object* getJson(char *str);
long file_tojson(char* fileName, struct json_object **json);
int getValue(struct  json_object *obj, char *field, char **str);
struct json_object* getObj(struct  json_object *obj, char *field);
long detect_oversize_json(char* fileName, struct json_object **json);
struct json_object* getObj_rec(struct json_object *obj, char *fields);
#endif