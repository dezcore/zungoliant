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
        join_file_element(fifo, &regex, ".*", 1, -1);

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

int test_exist() {
    /*struct json_object *serie;
    const char *title = "TOURBILLONS Ep1 | Film Congolais 2023 | Sila Bisalu | SBproduction.";
    //"TOURBILLONS Ep1 | Film Congolais 2023 | Sila Bisalu | SBproduction.";
    //"Saison 2 || VICTIME D’AMOUR || Ep 1 || Série Congolaise || DDtv || Janvier 2023"
    exist_serie((char*)title, &serie);
    if(serie != NULL) {
        exist_season((char*)title, serie);
        json_object_put(serie);
    }*/

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
        print_video(video, "");
    }
    free_video_struct(video);
    return 0;
}

int test_set_video(VIDEO *video) {
    if(video != NULL) {
        set_video_title(video, "Hello world !");
        set_video_category(video,"Video category");
        set_video_summary(video, "Video summary");
        set_video_url(video, "Video url");
        set_video_length(video, "Video length");
        set_video_censor_rating(video, "Video censor_rating");
    }
    return 0;
}

int test_video_array() {
    VIDEO video;
    VIDEO_ARRAY *array  = malloc(sizeof(*array));
    if(array != NULL) {
        init_video_array_struct(array, 3);
        for(int i = 0; i < array->length; i++) {
            test_set_video(&(array->elements[i]));
        }
        print_array_video(array, "", "\t");
        resize_video_array_struct(array, array->length+1);
        video = array->elements[array->length-1];
        set_video(&video, "title", "category", "summary", "url", "length", "censor_rating");
        print_array_video(array, "", "\t");
    }
    free_video_array_struct(array);
    return 0;
}

int test_season_struct() {
    SEASON *season = malloc(sizeof(*season));
    if(season != NULL) {
        init_season_struct(season, 3);
        set_season_title(season, "Seson title");
        set_season_date(season, "Season date");
        set_season_summary(season, "Season summary");

        for(int i = 0; i < season->videos->length; i++) {
            test_set_video(&(season->videos->elements[i]));
        }
        print_season(season, "", "\t", "\t\t");
    }
    free_season_struct(season);
    return 0;
}

int test_key_value() {
    KEY_VALUE *key_value = malloc(sizeof(*key_value));
    if(key_value != NULL) {
        init_key_value(key_value);
        set_key_value(key_value, "key", "value");
        print_key_value(key_value, "", "\t");
    }
    free_key_value(key_value);
    return 0;
}

int test_str() {
    STR *str = malloc(sizeof(*str));
    if(str != NULL) {
        init_str_struct(str);
        set_str_value(str, "Hello world !");
        print_str(str, "", "\t");
    }
    free_str(str);
    return 0;
}

int test_str_array() {
    STR_ARRAY *array = malloc(sizeof(*array));
    if(array != NULL) {
        init_str_array_struct(array, 2);
        for(int i = 0; i < array->length; i++) {
            set_str_value(&(array->elements[i]), "Hello world !");
        }
        print_array_str(array, "", "\t", "\t", "\t\t");
    }
    free_str_array_struct(array);
    return 0;
}

int test_set_seson(SEASON *season) {
    if(season != NULL) {
        set_season_title(season, "Seson title");
        set_season_date(season, "2014-01-01T08:15:39.736Z");
        set_season_summary(season, "Season summary");

        for(int i = 0; i < season->videos->length; i++) {
            test_set_video(&(season->videos->elements[i]));
        }
    }
    return 0;
}

int set_str_array(STR_ARRAY *array) {
    if(array != NULL) {
        for(int i = 0; i < array->length; i++) {
            set_str_value(&(array->elements[i]), "Hello world !");
        }
    }
    return 0;
}

int test_set_key_value(KEY_VALUE *key_value, char *key, char *value) {
    if(key_value != NULL) {
        set_key_value(key_value, key, value);
    }
    return 0;
}

