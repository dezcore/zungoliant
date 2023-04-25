#include "./../include/json.h"

int printJson(json_object *obj) {
    struct json_object_iterator it;
	struct json_object_iterator itEnd;

    if(obj != NULL) {
        //it = json_object_iter_init_default();
        it = json_object_iter_begin(obj);
	    itEnd = json_object_iter_end(obj);

        while(!json_object_iter_equal(&it, &itEnd)) {
		    printf("%s\n", json_object_iter_peek_name(&it));
		    printf("%s\n", json_object_to_json_string(json_object_iter_peek_value(&it)));
		    json_object_iter_next(&it);
	    }
    }

    return 0;
}

int getValue(json_object *obj, char *key, char **str) {
    json_object *target_obj;
    if(obj != NULL) {
        target_obj = json_object_object_get(obj, key);
        const char* value = json_object_get_string(target_obj);
        *str = (char *)realloc(*str, strlen(value) + 1);
        sprintf(*str, "%s", value);
        //json_object_object_get_ex(obj, key, &target_obj);
    }
    return 0;
}

json_object* getJson(char *str) {
    struct json_object *new_obj = NULL;

    if(str != NULL) {
        new_obj = json_tokener_parse(str);
    }
    //json_object_put(new_obj);
    return new_obj;
}