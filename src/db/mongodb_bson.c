#include "./../../include/db/mongodb_bson.h"

int json_tobson(char *json, bson_t **bson) {
  bson_error_t error;

  *bson = bson_new_from_json((const uint8_t *)json, -1, &error);
  if(!*bson) {
    fprintf (stderr, "%s\n", error.message);
    return EXIT_FAILURE;
  }

  return 0;
}

int init_video_struct(VIDEO *video) {
  if(video != NULL) {
    video->title = (char*)malloc(sizeof(char));
    video->category = (char*)malloc(sizeof(char));
    video->summary = (char*)malloc(sizeof(char));
    video->url = (char*)malloc(sizeof(char));
    video->length = (char*)malloc(sizeof(char));
    video->censor_rating = (char*)malloc(sizeof(char));
  }
  return 0;
}

int set_video_title(VIDEO *video, char *title) {
  char *new_title;
  if(video != NULL && title != NULL) {
    new_title = (char*) realloc(video->title, (strlen(title)+1) * sizeof(char));
    if(new_title != NULL) {
      video->title = new_title;
      sprintf(video->title, "%s", title);
    }
  }
  return 0;
}

int set_video_category(VIDEO *video, char *category) {
  char *new_category;
  if(video != NULL && category != NULL) {
    new_category = (char*) realloc(video->category, (strlen(category)+1) * sizeof(char));
    if(new_category != NULL) {
      video->category = new_category;
      sprintf(video->category, "%s", category);
    }
  }
  return 0;
}

int set_video_summary(VIDEO *video, char *summary) {
  char *new_summary;
  if(video != NULL && summary != NULL) {
    new_summary = (char*) realloc(video->summary, (strlen(summary)+1) * sizeof(char));
    if(new_summary != NULL) {
      video->summary = new_summary;
      sprintf(video->summary, "%s", summary);
    }
  }
  return 0;
}

int set_video_url(VIDEO *video, char *url) {
  char *new_url;
  if(video != NULL && url != NULL) {
    new_url = (char*) realloc(video->url, (strlen(url)+1) * sizeof(char));
    if(new_url != NULL) {
      video->url = new_url;
      sprintf(video->url, "%s", url);
    }
  }
  return 0;
}

int set_video_length(VIDEO *video, char *length) {
  char *new_length;
  if(video != NULL && length != NULL) {
    new_length = (char*) realloc(video->length, (strlen(length)+1) * sizeof(char));
    if(new_length != NULL) {
      video->length = new_length;
      sprintf(video->length, "%s", length);
    }
  }
  return 0;
}

int set_video_censor_rating(VIDEO *video, char *censor_rating) {
  char *new_censor_rating;
  if(video != NULL && censor_rating != NULL) {
    new_censor_rating = (char*) realloc(video->censor_rating, (strlen(censor_rating)+1) * sizeof(char));
    if(new_censor_rating != NULL) {
      video->censor_rating = new_censor_rating;
      sprintf(video->censor_rating, "%s", censor_rating);
    }
  }
  return 0;
}

int print_video(VIDEO *video, char *tabs) {
  if(video != NULL) {
    printf("%s", tabs);
    printf("\"Video\" : {\n");
    printf("%s", tabs);
    printf("\t\"Title\" : \"%s\",\n", video->title);
    printf("%s", tabs);
    printf("\t\"Category\" : \"%s\",\n", video->category);
    printf("%s", tabs);
    printf("\t\"Summary\" : \"%s\"\n", video->summary);
    printf("%s", tabs);
    printf("\t\"Url\" : \"%s\"\n", video->url);
    printf("%s", tabs);
    printf("\t\"Length\" : \"%s\"\n", video->length);
    printf("%s", tabs);
    printf("\t\"Censor_rating\" : \"%s\"\n", video->censor_rating);
    printf("%s", tabs);
    printf("}\n");
  }
  return 0;
}

int free_video_struct(VIDEO *video) {
  if(video != NULL) {
    free(video->title);
    free(video->category);
    free(video->summary);
    free(video->url);
    free(video->length);
    free(video->censor_rating);
    free(video);
  }
  return 0;
}