int set_season_array(SEASON_ARRAY *array) {
    if(array != NULL) {
        for(int i = 0; i < array->length; i++) {
            test_set_seson(&(array->elements[i]));
        }
    }
    return 0;
}

int test_season_array() {
    /*SEASON_ARRAY *array  = malloc(sizeof(*array));

    if(array != NULL) {
        init_season_array_struct(array, 2, 5); 
        for(int i = 0; i < array->length; i++) {
            test_set_seson(&(array->elements[i]));
        }
        print_array_season(array, "", "\t",  "\t\t", "\t\t\t");
        resize_season_array_struct(array, array->length + 1);
        
        set_seson(&(array->elements[array->length -1]) , "title", "2014-01-01T08:15:39.736Z", "summary", array->elements[0].videos);

        print_array_season(array, "", "\t",  "\t\t", "\t\t\t");

    }
    free_season_array_struct(array);*/
    return 0;
}

int set_key_value_array(KEY_VALUE_ARRAY *array) {
    if(array != NULL) {
        for(int i = 0; i < array->length; i++) {
            test_set_key_value(&(array->elements[i]), "title", "title value");
        }
    }
    return 0;
}

int test_key_value_array() {
   /*KEY_VALUE_ARRAY *array  = malloc(sizeof(*array));
    if(array != NULL) {
        init_key_value_array_struct(array, 2);
        for(int i = 0; i < array->length; i++) {
            test_set_key_value(&(array->elements[i]), "key", "value");
        }
        print_array_key_value(array,"", "\t", "\t", "\t\t") ;
    }
    free_key_value_array_struct(array);*/
    return 0;
}

int test_director() {
    DIRECTOR *director = malloc(sizeof(*director));
    if(director != NULL) {
        init_director_struct(director);
        set_director(director, "Director name","2014-01-01T08:15:39.736Z", "2014-01-01T08:15:39.736Z", "2014-01-01T08:15:39.736Z");
        print_director(director,  "", "\t");
    }
    free_director(director);
    return 0;
}

int test_studio() {
    STUDIO *studio = malloc(sizeof(*studio));
    if(studio != NULL) {
        init_studio_struct(studio);
        set_studio(studio, "Studio name", "Country", "City", "Fonder","2014-01-01T08:15:39.736Z", "EndYear", "2014-01-01T08:15:39.736Z");
        print_studio(studio, "", "\t");
    }
    free_studio(studio);
    return 0;
}

int test_set_studio(STUDIO *studio) {
    if(studio != NULL) {
        set_studio(studio, "Studio name", "Country", "City", "Fonder","2014-01-01T08:15:39.736Z", "2014-01-01T08:15:39.736Z", "2014-01-01T08:15:39.736Z");
    }
    return 0;
}

int test_create_serie(SERIE **res, int save) {
    SERIE *serie = malloc(sizeof(*serie));

    if(serie != NULL) {
        init_serie_default_parameters(serie);
        puts("test_create_seri");
        set_serie_default_parameters(serie, 2, 1, 2, 2);
        set_serie_year(serie, "2014-01-01T08:15:39.736Z"); //{ "$date": { "$numberLong": "1388560028000" } },
        set_director(serie->director, "Director name","2014-01-01T08:15:39.736Z", "2014-01-01T08:15:39.736Z", "2014-01-01T08:15:39.736Z");
        set_director(serie->producer, "Producer name","2028-01-01T08:15:39.736Z", "2024-01-01T08:15:39.736Z", "2023-01-01T08:15:39.736Z");
        test_set_studio(serie->studio);
        set_season_array(serie->seasons);
        set_str_array(serie->contentTag);
        set_key_value_array(serie->key_value_array);
        //print_serie(serie);
    }

    if(save)
        *res = serie;
    else
        free_serie(serie);
    return 0;
}

int test_serie_to_bson() {
    bson_t *document = bson_new();
    SERIE *serie = NULL;

    test_create_serie(&serie, 1);

    if(serie != NULL) {
        serie_to_bson(&document, serie);
        print_bson(document);
    }

    bson_destroy(document);
    free_serie(serie);
    return 0;
}

