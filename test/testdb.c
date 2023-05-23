#include "./../include/test/testdb.h"

int test_str_to_bson() {
    char  *string;
    bson_t *bson;
    char *json = "{\"name\": {\"first\":\"Grace\", \"last\":\"Hopper\"}}";
    json_tobson(json, &bson);
    string = bson_as_canonical_extended_json (bson, NULL);
    printf ("%s\n", string);
    bson_free(string);
    return 0;
}

int test_ping_mongodb() {
    printf("Test_ping_mongodb : \n");
    mongoc_client_t *client = NULL;
    init_mongo_client(&client);
    ping_mongodb(client);
    //get_collection(client, "maboke", "view");
    //insert_document(client, "maboke", "test");
    init_movie();
    //test_zjosn();
    free_mongo_client(client);
    //while(1);
    return 0;
}

int test_insert_document(SERIE *serie) {
    bson_t *document = bson_new();
    mongoc_client_t *client = NULL;

    init_mongo_client(&client);
    serie_to_bson(&document, serie);
    
    if(document != NULL && client != NULL) {
        //print_bson(document);
        insert_document(client, "maboke", "serie", document);
    }

    bson_destroy(document);
    free_mongo_client(client);
    return 0;
}

int test_matching_title() {
    SERIE *serie = NULL;
    ARRAY *array = NULL;
    File *titles_fifo = NULL;
    Element *title = NULL;
    size_t keysLen = 1;
    char *keys[] = {"title", "img", "category", "summary"};

    titles_fifo = init();

    if(titles_fifo != NULL) {
        init_fifo(&titles_fifo, "/data/file/titles");
        init_file_to_array("/data/file/titles_regex", &array);

        //print_array(array);
        //display(titles_fifo);
        while(0 < titles_fifo->size) {
            title = pop(titles_fifo);
            for(int i = 0; i < array->length; i++) {
                if(match_pattern(title->value, array->elements[i])) {
                    serie = malloc(sizeof(*serie));
                    if(serie != NULL) {
                        init_serie_struct(serie, keysLen);
                        add_value(&(serie)->keys, keys[0], 0);
                        add_value(&(serie)->values, title->value, 0);
                        test_insert_document(serie);
                        //print_serie(serie);
                        free_serie(serie);
                    } else {
                        displayElement(title);
                    }
                    
                    break;
                }
            }
            freeElement(title);
            title = NULL;
            serie = NULL;
        }

        freeFile(titles_fifo);
       
        free_array(array);
    }

    return 0;
}

int test_find_document() {
    bson_t *selector;
    mongoc_cursor_t *cursor = NULL;
    mongoc_client_t *client = NULL;

    init_mongo_client(&client);
    if(client != NULL) {
        json_tobson("{\"title\" : \"Groupe Kin Malebo - Molongo Molayi 1-2 (Théâtre Congolais) (2008)\" }", &selector);

        if(selector != NULL) {
           
            find_document(client, "maboke", "serie_test", selector, &cursor);
            if(cursor != NULL) {
                print_cursor(cursor);
                bson_free(cursor);
            }
            //print_bson(selector);
            bson_destroy(selector);
        }
        free_mongo_client(client);
    }
    return 0;
}

int test_find_document_by_regex() {
    bson_t *selector;
    mongoc_cursor_t *cursor = NULL;
    mongoc_client_t *client = NULL;

    init_mongo_client(&client);
    if(client != NULL) {
        json_tobson("{ \"title\": { \"$regex\" : \".*(T|t)h(é|e)(a|â)tre.*(C|c)(O|o)(N|n)(G|g)(O|o)(L|l).*\"}}", &selector);
        if(selector != NULL) {
            find_document(client, "maboke", "serie_test", selector, &cursor);
            if(cursor != NULL) {
                print_cursor(cursor);
                bson_free(cursor);
            }
            //print_bson(selector);
            bson_destroy(selector);
        }
        free_mongo_client(client);
    }
    return 0;
}

int test_delete_document() {
    bson_t *selector;
    mongoc_client_t *client = NULL;

    init_mongo_client(&client);
    if(client != NULL) {
        json_tobson("{\"title\" : \"Groupe Kin Malebo - Molongo Molayi 1-2 (Théâtre Congolais) (2008)\" }", &selector);
        if(selector != NULL) {
            delete_document(client,"maboke", "serie_test", selector);
            bson_free(selector);
        }
        free_mongo_client(client);
    }
    return 0;
}

