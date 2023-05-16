#include "./../../include/db/mongodb_bson.h"

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

int init_director(bson_t *director) {
  BSON_APPEND_UTF8(director, "name", "Director name");
  int_date(&director, "yearStart");
  int_date(&director, "yearEnd");
  int_date(&director, "birthYear");

  return 0;
}

int init_studio(bson_t *studio) {
  BSON_APPEND_UTF8(studio, "name", "Studio name");
  BSON_APPEND_UTF8(studio, "city", "Studio City");
  BSON_APPEND_UTF8(studio, "country", "Studio country");
  int_date(&studio, "yearStart");
  int_date(&studio, "yearEnd");
  int_date(&studio, "birthYear");
  BSON_APPEND_UTF8(studio, "fonder", "Studio fonder");
  return 0;
}

int init_actor(bson_t *actor) {
  BSON_APPEND_UTF8(actor, "name", "Actor name");
  BSON_APPEND_UTF8(actor, "gender", "Actor gender");
  int_date(&actor, "yearStart");
  int_date(&actor, "yearEnd");
  int_date(&actor, "birthYear");
  int_date(&actor, "deathYear");
  return 0;
}

int init_award(bson_t *award) {
  BSON_APPEND_UTF8(award, "name", "Award name");
  BSON_APPEND_UTF8(award, "organization", "Award organization");
  BSON_APPEND_UTF8(award, "contry", "Award contry");
  return 0;
}

int init_array() {
  return 0;
}

int init_cast(bson_t *cast) {
  bson_t actor, award;

  BSON_APPEND_ARRAY_BEGIN(cast, "actors", &actor);
  init_actor(&actor);
  //bson_append_document_end(document, &director);
  bson_append_array_end (cast, &actor);
  BSON_APPEND_ARRAY_BEGIN(cast, "awards", &award);
  init_award(&award);
  bson_append_array_end(cast, &award);

  return 0;
}

int init_content_tag( bson_t **document) {
  bson_t tag;
  char buf[16];
  size_t  keylen;
  const char *key;

  BSON_APPEND_ARRAY_BEGIN(*document, "contentTag", &tag);
  keylen = bson_uint32_to_string(0, &key, buf, sizeof buf);
  bson_append_utf8(&tag, key, (int)keylen, "test_tag", -1);
  //keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
  //bson_append_utf8 (&child, key, (int) keylen, lang_names[i], -1);
  bson_append_array_end(*document, &tag);

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

int init_serie() {
  char *str;
  size_t len = 4;
  bson_t *document = bson_new();
  bson_t director, producer, studio, cast;
  char *keys[] = {"title", "img", "category", "summary"};
  char *values[] = {"Serie title", "Serie img",  "Serie category", "Serie summary"};

  init_keys_and_values(&document, keys, values, len); 
  int_date(&document, "year");
  BSON_APPEND_DOCUMENT_BEGIN(document, "director", &director);
  init_director(&director);
  bson_append_document_end(document, &director);
  BSON_APPEND_DOCUMENT_BEGIN(document, "producer", &producer);
  init_director(&producer);
  bson_append_document_end(document, &producer);
  BSON_APPEND_DOCUMENT_BEGIN(document, "studio", &studio);
  init_studio(&studio);
  bson_append_document_end(document, &studio);
  BSON_APPEND_DOCUMENT_BEGIN(document, "cast", &cast);
  init_cast(&cast);
  bson_append_document_end(document, &cast);
  init_content_tag(&document);

  str = bson_as_canonical_extended_json(document, NULL);
  printf("%s\n", str);
  bson_free(str);
  /*
  * Clean up allocated bson documents.
  */
  bson_destroy (document);
  return 0;
}

int test_zbcon() {
  struct tm born = { 0 };
  struct tm died = { 0 };
  bson_t  *document;
  char *str;

   born.tm_year = 6;
   born.tm_mon = 11;
   born.tm_mday = 9;

   died.tm_year = 92;
   died.tm_mon = 0;
   died.tm_mday = 1;

   document = BCON_NEW (
      "born", BCON_DATE_TIME (mktime (&born) * 1000),
      "died", BCON_DATE_TIME (mktime (&died) * 1000),
      "name", "{",
      "first", BCON_UTF8 ("Grace"),
      "last", BCON_UTF8 ("Hopper"),
      "}",
      "languages", "[",
      BCON_UTF8 ("MATH-MATIC"),
      BCON_UTF8 ("FLOW-MATIC"),
      BCON_UTF8 ("COBOL"),
      "]",
      "degrees", "[",
      "{", "degree", BCON_UTF8 ("BA"), "school", BCON_UTF8 ("Vassar"), "}",
      "{", "degree", BCON_UTF8 ("PhD"), "school", BCON_UTF8 ("Yale"), "}",
      "]");

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