int test_bson_to_serie() {
    SERIE *serie = NULL;
    bson_t *document = bson_new();
    SERIE *serie1 = malloc(sizeof(*serie1));

    test_create_serie(&serie, 1);

    if(serie != NULL) {
        init_serie_default_parameters(serie1);
        resize_season_array_struct(serie->seasons, 2, 1);        
        test_set_seson(&(serie->seasons->elements[1]));
        serie_to_bson(&document, serie); 
        bson_to_serie(serie1, document);
        print_serie(serie1);
    }

    bson_destroy(document);
    free_serie(serie);
    free_serie(serie1);
    return 0;
}

int test_parse_date() {
    STR_ARRAY *datePartArray =(STR_ARRAY *) malloc(sizeof(*datePartArray));
    STR_ARRAY *hoursPartArray = (STR_ARRAY *) malloc(sizeof(*hoursPartArray));
    const char *date = "2014-01-01T08:15:39.736Z";

    parseDate((char*)date, "[0-9]{2}:[0-9]{2}:[0-9]{2}", "[0-9]{2}", hoursPartArray);
    if(hoursPartArray != NULL) {
        print_array_str(hoursPartArray, "", "\t", "\t", "\t\t");
    }

    parseDate((char *)date, "[0-9]{4}-[0-9]{2}-[0-9]{2}", "[0-9]+", datePartArray);
    if(datePartArray != NULL) {
        print_array_str(datePartArray, "", "\t", "\t", "\t\t");
    }

    free_str_array_struct(datePartArray);
    free_str_array_struct(hoursPartArray);
    return 0;
}

int test_date() {
    char *res = NULL;
    const char *date= "1388560028000";
    timestamp_to_utc((char *)date, &res);
    if(res != NULL) {
        printf("Date : %s\n", res);
        free(res);
    }
    return 0;
}

int test_matching_title() {
    SERIE *serie = NULL;
    STR_ARRAY *array = NULL;
    Element *title = NULL;
    size_t keysLen = 1;
    File *titles_fifo = malloc(sizeof(*titles_fifo));
    //char *keys[] = {"title", "img", "category", "summary"};

    if(titles_fifo != NULL) {
        init_file_struct(titles_fifo);
        init_fifo(&titles_fifo, "/data/file/titles");
        init_file_to_array("/data/file/titles_regex", array);

        //print_array(array);
        //display(titles_fifo);
        while(0 < titles_fifo->size) {
            title = pop(titles_fifo);
            for(int i = 0; i < array->length; i++) {
                if(match_pattern(title->value, array->elements[i].value)) {
                    serie = malloc(sizeof(*serie));
                    if(serie != NULL) {
                        init_serie_struct(serie, keysLen, 0, 0, 0);
                        //add_value(&(serie)->keys, keys[0], 0);
                        //add_value(&(serie)->values, title->value, 0);
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
        free_str_array_struct(array);
    }

    return 0;
}

int test_title_regex() {
    Element *title = NULL;
    File *titles_fifo = malloc(sizeof(*titles_fifo));

    if(titles_fifo != NULL) {
        init_file_struct(titles_fifo);
        init_fifo(&titles_fifo, "/data/file/titles");
        while(0 < titles_fifo->size) {
            title = pop(titles_fifo);
            printf("Title : %s => numb sesason : %d\n", title->value, get_title_season(title->value));
            freeElement(title);
        }   
    }
    freeFile(titles_fifo);
    return 0;
}

int test_title_episode_regex() {
    Element *title = NULL;
    File *titles_fifo = malloc(sizeof(*titles_fifo));

    if(titles_fifo != NULL) {
        init_file_struct(titles_fifo);
        init_fifo(&titles_fifo, "/data/file/titles");
        //init_urls(&bot->urls_fifo, &urlsFileSrc);  

        while(0 < titles_fifo->size) {
            title = pop(titles_fifo);
            //get_title_episode(title->value);
            printf("Title : %s => numb episode : %d\n", title->value, get_title_episode(title->value));
            freeElement(title);
        }   
    }

    freeFile(titles_fifo);
    return 0;
}