int init_video_array_struct(VIDEO_ARRAY *array, size_t length) {
    if(array != NULL) {
        array->elements = malloc(length * sizeof(*array->elements));
        for(int i = 0; i < length; i++) {
          //array->elements[i] = (VIDEO *) malloc(sizeof(VIDEO*));
          init_video_struct(&(array->elements[i]));
        }
        array->length = length;
    }

    return 0;
}

int free_video_array_struct(VIDEO_ARRAY *array) {
  if(array != NULL) {
    free(array->elements);
    free(array);
  }

  return 0;
}

int print_array_video(VIDEO_ARRAY *array, char *tabs, char* subtabs) {
  if(array != NULL) {
    printf("%s", tabs);
    printf("\"VideoArray\" : [\n");
    for(int i = 0; i < array->length; i++) {
      print_video(&(array->elements[i]), subtabs);
      if(i < array->length -1) 
        printf("%s,\n", subtabs);
    }
    printf("%s]\n", tabs);
  }
  return 0;
}

int init_season_struct(SEASON *season, size_t videoLen) {
  if(season != NULL) {
    season->title = (char*)malloc(sizeof(char));
    season->date = (char*)malloc(sizeof(char));
    season->summary = (char*)malloc(sizeof(char));
    season->number = 0;
    season->videos =  malloc(sizeof(*season->videos));
    if(season->videos != NULL) {
      init_video_array_struct(season->videos, videoLen);
    }
  }
  return 0;
}

int free_season_struct(SEASON *season) {
  if(season != NULL) {
    free(season->title);
    free(season->date);
    free(season->summary);
    free_video_array_struct(season->videos);
    free(season);
  }
  return 0;
}

int set_season_title(SEASON *season, char *title) {
  char *new_title;
  if(season != NULL && title != NULL) {
    new_title = (char*) realloc(season->title, (strlen(title)+1) * sizeof(char));
    if(new_title != NULL) {
      season->title = new_title;
      sprintf(season->title, "%s", title);
    }
  }
  return 0;
}

int set_season_date(SEASON *season, char *date) {
  char *new_date;
  if(season != NULL && date != NULL) {
    new_date = (char*) realloc(season->date, (strlen(date)+1) * sizeof(char));
    if(new_date != NULL) {
      season->date = new_date;
      sprintf(season->date, "%s", date);
    }
  }
  return 0;
}

int set_season_summary(SEASON *season, char *summary) {
  char *new_summary;
  if(season != NULL && summary != NULL) {
    new_summary = (char*) realloc(season->summary, (strlen(summary)+1) * sizeof(char));
    if(new_summary != NULL) {
      season->summary = new_summary;
      sprintf(season->summary, "%s", summary);
    }
  }
  return 0;
}

int print_season(SEASON *season, char *tabs) {
  if(season != NULL) {
    printf("%s", tabs);
    printf("Season : {\n");
    printf("%s", tabs);
    printf("\t\"Title\" : \"%s\",\n", season->title);
    printf("%s", tabs);
    printf("\t\"Date\" : \"%s\",\n", season->date);
    printf("%s", tabs);
    printf("\t\"Summary\" : \"%s\",\n", season->summary);
    printf("%s", tabs);
    print_array_video(season->videos, "\t", "\t\t");
    printf("%s", tabs);
    printf("}\n");
  }
  return 0;
}

int init_season_array_struct(SEASON_ARRAY *array, size_t length) {
  if(array != NULL) {
    array->elements = malloc(length * sizeof(array->elements));
    for(int i = 0; i < length; i++) {
      array->elements[i] = (SEASON*) malloc(sizeof(SEASON*));
      //init_season_struct(array->elements[i]);
    }
    array->length = length;
  }
  return 0;
}

int free_season_array_struct(SEASON_ARRAY *array) {
  if(array != NULL) {
    for(int i = 0; i <  array->length; i++) {
      free_season_struct(array->elements[i]);
    }
    free(array->elements);
    free(array);
  }

  return 0;
}

