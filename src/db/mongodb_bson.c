#include "./../../include/db/mongodb_bson.h"

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
  bson_free(str);
  /*
  * Clean up allocated bson documents.
  */
  bson_destroy (document);
  return 0;
}

int josn_tobson(char *json, bson_t **bson) {
  bson_error_t error;

  *bson = bson_new_from_json((const uint8_t *)json, -1, &error);
  if(!*bson) {
    fprintf (stderr, "%s\n", error.message);
    return EXIT_FAILURE;
  }

  return 0;
}