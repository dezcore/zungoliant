#ifndef JSON_H_
#define JSON_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>

int getValue(struct  json_object *obj, char *key, char **str);
struct json_object* getJson(char *str);
struct json_object* getObj(struct  json_object *obj, char *field);
struct json_object* getObj_rec(struct json_object *obj, char *fields);
#endif