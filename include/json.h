#ifndef JSON_H_
#define JSON_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json.h>

int getValue(json_object *obj, char *key, char **str);
json_object* getJson(char *str);
#endif