int init_serie_struct(SERIE *serie, size_t array_size) {
  if(serie != NULL) {
    serie->keys = NULL;
    serie->values = NULL;
    serie->director = NULL;
    serie->pproducer = NULL;
    serie->studio = NULL;
    serie->cats = NULL;
    serie->contentTag = NULL;

    init_array(&(serie->keys), array_size, 5, "");
    init_array(&(serie->values), array_size, 5, "");
    init_array(&(serie->contentTag), array_size, 5, "");
  }  
  return 0;
}

int print_serie(SERIE *serie) {
  if(serie != NULL) {
    printf("Serie : {\n");

    for(int i = 0; i < serie->keys->length; i++) {
      printf("\t%s : %s", serie->keys->elements[i],  serie->values->elements[i]);

      if(i < serie->keys->length -1)
        printf(",\n");
      else
       printf("\n");
    }

    printf("}\n");

  }
  return 0;
}

int free_serie(SERIE *serie) {
  if(serie != NULL) {
    if(serie->keys != NULL)
      free_array(serie->keys);

    if(serie->values != NULL)
      free_array(serie->values);

    if(serie->contentTag != NULL)
      free_array(serie->contentTag);

    free(serie);
  }
  return 0;
}

int int_date(bson_t **bson, char *field) {
  struct tm year = { 0 };
  /*
    * Append { "born" : ISODate("1906-12-09") } to the document.
    * Passing -1 for the length argument tells libbson to calculate the string length.
  */
  year.tm_year = 6;  /* years are 1900-based */
  year.tm_mon = 11;  /* months are 0-based */
  year.tm_mday = 9;

  BSON_APPEND_DATE_TIME(*bson, field, mktime(&year) * 1000);

  return 0;
}

int int_date_(bson_t *bson, char *field) {
  struct tm year = { 0 };
  /*
    * Append { "born" : ISODate("1906-12-09") } to the document.
    * Passing -1 for the length argument tells libbson to calculate the string length.
  */
  year.tm_year = 6;  /* years are 1900-based */
  year.tm_mon = 11;  /* months are 0-based */
  year.tm_mday = 9;

  BSON_APPEND_DATE_TIME(bson, field, mktime(&year) * 1000);

  return 0;
}

int init_director(bson_t *director) {
  BSON_APPEND_UTF8(director, "name", "Director name");
  int_date(&director, "startYear");
  int_date(&director, "endYear");
  int_date(&director, "birthYear");

  return 0;
}

int init_studio(bson_t *studio) {
  BSON_APPEND_UTF8(studio, "name", "Studio name");
  BSON_APPEND_UTF8(studio, "city", "Studio City");
  BSON_APPEND_UTF8(studio, "country", "Studio country");
  int_date(&studio, "startYear");
  int_date(&studio, "endYear");
  int_date(&studio, "birthYear");
  BSON_APPEND_UTF8(studio, "fonder", "Studio fonder");
  return 0;
}

int init_actor(bson_t *actor) {
  char buf[16];
  size_t keylen;
  bson_t child2;
  const char *key;

  keylen = bson_uint32_to_string (0, &key, buf, sizeof buf);
  bson_append_document_begin(actor, key, (int)keylen, &child2);

  BSON_APPEND_UTF8(&child2, "name", "Actor name");
  BSON_APPEND_UTF8(&child2, "gender", "Actor gender");
  int_date_(&child2, "startYear");
  int_date_(&child2, "endYear");
  int_date_(&child2, "birthYear");
  int_date_(&child2, "deathYear");
  bson_append_document_end(actor, &child2);

  return 0;
}

int init_award(bson_t *award) {
  char buf[16];
  size_t keylen;
  bson_t child2;
  const char *key;

  keylen = bson_uint32_to_string (0, &key, buf, sizeof buf);
  bson_append_document_begin(award, key, (int)keylen, &child2);
  BSON_APPEND_UTF8(&child2, "name", "Award name");
  BSON_APPEND_UTF8(&child2, "organization", "Award organization");
  BSON_APPEND_UTF8(&child2, "contry", "Award contry");
  bson_append_document_end(award, &child2);
  return 0;
}

