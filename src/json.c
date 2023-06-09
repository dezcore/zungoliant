#include "./../include/json.h"

int iterObj(struct json_object *obj) {
    unsigned int ii;
    struct json_object *val;
    
    if(obj != NULL) {
        //int parsed_len = json_object_get_string_len(obj);
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

int json_tofile(const char *outfile,struct json_object *jso) {
    int rv;

    if(outfile != NULL) {
        rv = json_object_to_file(outfile, jso);
        //rv = json_object_to_file_ext(outfile2, jso, JSON_C_TO_STRING_PRETTY);
        printf("%s: json_object_to_file(%s, jso)=%d\n", (rv == 0) ? "OK" : "FAIL", outfile, rv);
    }

    return 0;
}

long sizeof_file(char* fileName) {
    long size = 0;
    FILE * file = fopen(fileName, "rb");

    if(file != NULL) {
        fseek(file, 0L, SEEK_END);
        size = ftell(file);
        //You can then seek back
        fseek(file, 0L, SEEK_SET);
        //rewind(file);
    }
    fclose(file);
    return size;
}

long file_tojson_byfd(char* fileName, struct json_object **json) {
    int fd;
    long size = sizeof_file(fileName);

    if(size < 86117) {
        fd = open(fileName, O_RDONLY);
        if(fd ==-1) {
            // print which type of error have in a code
            printf("Error Number % d\n", errno);     
            // print program detail "Success or failure"
            perror("Program");                
        }

        lseek(fd, 0, SEEK_SET);
        *json = json_object_from_fd(fd);

        if(close(fd) < 0) {
            perror("c1");
            exit(1);
        }
    }

    const char* error = json_util_get_last_err();
    
    if(error != NULL) {
        printf("Error : %s, fileSize : %ld\n", error, size);
    }

    return size;
}

long file_tojson(char* fileName, struct json_object **json) {
    long size = 0;

    if(fileName != NULL) {
       size = file_tojson_byfd(fileName, &(*json)); 
    }

    return size;
}

long detect_oversize_json(char* fileName, struct json_object **json) {
    int fd;
    long size = sizeof_file(fileName);

    fd = open(fileName, O_RDONLY);
    if(fd ==-1) {
        // print which type of error have in a code
        printf("Error Number % d\n", errno);     
        // print program detail "Success or failure"
        perror("Program");                
    }

    lseek(fd, 0, SEEK_SET);
    *json = json_object_from_fd(fd);
    
    if(close(fd) < 0) {
        perror("c1");
        exit(1);
    }

    const char* error = json_util_get_last_err();

    if(error != NULL) {
        printf("Error : %s, fileSize : %ld, fileName : %s\n", error, size, fileName);
        printf("VALUE : %s\n", json_object_get_string(*json));
    }
    
    return size;
}
