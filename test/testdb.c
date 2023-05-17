#include "./../include/test/testdb.h"

int test_str_to_bson() {
    char  *string;
    bson_t *bson;
    char *json = "{\"name\": {\"first\":\"Grace\", \"last\":\"Hopper\"}}";
    josn_tobson(json, &bson);
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
    //init_movie();
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
        insert_document(client, "maboke", "serie_test", document);
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
        josn_tobson("{\"title\" : \"Groupe Kin Malebo - Molongo Molayi 1-2 (Théâtre Congolais) (2008)\" }", &selector);

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
        josn_tobson("{ \"title\": { \"$regex\" : \".*(T|t)h(é|e)(a|â)tre.*(C|c)(O|o)(N|n)(G|g)(O|o)(L|l).*\"}}", &selector);
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
        josn_tobson("{\"title\" : \"Groupe Kin Malebo - Molongo Molayi 1-2 (Théâtre Congolais) (2008)\" }", &selector);
        if(selector != NULL) {
            delete_document(client,"maboke", "serie_test", selector);
            bson_free(selector);
        }
        free_mongo_client(client);
    }
    return 0;
}