int init_cast(bson_t *cast) {
  bson_t actor, award;

  BSON_APPEND_ARRAY_BEGIN(cast, "actors", &actor);
  init_actor(&actor);
  bson_append_array_end (cast, &actor);
  
  BSON_APPEND_ARRAY_BEGIN(cast, "awards", &award);
  init_award(&award);
  bson_append_array_end(cast, &award);

  return 0;
}

int init_content_tag(bson_t **document) {
  bson_t tag;
  char buf[16];
  size_t  keylen;
  const char *key;

  BSON_APPEND_ARRAY_BEGIN(*document, "contentTag", &tag);
  keylen = bson_uint32_to_string(0, &key, buf, sizeof buf);
  bson_append_utf8(&tag, key, (int)keylen, "test_tag", -1);
  bson_append_array_end(*document, &tag);

  return 0;
}

int init_video(bson_t *video) {
  char buf[16];
  size_t keylen;
  bson_t child2;
  const char *key;

  if(video != NULL) {
    keylen = bson_uint32_to_string(0, &key, buf, sizeof buf);
    bson_append_document_begin(video, key, (int)keylen, &child2);
    BSON_APPEND_UTF8(&child2, "title", "Video title");
    BSON_APPEND_UTF8(&child2, "category", "Video category");
    BSON_APPEND_UTF8(&child2, "summary", "Video summary");
    BSON_APPEND_UTF8(&child2, "url", "Video url");
    BSON_APPEND_UTF8(&child2, "length", "Video length");
    BSON_APPEND_UTF8(&child2, "censor_rating", "Video censor_rating");
    int_date_(&child2, "created_at");
    int_date_(&child2, "upDated_at");
    bson_append_document_end(video, &child2);
  }

  return 0;
}

int init_season(bson_t *season) {
  bson_t videos;
  char buf[16];
  size_t keylen;
  bson_t child2;
  const char *key;

  if(season != NULL) {
    keylen = bson_uint32_to_string(0, &key, buf, sizeof buf);
    bson_append_document_begin(season, key, (int)keylen, &child2);
    BSON_APPEND_UTF8(&child2, "title", "Season title");
    int_date_(&child2, "date");
    BSON_APPEND_UTF8(&child2, "summary", "Season summary");
    BSON_APPEND_INT32(&child2, "number", 1);
    BSON_APPEND_ARRAY_BEGIN(&child2, "videos", &videos);
    init_video(&videos);
    bson_append_array_end(&child2, &videos);
    bson_append_document_end(season, &child2); 
  }

  return 0;
}

int init_seasons(bson_t **document) {
  bson_t season;
  BSON_APPEND_ARRAY_BEGIN(*document, "seasons", &season);
  init_season(&season);
  bson_append_array_end(*document, &season);
  return 0;
}

int init_keys_and_values(bson_t **bson, char **keys, char **values, size_t len) {  
  if(keys != NULL && values != NULL) {
    for(int i = 0; i < len; i++) {
      BSON_APPEND_UTF8(*bson, keys[i], values[i]);
    }
  }
  return 0;
}

int serie_to_bson(bson_t **document, SERIE *serie) {
  bson_t director, producer, studio, cast;
  //char *keys[] = {"title", "img", "category", "summary"};
  //char *values[] = {"Serie title", "Serie img",  "Serie category", "Serie summary"};

  if(serie != NULL) {
    init_keys_and_values(&(*document),serie->keys->elements, serie->values->elements, serie->keys->length); 
  }

  int_date(&(*document), "year");
  BSON_APPEND_DOCUMENT_BEGIN(*document, "director", &director);
  init_director(&director);
  bson_append_document_end(*document, &director);
  BSON_APPEND_DOCUMENT_BEGIN(*document, "producer", &producer);
  init_director(&producer);
  bson_append_document_end(*document, &producer);
  BSON_APPEND_DOCUMENT_BEGIN(*document, "studio", &studio);
  init_studio(&studio);
  bson_append_document_end(*document, &studio);
  BSON_APPEND_DOCUMENT_BEGIN(*document, "cast", &cast);
  init_cast(&cast);
  bson_append_document_end(*document, &cast);
  init_content_tag(&(*document));
  init_seasons(&(*document));
  return 0;
}

