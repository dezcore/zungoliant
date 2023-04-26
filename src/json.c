#include "./../include/json.h"

int printJson(struct json_object *obj) {
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

int iterObj(struct json_object *obj) {
    unsigned int ii;
    struct json_object *val;

    if(obj != NULL) {
        for(ii = 0; ii < json_object_array_length(obj); ii++){
		    val = json_object_array_get_idx(obj, ii);
		    printf("%s%.2lf", (ii > 0) ? "," : "", json_object_get_double(val));
	    }
    }

    return 0;
}

int getValue(struct  json_object *obj, char *field, char **str) {
    const char* value;
    struct json_object *target_obj = NULL;

    if(obj != NULL) {
        //target_obj = json_object_object_get(obj, key);
        if(!json_object_object_get_ex(obj, field, &target_obj)) {
            printf("Field %s does not exist\n", field);
        } else {
            value = json_object_to_json_string_ext(target_obj, JSON_C_TO_STRING_PRETTY);
            //json_object_get_string(target_obj);
            //json_object_to_json_string(target_obj);
            *str = (char *)realloc(*str, strlen(value) + 1);
            sprintf(*str, "%s", value);
            json_object_put(target_obj);
        }
    }

    return 0;
}

struct json_object* getObj(struct json_object *obj, char *field) {
    struct json_object *target_obj = NULL;

    if(obj != NULL) {
        target_obj = json_object_object_get(obj, field);
    }

    return target_obj;
}

struct json_object* getObj_rec(struct json_object *obj, char *fields) { //fields example : "/arr/0/obj/2/obj1"
    struct json_object *target_obj = NULL;

    if(obj != NULL) {
        json_pointer_get(obj, fields, &target_obj);
        //json_pointer_getf(obj, &target_obj, "/%s/%d/%s/%d/%s", "arr", 0, "obj", 2, "obj2")
        //json_object_is_type(jo2, json_type_string)
    }
    return target_obj;
}

struct json_object* getJson(char *str) {
    struct json_object *new_obj = NULL;

    if(str != NULL) {
        new_obj = json_tokener_parse(str);
    }
    //json_object_put(new_obj);
    return new_obj;
}

int copyJson(struct json_object *src) {
    struct json_object *dst = NULL;
    if(src != NULL) {
        json_object_deep_copy(src, &dst, NULL);
    }
    return 0;
}

int sameJson(struct json_object *src) {
    struct json_object *dst = NULL;
    if(src != NULL) {
        return  json_object_equal(src, dst);
    }
    return 0;
}