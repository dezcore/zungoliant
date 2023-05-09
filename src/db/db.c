#include "./../include/db/db.h"

int ping_mongodb(mongoc_client_t *client) {
  bson_t *command = NULL;
  mongoc_database_t *database = NULL;

  // Get a handle on the "admin" database.
  database = mongoc_client_get_database(client, "admin");

  if(database != NULL) {
    //Ping the database.
    command = BCON_NEW("ping", BCON_INT32(1));

    if(mongoc_database_command_simple(database, command, NULL, &reply, &error)) {
      printf("Pinged your deployment. You successfully connected to MongoDB!\n");
    } else {
      // Error condition.
      printf("Error: %s\n", error.message);
    }
  }

  //Perform Cleanup.
  bson_destroy(&reply);
  bson_destroy(command);
  mongoc_database_destroy(database);

  return 0;
}

int init_mongo_client(mongoc_client_t **client) {
  bson_error_t error = {0};
  mongoc_server_api_t *api = NULL;
  //const char *uri_string = "mongodb://localhost:27017";

  //Initialize the MongoDB C Driver.
  mongoc_init();
  
  // Replace the <connection string> with your MongoDB deployment's connection string.
  *client = mongoc_client_new("<connection string>");
  //*client = mongoc_client_new_from_uri (uri);

  // Set the version of the Stable API on the client.
  api = mongoc_server_api_new (MONGOC_SERVER_API_V1);

  if(!mongoc_client_set_server_api (client, api, &error)) {
	  // Error condition.
	  printf("Error: %s\n", error.message);
	  return 0;
  }
  
  return 0;
}

int free_mongo_client(mongoc_client_t *client) {
  //Perform Cleanup.
  mongoc_client_destroy (client);
  mongoc_cleanup();
  return 0;
}