int init_date__(struct tm date) {
  date.tm_year = 6;
  date.tm_mon = 11;
  date.tm_mday = 9;
  return 0;
}

int init_movie() {
  struct tm startYear = {0};
  struct tm endYear = {0};
  struct tm birthYear = {0};
  struct tm deathYear = {0};
  struct tm created_at = {0};
  bson_t  *document;
  char *str;

  init_date__(startYear);
  init_date__(endYear);
  init_date__(birthYear);
  init_date__(deathYear);
  init_date__(created_at);

  document = BCON_NEW(
    "director", "{",
      "name", BCON_UTF8("Director name"),
      "startYear", BCON_DATE_TIME(mktime (&startYear) * 1000),
      "endYear", BCON_DATE_TIME(mktime (&endYear) * 1000),
      "birthYear", BCON_DATE_TIME(mktime (&birthYear) * 1000),
    "}",
    "producer", "{",
      "name", BCON_UTF8("Producer name"),
      "startYear", BCON_DATE_TIME(mktime (&startYear) * 1000),
      "endYear", BCON_DATE_TIME(mktime (&endYear) * 1000),
      "birthYear", BCON_DATE_TIME(mktime (&birthYear) * 1000),
    "}",
    "studio", "{",
      "name", BCON_UTF8("Studio name"),
      "city", BCON_UTF8("Studio city"),
      "country", BCON_UTF8("Studio country"),
      "startYear", BCON_DATE_TIME(mktime (&startYear) * 1000),
      "endYear", BCON_DATE_TIME(mktime (&endYear) * 1000),
      "birthYear", BCON_DATE_TIME(mktime (&birthYear) * 1000),
      "fonder", BCON_UTF8("Studio fonder"),
    "}",
     "cast", "{",
        "actors", "[",
          "{", 
            "name", BCON_UTF8 ("Actor name"), 
            "startYear", BCON_DATE_TIME(mktime (&startYear) * 1000),
            "endYear", BCON_DATE_TIME(mktime (&endYear) * 1000),
            "birthYear", BCON_DATE_TIME(mktime (&birthYear) * 1000),
            "deathYear", BCON_DATE_TIME(mktime (&deathYear) * 1000),
            "gender", BCON_UTF8 ("Actor gender"), 
          "}",
        "]",
        "awards", "[",
          "{", 
            "name", BCON_UTF8("Award name"),
            "organization", BCON_UTF8("Organization"), 
            "contry;", BCON_UTF8("Contry"),
          "}", 
        "]",
    "}", 
    "video", "{",
      "title", BCON_UTF8("Video title"),
      "category", BCON_UTF8("Video category"),
      "summary", BCON_UTF8("Video summary"),
      "url", BCON_UTF8("Video url"),
      "length", BCON_UTF8("Video length"),
      "censor_rating", BCON_UTF8("Video censor_rating"),
      "created_at", BCON_DATE_TIME(mktime (&created_at) * 1000),
      "endYear", BCON_DATE_TIME(mktime (&endYear) * 1000),
      "birthYear", BCON_DATE_TIME(mktime (&birthYear) * 1000),
      "fonder", BCON_UTF8("Studio fonder"),
  "}");
  /*
  * Print the document as a JSON string.
  */
  str = bson_as_canonical_extended_json (document, NULL);
  printf ("%s\n", str);
  bson_free (str);
  /*
  * Clean up allocated bson documents.
  */
  bson_destroy (document);
  return 0;
}

int create_season(struct json_object *serie) {
  if(serie != NULL) {
    printf("create_season\n");
    //json_object_set_string(tmp, SHORT);
    //init_season(bson_t *season) 
  }
  return 0;
}

int get_seasontitle(char *title, char **season_title) {
  if(title != NULL) {
    get_str_match(title, "([sS]aison)[ ]*[0-9]", &(*season_title));

    if(*season_title == NULL) {
      *season_title = (char*) calloc(20, sizeof(char));
      sprintf(*season_title, "%s", "Season 1\0");
    }
  }

  return 0;
}