int test_update_document() {
    bson_t *selector, *update;
    mongoc_client_t *client = NULL;

    init_mongo_client(&client);
    if(client != NULL) {
        selector = BCON_NEW("title", BCON_UTF8("\"BILAN NÉGATIF\" EPISODE 9 ET FIN"));
        json_tobson("{\"$set\" : {\"contentTag\" : [\"testtag1\", \"testtag2\", \"testtag3\"]}}", &update); 

        if(selector != NULL && update != NULL) {
            update_document(client,"maboke", "serie_test", selector, update);
            //print_bson(selector);
            //print_bson(update);
            bson_free(update);
            bson_free(selector);
        }
        free_mongo_client(client);
    }
    return 0;
}

int test_match_patterns() {
    char *regex = NULL;
    bson_t *selector;
    mongoc_cursor_t *cursor = NULL;
    mongoc_client_t *client = NULL;
    File *fifo = malloc(sizeof(*fifo));

    fifo_init(fifo);
    init_mongo_client(&client);
    get_match("TOURBILLONS Ep5 | Film congolais 2023 | Sila Bisalu | SBproduction.", "[A-Za-z]+[ ]+[A-Za-z]+", fifo);//[^0-9 ]+ or [A-Za-z]+

    if(fifo != NULL && client != NULL) {
        //display(fifo);
        join_file_element(fifo, &regex, ".*", 1);

        if(regex != NULL) {
            //printf("Regex : %s\n", regex);
            selector =  BCON_NEW(
                "title", "{",
                    "$regex", BCON_UTF8(regex),
                    "$options", BCON_UTF8("i"),
                "}"
            );

            if(selector != NULL) {
                find_document(client, "maboke", "serie", selector, &cursor);
                if(cursor != NULL) {
                    print_cursor(cursor);
                    bson_free(cursor);
                }
                //print_bson(selector);
                bson_destroy(selector);
            }
            free(regex);
        }

        freeFile(fifo);
        free_mongo_client(client);
    }

    return 0;
}

int test_parse_date() {
    ARRAY *datePartArray = NULL;
    ARRAY *hoursPartArray = NULL;
    const char *date = "2014-01-01T08:15:39.736Z";

    parseDate((char*)date, "[0-9]{2}:[0-9]{2}:[0-9]{2}", "[0-9]{2}", &hoursPartArray);

    if(hoursPartArray != NULL) {
        print_array(hoursPartArray);
        free_array(hoursPartArray);   
    }

    parseDate((char *)date, "[0-9]{4}-[0-9]{2}-[0-9]{2}", "[0-9]+", &datePartArray);

    if(datePartArray != NULL) {
        print_array(datePartArray);
        free_array(datePartArray);   
    }

    return 0;
}

int test_exist() {
    struct json_object *serie;
    const char *title = "TOURBILLONS Ep1 | Film Congolais 2023 | Sila Bisalu | SBproduction.";
    //"TOURBILLONS Ep1 | Film Congolais 2023 | Sila Bisalu | SBproduction.";
    //"Saison 2 || VICTIME D’AMOUR || Ep 1 || Série Congolaise || DDtv || Janvier 2023"

    exist_serie((char*)title, &serie);

    if(serie != NULL) {
        //printJson(json);
        exist_season((char*)title, serie);
        json_object_put(serie);
    }

    return 0;
}

int test_video_struct() {
    VIDEO *video = malloc(sizeof(*video));
    if(video != NULL) {
        init_video_struct(video);
        set_video_title(video, "Hello world !");
        set_video_category(video,"Video category");
        set_video_summary(video, "Video summary");
        set_video_url(video, "Video url");
        set_video_length(video, "Video length");
        set_video_censor_rating(video, "Video censor_rating");
        print_video(video);
    }
    free_video_struct(video);
    return 0;
}

int test_video_array() {
    VIDEO_ARRAY *array  = malloc(sizeof(*array));
    if(array != NULL) {
        init_video_array_struct(array, 2);
    }
    free_video_array_struct(array);
    return 0;
}