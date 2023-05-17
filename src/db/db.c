#include "./../../include/db/db.h"


int print_bson(bson_t *bson) {
  char *str;
  
  if(bson != NULL) {
    str = bson_as_canonical_extended_json(bson, NULL);
    printf("%s\n", str);
    bson_free(str);
  }

  return 0;
}

int print_cursor(mongoc_cursor_t *cursor) {
  char *str;
  const bson_t *next_doc;

  if(cursor != NULL) {
    while (mongoc_cursor_next(cursor, &next_doc)) {
      str = bson_as_relaxed_extended_json(next_doc, NULL);
      printf("%s\n", str);
      bson_free(str);
    }
  }

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

int get_collection(mongoc_client_t *client, char *dbName, char *collection) {
  char *str;
  bson_t *cmd;
  bson_t reply;
  bson_error_t error;
  mongoc_collection_t *coll;
  
  if(client != NULL) {
    coll = mongoc_client_get_collection(client, dbName, collection);
    cmd = BCON_NEW("ping", BCON_INT32 (1));

    if(mongoc_collection_command_simple(coll, cmd, NULL, &reply, &error)) {
      str = bson_as_canonical_extended_json(&reply, NULL);
      printf("Got reply: %s\n", str);
      bson_free(str);
    } else {
      fprintf(stderr, "Got error: %s\n", error.message);
    }
  }

  bson_destroy(&reply);
  bson_destroy(cmd);
  mongoc_collection_destroy(coll);
  return 0;
}

int find_and_update(mongoc_client_t *client, char *dbName, char *collection) {
  bson_t *query;
  bson_t *update;
  bson_t reply;
  bson_error_t error = {0};
  mongoc_collection_t *coll;

  coll = mongoc_client_get_collection(client, dbName, collection);
  /*
  * Build our query, {"cmpxchg": 1}
  */
  query = BCON_NEW("cmpxchg", BCON_INT32 (1));

   /*
    * Build our update. {"$set": {"cmpxchg": 2}}
  */
  update = BCON_NEW("$set", "{", "cmpxchg", BCON_INT32(2), "}");

  /*
  * Submit the findAndModify.
  */
  if(!mongoc_collection_find_and_modify(coll, query, NULL, update, NULL, false, false, true, &reply, &error)) {
    fprintf (stderr, "find_and_modify() failure: %s\n", error.message);
    return EXIT_FAILURE;
  }

  print_bson(&reply);

  bson_destroy(query);
  bson_destroy(update);
  bson_destroy(&reply);
  mongoc_collection_destroy(coll);

  return 0;
}

int find_document(mongoc_client_t *client, char *dbName, char *collection, bson_t *selector,  mongoc_cursor_t **cursor) {
  mongoc_collection_t *coll;
  //bson_t *selector = BCON_NEW("_id", "{", "$gt", BCON_INT32(0), "}");
  coll = mongoc_client_get_collection(client, dbName, collection);

  if(coll != NULL) {
    *cursor = mongoc_collection_find_with_opts(coll, selector, NULL, NULL);
  }
  
  mongoc_collection_destroy(coll);
  return 0;
}

int update_document(mongoc_client_t *client, char *dbName, char *collection) {
  bson_t *update;
  bson_error_t error = {0};
  mongoc_collection_t *coll;
  bson_t *selector = BCON_NEW("_id", "{", "$gt", BCON_INT32 (0), "}");

  coll = mongoc_client_get_collection(client, dbName, collection);
  /*
    * Build our update. {"$set": {"x": 1}}
  */
  update = BCON_NEW("$set", "{", "x", BCON_INT32 (1), "}");

  if(!mongoc_collection_update_one(coll, selector, update, NULL, NULL, &error)) {
    fprintf(stderr, "update failed: %s\n", error.message);
    return EXIT_FAILURE;
  }

  bson_destroy(update);
  bson_destroy(selector);
  mongoc_collection_destroy(coll);

  return 0;
}

int insert_document(mongoc_client_t *client, char *dbName, char *collection, bson_t *to_insert) {
  bson_error_t error = {0};
  mongoc_collection_t *coll;

  coll = mongoc_client_get_collection(client, dbName, collection);
  mongoc_client_set_error_api(client, 2);

  /* insert a document */
  if(!mongoc_collection_insert_one(coll, to_insert, NULL, NULL, &error)) {
    fprintf(stderr, "insert failed: %s\n", error.message);
    return EXIT_FAILURE;
  }

  mongoc_collection_destroy(coll);

  return 0;
}

int create_collection(mongoc_client_t *client, char *collectionName, char *dbName) {
  bson_error_t error;
  mongoc_database_t *database = NULL;
  mongoc_collection_t *collection = NULL;

  database = mongoc_client_get_database(client, dbName);

  /* inserting into a nonexistent collection normally creates it, but a
  * collection can't be created in a transaction; create it now */
  collection = mongoc_database_create_collection(database, collectionName, NULL, &error);

  if(!collection) {
    /* code 48 is NamespaceExists, see error_codes.err in mongodb source */
    if(error.code == 48) {
      collection = mongoc_database_get_collection(database, "collection");
    } else {
      MONGOC_ERROR ("Failed to create collection: %s", error.message);
      //goto done;
    }
  }
  
  mongoc_collection_destroy(collection);
  mongoc_database_destroy(database);
  
  return 0;
}

int delete_document(mongoc_client_t *client, char *collectionName, char *dbName, bson_t *doc) {
  bson_error_t error;
  mongoc_collection_t *collection;
  mongoc_database_t *database = NULL;

  database = mongoc_client_get_database(client, dbName);
  collection = mongoc_database_create_collection(database, collectionName, NULL, &error);

  if(!mongoc_collection_delete_one(collection, doc, NULL, NULL, &error)) {
    fprintf (stderr, "Delete failed: %s\n", error.message);
  }

  mongoc_collection_destroy(collection);
  mongoc_database_destroy(database);

  return 0;
}

int init_mongo_client(mongoc_client_t **client) {
  mongoc_uri_t *uri;
  bson_error_t error = {0};
  const char *uri_string = "mongodb://root:secret@mongodb";

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