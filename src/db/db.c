#include "./../../include/db/db.h"

int print_res(const bson_t *reply) {
  char *str;
  
  BSON_ASSERT(reply);
  str = bson_as_canonical_extended_json (reply, NULL);
  printf ("%s\n", str);
  bson_free (str);

  return 0;
} 
int ping_mongodb(mongoc_client_t *client) {
  bson_error_t error = {0};
  bson_t *command = NULL, reply;
  mongoc_database_t *database = NULL;

  /*
    * Get a handle on the database "db_name" and collection "coll_name"
  */
  database = mongoc_client_get_database(client, "maboke");
  //collection = mongoc_client_get_collection(client, "maboke", "serie");

  if(database != NULL) {
    /*
      * Do work. This example pings the database, prints the result as JSON and
      * performs an insert
    */
    command = BCON_NEW("ping", BCON_INT32(1));

    if(mongoc_database_command_simple(database, command, NULL, &reply, &error)) {
      printf("Pinged your deployment. You successfully connected to MongoDB!\n");
    } else {
      // Error condition.
      printf("Error*: %s\n", error.message);
    }
  }

  //Perform Cleanup.
  bson_destroy(&reply);
  bson_destroy(command);
  mongoc_database_destroy(database);

  return 0;
}

int init_mongo_client(mongoc_client_t **client) {
  mongoc_uri_t *uri;
  bson_error_t error = {0};
  const char *uri_string = "mongodb://root:secret@localhost:27017/?authMechanism=DEFAULT";

  //Initialize the MongoDB C Driver.
  mongoc_init();

  /*
    * Safely create a MongoDB URI object from the given string
  */
  uri = mongoc_uri_new_with_error(uri_string, &error);
  
  if(!uri) {
    fprintf (stderr,
      "failed to parse URI: %s\n"
      "error message:       %s\n",
      uri_string,
      error.message);
    return EXIT_FAILURE;
  }
  /*
    * Create a new client instance
  */
  *client = mongoc_client_new_from_uri(uri);

  if(!(*client)) {
    return EXIT_FAILURE;
  }

  /*
    * Register the application name so we can track it in the profile logs
    * on the server. This can also be done from the URI (see other examples).
  */
  mongoc_client_set_appname(*client, "connect-maboke");
  mongoc_uri_destroy(uri);
  return 0;
}

int free_mongo_client(mongoc_client_t *client) {
  //Perform Cleanup.
  mongoc_client_destroy(client);
  mongoc_cleanup();
  return 0;
}