int exist_season(char *title, struct json_object *serie) {
  int exist = 0;
  char *season_title = NULL;
  struct json_object *seasons, *season, *titleObj;
  get_seasontitle(title, &season_title);

  if(serie != NULL && season_title != NULL) {
    seasons = getObj_rec(serie, "/seasons");
    if(seasons != NULL) {
      for(int i = 0; i < json_object_array_length(seasons); i++) {
        season = json_object_array_get_idx(seasons, i);
        titleObj = getObj_rec(season, "/title");

        if(titleObj != NULL && strcmp((char*)json_object_get_string(titleObj), season_title) == 0) {
          exist = 1;
          break;
          //printf("Title : %s, %s\n", season_title, (char*)json_object_get_string(titleObj));
        }
        printJson(season);
        
      }
    }

    free(season_title);
  }

  return exist;
}

int exist_serie(char *title, struct json_object **json) {
  char *str;
  char *regex = NULL;
  const bson_t *document;
  bson_t *selector = NULL;
  mongoc_client_t *client = NULL;
  File *fifo = malloc(sizeof(*fifo));
  mongoc_cursor_t *cursor = NULL;

  fifo_init(fifo);

  if(title != NULL) {
    init_mongo_client(&client);
    get_match(title, "[A-Za-z]+[ ]+[A-Za-z]+", fifo);
    join_file_element(fifo, &regex, ".*", 1);
    //printf("Regex : %s\n", regex);
    if(regex != NULL && client != NULL) {
      selector =  BCON_NEW(
        "title", "{",
          "$regex", BCON_UTF8(regex),
          "$options", BCON_UTF8("i"),
        "}"
      );

      if(selector != NULL) {
        //print_bson(selector);
        find_document(client, "maboke", "serie", selector, &cursor);
        if(cursor != NULL && mongoc_cursor_next(cursor, &document)) {
          str = bson_as_relaxed_extended_json(document, NULL);
          *json = getJson(str);
          bson_free(str);
          //printf("%s\n", str);
          //print_cursor(cursor);       
        }
      }
      
    }
  }

  free(regex);
  freeFile(fifo);
  bson_free(cursor);
  bson_destroy(selector);
  free_mongo_client(client);

  return 0;
}

int check_beforeinsert(SERIE *serie) {
  bson_t *document = bson_new();
  mongoc_client_t *client = NULL;

  if(serie != NULL) {
    print_serie(serie);
    init_mongo_client(&client);
    //serie_to_bson(&document, serie);
    if(document != NULL && client != NULL) {
      print_bson(document);
      //insert_document(client, "maboke", "serie", document);
    }
  }

  bson_destroy(document);
  free_mongo_client(client);

  return 0;
}

int save_serie(struct json_object *video) {
  SERIE *serie = NULL;
  size_t keysLen = 3;
  struct json_object *titleObj,  *imgObj, *videoObj;
  serie = malloc(sizeof(*serie));

  if(serie != NULL && video != NULL) {
    printf("SaveSerie : \n");
    titleObj = getObj_rec(video, TITLE_FIELD);
    imgObj = getObj_rec(video, IMG_FIELD);
    videoObj = getObj_rec(video, VIDEOID_FIELD);
    
    init_serie_struct(serie, keysLen);
    add_value(&(serie)->keys, "videoId", 0);
    add_value(&(serie)->keys, "title", 1);
    add_value(&(serie)->keys, "img", 2);

    add_value(&(serie)->values, (char *)json_object_get_string(videoObj), 0);
    add_value(&(serie)->values, (char *)json_object_get_string(titleObj), 1);
    add_value(&(serie)->values, (char *)json_object_get_string(imgObj), 2);
    //check_beforeinsert(serie, (char *)json_object_get_string(titleObj));
    //exist_serie((char *)json_object_get_string(titleObj));
  }

  free_serie(serie);
  
  return 0;
}

int save_video(struct json_object *video, const char *title) {
  if(video != NULL && title != NULL) {
    save_serie(video); 
  } 
  return 0;
}