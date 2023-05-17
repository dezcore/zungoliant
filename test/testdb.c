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

int test_insert_document() {
    char *str;
    bson_t *document = bson_new();
    mongoc_client_t *client = NULL;

    init_mongo_client(&client);
    init_serie(&document);

    str = bson_as_canonical_extended_json(document, NULL);
    printf("%s\n", str);
    /*
    * Clean up allocated bson documents.
    */
    bson_free(str);
    bson_destroy(document);
    free_mongo_client(client);
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

int test_matching_title() {
    ARRAY *array = NULL;
    File *titles_fifo = NULL;
    Element *title = NULL;
    titles_fifo = init();
    
    if(titles_fifo != NULL) {
        init_fifo(&titles_fifo, "/data/file/titles");
        init_file_to_array("/data/file/titles_regex", &array);
        //print_array(array);
        while(0 < titles_fifo->size) {
            title = pop(titles_fifo);
            for(int i = 0; i < array->length; i++) {
                if(match_pattern(title->value, array->elements[i])) {
                    displayElement(title);
                }
            }
            freeElement(title);
            title = NULL;
        }
        freeFile(titles_fifo);
        free_array(array);
    }
    return 0;
}