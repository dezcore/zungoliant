#include "./../include/test/testdb.h"

int test_ping_mongodb() {
    printf("Test_ping_mongodb : \n");
    mongoc_client_t *client = NULL;
    init_mongo_client(&client);
    ping_mongodb(client);
    //get_collection(client, "maboke", "view");
    //insert_document(client, "maboke", "test");
    //init_serie();
    //test_zbcon();
    test_zjosn();
    free_mongo_client(client);
    //while(1);
    return 0;
}