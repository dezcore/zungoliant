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

int init_studio_struct(STUDIO *studio) {
  if(studio != NULL) {
    studio->name =  (char*) calloc(1, sizeof(char));
    studio->startYear =  (char*) calloc(1, sizeof(char));
    studio->endYear =  (char*) calloc(1, sizeof(char));
    studio->bithYear =  (char*) calloc(1, sizeof(char));
    studio->city =  (char*) calloc(1, sizeof(char));
    studio->country =  (char*) calloc(1, sizeof(char));
    studio->fonder =  (char*) calloc(1, sizeof(char));
  }
  return 0;
}

int set_studio_name(STUDIO *studio, char *name) {
  char *new_name;
  if(studio != NULL && name != NULL) {
    new_name = (char*) realloc(studio->name, (strlen(name)+1) * sizeof(char));
    if(new_name != NULL) {
      studio->name = new_name;
      sprintf(studio->name, "%s", name);
    }
  }
  return 0;
}

int set_studio_country(STUDIO *studio, char *country) {
  char *new_country;

  if(studio != NULL && country != NULL) {
    new_country = (char*) realloc(studio->country, (strlen(country)+1) * sizeof(char));
    if(new_country != NULL) {
      studio->country = new_country;
      sprintf(studio->country, "%s", country);
    }
  }

  return 0;
}

int set_studio_city(STUDIO *studio, char *city) {
  char *new_city;
  if(studio != NULL && city != NULL) {
    new_city = (char*) realloc(studio->city, (strlen(city)+1) * sizeof(char));
    if(new_city != NULL) {
      studio->city = new_city;
      sprintf(studio->city, "%s", city);
    }
  }
  return 0;
}

int set_studio_fonder(STUDIO *studio, char *fonder) {
  char *new_fonder;
  if(studio != NULL && fonder != NULL) {
    new_fonder = (char*) realloc(studio->fonder, (strlen(fonder)+1) * sizeof(char));
    if(new_fonder != NULL) {
      studio->fonder = new_fonder;
      sprintf(studio->fonder, "%s", fonder);
    }
  }
  return 0;
}

int set_studio_startYear(STUDIO *studio, char *date) {
  char *new_data;
  if(studio != NULL && date != NULL) {
    new_data = (char*) realloc(studio->startYear, (strlen(date)+1) * sizeof(char));
    if(new_data != NULL) {
      studio->startYear = new_data;
      sprintf(studio->startYear, "%s", date);
    }
  }
  return 0;
}

int set_studio_endYear(STUDIO *studio, char *date) {
  char *new_data;
  if(studio != NULL && date != NULL) {
    new_data = (char*) realloc(studio->endYear, (strlen(date)+1) * sizeof(char));
    if(new_data != NULL) {
      studio->endYear = new_data;
      sprintf(studio->endYear, "%s", date);
    }
  }
  return 0;
}

int set_studio_bithYear(STUDIO *studio, char *date) {
  char *new_data;
  if(studio != NULL && date != NULL) {
    new_data = (char*) realloc(studio->bithYear, (strlen(date)+1) * sizeof(char));
    if(new_data != NULL) {
      studio->bithYear = new_data;
      sprintf(studio->bithYear, "%s", date);
    }
  }
  return 0;
}

int set_studio(STUDIO *studio, char *name, char *country, char *city, char *fonder, char *startYear, char *endYear, char *bithYear) {
  if(studio != NULL) {
    set_studio_name(studio, name);
    set_studio_city(studio, city);
    set_studio_country(studio, country);
    set_studio_fonder(studio, fonder);
    set_studio_startYear(studio, startYear);
    set_studio_endYear(studio, endYear);
    set_studio_bithYear(studio, bithYear);
  }
  return 0;
}

int free_studio(STUDIO *studio) {
  if(studio != NULL) {
    free(studio->name);
    free(studio->city);
    free(studio->country);
    free(studio->fonder);
    free(studio->startYear);
    free(studio->endYear);
    free(studio->bithYear);
  }
  free(studio);
  return 0;
}

int print_studio(STUDIO *studio, char *tabs, char *subtabs) {
  if(studio != NULL) {
    printf(tabs);
    printf("\"Studio\" : {\n");
    printf(subtabs);
    printf("Name : %s,\n", studio->name);
    printf(subtabs);
    printf("City : %s,\n", studio->city);
    printf(subtabs);
    printf("Fonder : %s,\n", studio->fonder);
    printf(subtabs);
    printf("StartYear : %s,\n", studio->startYear);
    printf(subtabs);
    printf("EndYear : %s,\n", studio->endYear);
    printf(subtabs);
    printf("BithYear : %s\n", studio->bithYear);
    printf(tabs);
    printf("}\n");
  }
  return 0;
}

int init_director_struct(DIRECTOR *director) {
  if(director != NULL) {
    director->name = (char *) calloc(1, sizeof(char));
    director->startYear = (char *) calloc(1, sizeof(char));
    director->endYear = (char *) calloc( 1, sizeof(char));
    director->bithYear = (char *) calloc(1, sizeof(char));
  }
  return 0;
}

int set_director_name(DIRECTOR *director, char *name) {
  char *new_name;
  if(director != NULL && name != NULL) {
    new_name = (char*) realloc(director->name, (strlen(name)+1) * sizeof(char));
    if(new_name != NULL) {
      director->name = new_name;
      sprintf(director->name, "%s", name);
    }
  }
  return 0;
}

int set_director_startYear(DIRECTOR *director, char *date) {
  char *new_data;
  if(director != NULL && date != NULL) {
    new_data = (char*) realloc(director->startYear, (strlen(date)+1) * sizeof(char));
    if(new_data != NULL) {
      director->startYear = new_data;
      sprintf(director->startYear, "%s", date);
    }
  }
  return 0;
}

int set_director_endYear(DIRECTOR *director, char *date) {
  char *new_data;
  if(director != NULL && date != NULL) {
    new_data = (char*) realloc(director->endYear, (strlen(date)+1) * sizeof(char));
    if(new_data != NULL) {
      director->endYear = new_data;
      sprintf(director->endYear, "%s", date);
    }
  }
  return 0;
}

int set_director_bithYear(DIRECTOR *director, char *date) {
  char *new_data;
  if(director != NULL && date != NULL) {
    new_data = (char*) realloc(director->bithYear, (strlen(date)+1) * sizeof(char));
    if(new_data != NULL) {
      director->bithYear = new_data;
      sprintf(director->bithYear, "%s", date);
    }
  }
  return 0;
}

int set_director(DIRECTOR *director, char *name, char *startYear, char *endYear, char *bithYear) {
  if(director != NULL) {
    set_director_name(director, name);
    set_director_startYear(director, startYear);
    set_director_endYear(director, endYear);
    set_director_bithYear(director, bithYear);
  }
  return 0;
}

int free_director(DIRECTOR *director) {
  if(director != NULL) {
    free(director->name);
    free(director->startYear);
    free(director->endYear);
    free(director->bithYear);
  }
  free(director);
  return 0;
}

int print_director(DIRECTOR *director, char *tabs, char *subtabs) {
  if(director != NULL) {
    printf(tabs);
    printf("\"Director\" : {\n");
    printf(subtabs);
    printf("Name : %s,\n", director->name);
    printf(subtabs);
    printf("StartYear : %s,\n", director->startYear);
    printf(subtabs);
    printf("EndYear : %s,\n", director->endYear);
    printf(subtabs);
    printf("BithYear : %s\n", director->bithYear);
    printf(tabs);
    printf("}\n");
  }
  return 0;
}

int init_video_struct(VIDEO *video) {
  if(video != NULL) {
    video->title = (char*) calloc(1, sizeof(char));
    video->category = (char*) calloc(1, sizeof(char)); 
    video->summary = (char*) calloc(1, sizeof(char));
    video->url = (char*) calloc(1, sizeof(char));
    video->length = (char*) calloc(1, sizeof(char));
    video->censor_rating = (char*) calloc(1, sizeof(char));
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

int init_video_default_array_struct(VIDEO_ARRAY *array) {
  if(array != NULL) {
    array->elements = NULL;
    array->length = 0;
  }
  return 0;
}

int init_video_array_struct(VIDEO_ARRAY *array, size_t length) {
  VIDEO *video;
  if(array != NULL && array->elements == NULL) {
    array->elements = malloc(length * sizeof(*array->elements));
    for(int i = 0; i < length; i++) {
      video = &(array->elements[i]);
      init_video_struct(video);
    }
    array->length = length;
  }

  return 0;
}

int set_video(VIDEO *video, char *title, char *category, char *summary, char *url, char *length, char *censor_rating) {
    if(video != NULL && title != NULL && category != NULL && summary != NULL && url != NULL && length != NULL && censor_rating != NULL) {
        set_video_title(video, title);
        set_video_category(video, category);
        set_video_summary(video, summary);
        set_video_url(video, url);
        set_video_length(video, length);
        set_video_censor_rating(video, censor_rating);
    }
    return 0;
}

int resize_video_array_struct(VIDEO_ARRAY *array, size_t length) {
    VIDEO *elements;

    if(array != NULL && array->length < length) {
      elements = (VIDEO*) realloc(array->elements, length * sizeof(*array->elements));

      if(elements != NULL) {
        for(int i = array->length; i < length; i++) {
          init_video_struct(&(elements[i]));
        }
        array->elements = elements;
        array->length = length;
      }
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
    season->number = 0;
    season->title = (char*) calloc(1, sizeof(char));
    season->date = (char*) calloc(1, sizeof(char));
    season->summary = (char*) calloc(1, sizeof(char));
    season->videos =  malloc(sizeof(*season->videos));
    init_video_default_array_struct(season->videos);

    if(season->videos != NULL && 0 < videoLen) {
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

int set_seson(SEASON *season, char *title, char *date, char *summary, VIDEO_ARRAY *videos) {
  if(season != NULL && title != NULL && date != NULL && summary != NULL) {
    set_season_title(season, title);
    set_season_date(season, date);
    set_season_summary(season, summary);
    season->number = get_title_season(title);

    if(videos != NULL) {
      if(season->videos->length < videos->length)
        resize_video_array_struct(season->videos, videos->length);

      for(int i = 0; i < videos->length; i++) {
        set_video(&(season->videos->elements[i]) , videos->elements[i].title, 
          videos->elements[i].category, videos->elements[i].summary, 
          videos->elements[i].url, videos->elements[i].length, videos->elements[i].censor_rating
        );
      }
    }
    
  }
  return 0;
}

int print_season(SEASON *season, char *tabs, char *videos_tabs, char *videos_subtabs) {
  if(season != NULL) {
    printf("%s", tabs);
    printf("Season : {\n");
    printf("%s", tabs);
    printf("\t\"Title\" : \"%s\",\n", season->title);
    printf("%s", tabs);
    printf("\t\"Date\" : \"%s\",\n", season->date);
    printf("%s", tabs);
    printf("\t\"Number\" : \"%d\",\n", season->number);
    printf("%s", tabs);
    printf("\t\"Summary\" : \"%s\",\n", season->summary);
    //printf("%s", tabs);
    print_array_video(season->videos, videos_tabs, videos_subtabs);
    printf("%s", tabs);
    printf("}\n");
  }
  return 0;
}

int init_season_default_array_struct(SEASON_ARRAY *array) {
  if(array != NULL) {
    array->elements = NULL;
    array->length = 0;
  }
  return 0;
}

int init_season_array_struct(SEASON_ARRAY *array, size_t length, size_t videosLen) {
    SEASON *season;
    if(array != NULL && array->elements == NULL) {
        array->elements = malloc(length * sizeof(*array->elements));
        for(int i = 0; i < length; i++) {
          season = &(array->elements[i]);
          init_season_struct(season, videosLen);
        }
        array->length = length;
    }
    return 0;
}

int free_season_array_struct(SEASON_ARRAY *array) {
  VIDEO *video;
  SEASON *season;

  if(array != NULL) {
    if(0 < array->length) {
      for(int i = 0; i < array->length; i++) {
        season = &(array->elements[i]);
        free(season->date);
        free(season->summary);
        free(season->title);
        if(0 < season->videos->length) {
          for(int j = 0; j < season->videos->length; j++) {
            video = &(season->videos->elements[j]);
            free(video->category);
            free(video->censor_rating);
            free(video->length);
            free(video->summary);
            free(video->title);
            free(video->url);
          }
          free(season->videos);
        }
      }
    }
    free(array->elements);
  }
  free(array);
  return 0;
}

int resize_season_array_struct(SEASON_ARRAY *array, size_t length,  size_t videoLen) {
  SEASON *elements;

  if(array != NULL && array->length < length) {
    elements = (SEASON*) realloc(array->elements, length * sizeof(*array->elements));

    if(elements != NULL) {
      for(int i = array->length; i < length; i++) {
        init_season_struct(&(elements[i]), 1);
      }
      array->elements = elements;
      array->length = length;
    }
  }
  return 0;
}

int print_array_season(SEASON_ARRAY *array, char *tabs, char* subtabs, char *season_tabs, char *season_subtabs) {
  if(array != NULL) {
    printf("%s", tabs);
    printf("\"SeasonArray\" : [\n");
    for(int i = 0; i < array->length; i++) {
      print_season(&(array->elements[i]), subtabs, season_tabs, season_subtabs);
      if(i < array->length -1) 
        printf("%s,\n", subtabs);
    }
    printf("%s]\n", tabs);
  }
  return 0;
}

int init_key_value(KEY_VALUE *key_value) {
  if(key_value != NULL) {
    key_value->key = (char*) calloc(1, sizeof(char));
    key_value->value = (char*) calloc(1, sizeof(char));
  }
  return 0;
}

int set_key_value_key(KEY_VALUE *key_value, char *key) {
  char *new_key;
  if(key_value != NULL && key != NULL) {
    new_key = (char*) realloc(key_value->key, (strlen(key)+1) * sizeof(char));
    if(new_key != NULL) {
      key_value->key = new_key;
      sprintf(key_value->key, "%s", key);
    }
  }
  return 0;
}

int set_key_value_value(KEY_VALUE *key_value, char *value) {
  char *new_value;
  if(key_value != NULL && value != NULL) {
    new_value = (char*) realloc(key_value->value, (strlen(value)+1) * sizeof(char));
    if(new_value != NULL) {
      key_value->value = new_value;
      sprintf(key_value->value, "%s", value);
    }
  }
  return 0;
}

int set_key_value(KEY_VALUE *key_value, char *key, char *value) {
  if(key_value != NULL && key != NULL && value != NULL) {
    set_key_value_key(key_value, key);
    set_key_value_value(key_value, value);
  }
  return 0;
}

int print_key_value(KEY_VALUE *key_value, char *kv_tabs, char *kv_subtabs) {
  if(key_value != NULL) {
    printf(kv_tabs);
    printf("Key_value : {\n");
    printf(kv_subtabs);
    printf("%s : %s\n", key_value->key, key_value->value);
    printf(kv_tabs);
    printf("}\n");
  }
  return 0;
}

int init_key_value_array_struct(KEY_VALUE_ARRAY *array, size_t length) {
  KEY_VALUE *element;

  if(array != NULL) {
    array->elements = malloc(length * sizeof(*array->elements));
    for(int i = 0; i < length; i++) {
      element = &(array->elements[i]);
      init_key_value(element);
    }
    array->length = length;
  }
  return 0;
}

int free_key_value_array_struct(KEY_VALUE_ARRAY *array) {
  KEY_VALUE *element;
  if(array != NULL) {
    if(0 < array->length) {
      for(int i = 0; i < array->length; i++) {
        element = &(array->elements[i]);
        free(element->key);
        free(element->value);
      }
    }
    free(array->elements);
  }
  free(array);
  return 0;
}

int resize_key_value_array_struct(KEY_VALUE_ARRAY *array, size_t length) {
  KEY_VALUE *elements;

  if(array != NULL && array->length < length) {
    elements = (KEY_VALUE*) realloc(array->elements, length * sizeof(*array->elements));

    if(elements != NULL) {
      for(int i = array->length; i < length; i++) {
        init_key_value(&(elements[i]));
      }
      array->elements = elements;
      array->length = length;
    }
  }
  return 0;
}

int print_array_key_value(KEY_VALUE_ARRAY *array, char *tabs, char* subtabs, char *kv_tabs, char *kv_subtabs) {
  if(array != NULL) {
    printf("%s", tabs);
    printf("\"Key_Value_Array\" : [\n");
    for(int i = 0; i < array->length; i++) {
      print_key_value(&(array->elements[i]), kv_tabs, kv_subtabs);
      if(i < array->length -1) 
        printf("%s,\n", subtabs);
    }
    printf("%s]\n", tabs);
  }
  return 0;
}

int free_key_value(KEY_VALUE *key_value) {
  if(key_value != NULL) {
    free(key_value->key);
    free(key_value->value);
    free(key_value);
  }
  return 0;
}

int init_serie_default_parameters(SERIE *serie) {
  if(serie != NULL) {
    serie->year =(char*) calloc(1, sizeof(*serie->year));
    serie->director = malloc(sizeof(*serie->director));
    serie->producer = malloc(sizeof(*serie->producer));
    serie->studio =  malloc(sizeof(*serie->studio));
    serie->contentTag =  malloc(sizeof(*serie->contentTag));
    serie->key_value_array = malloc(sizeof(*serie->key_value_array));
    serie->seasons =  malloc(sizeof(*serie->seasons));

    init_director_struct(serie->director);
    init_director_struct(serie->producer);
    init_studio_struct(serie->studio);
    init_default_str_array_struct(serie->contentTag);
    init_key_value_array_struct(serie->key_value_array, 1);
    init_season_default_array_struct(serie->seasons);
    //serie->cats = NULL; 
  }
  return 0;
}

int free_serie(SERIE *serie) {
  if(serie != NULL) {
    free(serie->year);
    free_director(serie->director);
    free_director(serie->producer);
    free_studio(serie->studio);
    free_str_array_struct(serie->contentTag);
    free_key_value_array_struct(serie->key_value_array);
    free_season_array_struct(serie->seasons);
  }
  free(serie);
  return 0;
}

int set_serie_default_parameters(SERIE *serie, int numb_of_keys,  int seasons,  int episodes, int tags) {
  if(serie != NULL) {

    resize_key_value_array_struct(serie->key_value_array, numb_of_keys);
    resize_str_array_struct(serie->contentTag, tags);
    resize_season_array_struct(serie->seasons, seasons, episodes);
    //printf("numb_of_tags : %d, numb_of_season : %d, num_of_episodes : %d\n", tags, seasons, episodes);
  }

  return 0;
}

int init_serie_struct(SERIE *serie, size_t keys_values_size, size_t number_of_season, size_t number_of_episodes, int content_tags) {
  if(serie != NULL) {
    serie->year = (char*) malloc(sizeof(char));
    serie->director = malloc(sizeof(*serie->director));
    serie->producer = malloc(sizeof(*serie->producer));
    serie->studio =  malloc(sizeof(*serie->studio));
    serie->contentTag =  malloc(sizeof(*serie->contentTag));
    //serie->cats = NULL; 
    serie->key_value_array = malloc(sizeof(*serie->key_value_array));
    serie->seasons =  malloc(sizeof(*serie->seasons));

    if(serie->director != NULL)
      init_director_struct(serie->director);

    if(serie->producer != NULL)
      init_director_struct(serie->producer);

    if(serie->studio != NULL)
      init_studio_struct(serie->studio);

    if(serie->contentTag != NULL)
      init_str_array_struct(serie->contentTag, content_tags);

    if(serie->key_value_array != NULL)
      init_key_value_array_struct(serie->key_value_array, keys_values_size);

    if(serie->seasons != NULL)
      init_season_array_struct(serie->seasons, number_of_season, number_of_episodes); 
    //init_array(&(serie->contentTag), array_size, 5, "");
  }  
  return 0;
}

int set_serie_year(SERIE *serie, char *year) {
  char *new_year;

  if(serie != NULL && year != NULL) {
    new_year = (char*) realloc(serie->year, (strlen(year)+1) * sizeof(char));
    if(new_year != NULL) {
      serie->year = new_year;
      sprintf(serie->year, "%s", year);
    }
  }

  return 0;
}

int print_serie(SERIE *serie) {
  if(serie != NULL) {
    printf("\"Serie\" : {\n");
    printf("\tYear : %s,\n", serie->year);
    print_director(serie->director, "\t", "\t\t");
    print_director(serie->producer,  "\t", "\t\t");
    print_studio(serie->studio, "\t", "\t\t");
    print_array_str(serie->contentTag, "\t", "\t\t", "\t\t", "\t\t\t");
    print_array_key_value(serie->key_value_array,"\t", "\t\t", "\t\t", "\t\t\t");
    print_array_season(serie->seasons, "\t", "\t\t", "\t\t\t", "\t\t\t\t");
    printf("}\n");
  }
  return 0;
}

int init_date(bson_t **bson, char *field, char *str_date) {
  STR_ARRAY *datePartArray = (STR_ARRAY *) malloc(sizeof(*datePartArray));
  STR_ARRAY *hoursPartArray = (STR_ARRAY *) malloc(sizeof(*hoursPartArray));
  struct tm year = { 0 };

  init_default_str_array_struct(datePartArray);
  init_default_str_array_struct(hoursPartArray);

  if(hoursPartArray != NULL) {
    parseDate(str_date, "[0-9]{2}:[0-9]{2}:[0-9]{2}", "[0-9]{2}", hoursPartArray);
    //print_array_str(hoursPartArray,"","\t", "\t\t", "\t\t\t");
    year.tm_hour = atoi(hoursPartArray->elements[0].value) - 1; 
    year.tm_min = atoi(hoursPartArray->elements[1].value) - 1; 
    year.tm_sec = atoi(hoursPartArray->elements[2].value); 
    //print_array_str(hoursPartArray, "", "\t", "\t", "\t\t");
  }

  if(datePartArray != NULL) {
    parseDate(str_date, "[0-9]{4}-[0-9]{2}-[0-9]{2}", "[0-9]+", datePartArray);
    year.tm_year = atoi(datePartArray->elements[0].value) - 1900;  /* years are 1900-based */
    year.tm_mon = atoi(datePartArray->elements[1].value) - 1;  /* months are 0-based */
    year.tm_mday = atoi(datePartArray->elements[2].value);
    //print_array_str(datePartArray, "", "\t", "\t", "\t\t");
  }

  BSON_APPEND_DATE_TIME(*bson, field, mktime(&year) * 1000);
  
  free_str_array_struct(datePartArray);
  free_str_array_struct(hoursPartArray);

  return 0;
}

int int_date_(bson_t *bson, char *field, char *str_date) {
  init_date(&bson, field, str_date);
  return 0;
}

int init_director(bson_t *director_bson, DIRECTOR *director) {

  if(director_bson != NULL && director != NULL) {
    BSON_APPEND_UTF8(director_bson, "name", director->name);
    init_date(&director_bson, "startYear", director->startYear);
    init_date(&director_bson, "endYear", director->endYear);
    init_date(&director_bson, "birthYear", director->bithYear);
  }

  return 0;
}

int init_studio(bson_t *studio_bson, STUDIO *studio) {
  if(studio != NULL) {
    BSON_APPEND_UTF8(studio_bson, "name", studio->name);
    BSON_APPEND_UTF8(studio_bson, "city", studio->city);
    BSON_APPEND_UTF8(studio_bson, "country", studio->country);
    init_date(&studio_bson, "startYear", studio->startYear);
    init_date(&studio_bson, "endYear", studio->endYear);
    init_date(&studio_bson, "birthYear", studio->bithYear);
    BSON_APPEND_UTF8(studio_bson, "fonder", studio->fonder);
  }
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
  int_date_(&child2, "startYear", "");
  int_date_(&child2, "endYear", "");
  int_date_(&child2, "birthYear", "");
  int_date_(&child2, "deathYear", "");
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
  //init_actor(&actor);
  bson_append_array_end (cast, &actor);

  BSON_APPEND_ARRAY_BEGIN(cast, "awards", &award);
  //init_award(&award);
  bson_append_array_end(cast, &award);

  return 0;
}

int init_content_tag(bson_t **document,  STR_ARRAY *contentTag) {
  bson_t tag;
  char buf[16];
  size_t  keylen;
  const char *key;

  if(document != NULL && contentTag != NULL) {
    BSON_APPEND_ARRAY_BEGIN(*document, "contentTag", &tag);
    for(int i = 0; i <contentTag->length; i++) {
      keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
      bson_append_utf8(&tag, key, (int)keylen, contentTag->elements[i].value, -1);
    }
    bson_append_array_end(*document, &tag);
  }

  return 0;
}

int init_video(bson_t *video_bson, VIDEO *video, int index) {
  char buf[16];
  size_t keylen;
  bson_t child2;
  const char *key;

  if(video_bson != NULL && video != NULL) {
    keylen = bson_uint32_to_string(index, &key, buf, sizeof buf);
    bson_append_document_begin(video_bson, key, (int)keylen, &child2);
    BSON_APPEND_UTF8(&child2, "title", video->title);
    BSON_APPEND_UTF8(&child2, "category", video->category);
    BSON_APPEND_UTF8(&child2, "summary", video->summary);
    BSON_APPEND_UTF8(&child2, "url", video->url);
    BSON_APPEND_UTF8(&child2, "length", video->length);
    BSON_APPEND_UTF8(&child2, "censor_rating", video->censor_rating);
    //int_date_(&child2, "created_at");
    //int_date_(&child2, "upDated_at");
    bson_append_document_end(video_bson, &child2);
  }

  return 0;
}

int init_season(bson_t *season_bson, SEASON *season, int index) {
  bson_t videos;
  char buf[16];
  size_t keylen;
  bson_t child2;
  const char *key;

  if(season_bson != NULL && season != NULL) {
    keylen = bson_uint32_to_string(index, &key, buf, sizeof buf);
    bson_append_document_begin(season_bson, key, (int)keylen, &child2);
    BSON_APPEND_UTF8(&child2, "title", season->title);
    int_date_(&child2, "date", season->date);
    BSON_APPEND_UTF8(&child2, "summary", season->summary);
    BSON_APPEND_INT32(&child2, "number", season->number);
    BSON_APPEND_ARRAY_BEGIN(&child2, "videos", &videos);

    for(int i = 0; i < season->videos->length; i++) {
      init_video(&videos, &(season->videos->elements[i]), i);
    }
    
    bson_append_array_end(&child2, &videos);
    bson_append_document_end(season_bson, &child2); 
  }

  return 0;
}

int init_seasons(bson_t **document, SEASON_ARRAY *seasons) {
  bson_t season_bson;

  if(*document != NULL && seasons != NULL) {
    BSON_APPEND_ARRAY_BEGIN(*document, "seasons", &season_bson);
    for(int i = 0; i < seasons->length; i++) {
      init_season(&season_bson, &(seasons->elements[i]), i);
    }
    bson_append_array_end(*document, &season_bson);
  }
  return 0;
}

int init_keys_and_values(bson_t **bson, KEY_VALUE_ARRAY *array) {
  if(array != NULL) {
    for(int i = 0; i < array->length; i++) {
      BSON_APPEND_UTF8(*bson, array->elements[i].key, array->elements[i].value);
    }
  }
  return 0;
}

int serie_to_bson(bson_t **document, SERIE *serie) {
  //bson_t director, producer, studio, cast;

  if(serie != NULL) {
    init_keys_and_values(&(*document), serie->key_value_array);
    init_date(&(*document), "year", serie->year);
    //BSON_APPEND_DOCUMENT_BEGIN(*document, "director", &director);
    //init_director(&director, serie->director);
    //bson_append_document_end(*document, &director);
    //BSON_APPEND_DOCUMENT_BEGIN(*document, "producer", &producer);
    //init_director(&producer, serie->producer);
    //bson_append_document_end(*document, &producer);
    //BSON_APPEND_DOCUMENT_BEGIN(*document, "studio", &studio);
    //init_studio(&studio, serie->studio);
    //bson_append_document_end(*document, &studio);
    //BSON_APPEND_DOCUMENT_BEGIN(*document, "cast", &cast);
    //init_cast(&cast);
    //bson_append_document_end(*document, &cast);
    //init_content_tag(&(*document), serie->contentTag);
    init_seasons(&(*document), serie->seasons);
  }
  return 0;
}

int serie_to_set_bson(bson_t **document, SERIE *serie) {
  bson_t set;
  bson_t *serie_set;
  //bson_t director, producer, studio, cast;
  
  if(serie != NULL) {
    puts("serie_to_set_bson");
    serie_set = &set;
    BSON_APPEND_DOCUMENT_BEGIN(*document, "$set", &set);
    init_keys_and_values(&serie_set, serie->key_value_array);
    init_date(&serie_set, "year", serie->year);
    init_seasons(&serie_set, serie->seasons);
    bson_append_document_end(*document, &set);
  }
  return 0;
}

char* deserialize_date(struct json_object *date_json) {
  char *res = NULL;
  json_object *timestamp_json = getObj_rec(date_json, "/$date/$numberLong");

  if(timestamp_json != NULL) {
    timestamp_to_utc((char *)json_object_get_string(timestamp_json), &res);
  }

  return res;
}
int deserialize_year(SERIE *serie, struct json_object *year) {
  char *date = deserialize_date(year);

  if(serie != NULL && date != NULL) {
    set_serie_year(serie, date);
    //printf("%s\n", json_object_get_string(year));
    free(date);
  }

  return 0;
}

int deserialize_cast(struct json_object *cast) {
  if(cast != NULL) {
    printf("Cast : %s\n", json_object_get_string(cast));
  }
  return 0;
}

int deserialize_director(DIRECTOR *director, struct json_object *director_json) {
  struct json_object *nameObj, *startYearObj, *endYearObj, *birthYearObj;
  char *startYear, *endYear, *birthYear;
  //char *date = deserialize_date(year);

  if(director != NULL && director_json != NULL) {
    nameObj = json_object_object_get(director_json, "name");
    startYearObj = json_object_object_get(director_json, "startYear");
    endYearObj = json_object_object_get(director_json, "endYear");
    birthYearObj = json_object_object_get(director_json, "bithYear");

    set_director_name(director, (char*) json_object_get_string(nameObj));
    
    startYear = deserialize_date(startYearObj);
    endYear = deserialize_date(endYearObj);
    birthYear = deserialize_date(birthYearObj);

    if(startYear != NULL)
      set_director_startYear(director, startYear);
    
    if(endYear != NULL)
      set_director_endYear(director, endYear);

    if(birthYear != NULL)
      set_director_bithYear(director, birthYear);

    free(startYear);
    free(endYear);
    free(birthYear);
  }
  return 0;
}

int deserialize_studio(STUDIO *studio, struct json_object *studio_json) {
  char *startYear, *endYear, *birthYear;
  struct json_object *nameObj, *cityObj, *countryObj, *fonderObj, *startYearObj, *endYearObj, *birthYearObj;

  if(studio != NULL && studio_json != NULL) {
    nameObj = json_object_object_get(studio_json, "name");
    cityObj = json_object_object_get(studio_json, "city");
    countryObj = json_object_object_get(studio_json, "country");
    fonderObj = json_object_object_get(studio_json, "fonder");
    startYearObj = json_object_object_get(studio_json, "startYear");
    endYearObj = json_object_object_get(studio_json, "endYear");
    birthYearObj = json_object_object_get(studio_json, "bithYear");

    set_studio_name(studio, (char*) json_object_get_string(nameObj));
    set_studio_city(studio, (char*) json_object_get_string(cityObj));
    set_studio_country(studio, (char*) json_object_get_string(countryObj));
    set_studio_fonder(studio, (char*) json_object_get_string(fonderObj));

    startYear = deserialize_date(startYearObj);
    endYear = deserialize_date(endYearObj);
    birthYear = deserialize_date(birthYearObj);

    if(startYear != NULL)
      set_studio_startYear(studio, startYear);
    
    if(endYear != NULL)
      set_studio_endYear(studio, endYear);

    if(birthYear != NULL)
      set_studio_bithYear(studio, birthYear);

    free(startYear);
    free(endYear);
    free(birthYear);
  }
  return 0;
}

int numb_of_tags(struct json_object *tags) {
  int numb = 0;

  if(tags != NULL && json_object_get_type(tags) == json_type_array) {
    numb = json_object_array_length(tags);
  }

  return numb;
}

int deserialize_tags(STR_ARRAY *contentTag, struct json_object *tags) {
  struct json_object *tag;

  if(contentTag != NULL && tags != NULL && json_object_get_type(tags) == json_type_array) {
    for(int i = 0; i < json_object_array_length(tags); i++) {
      tag = json_object_array_get_idx(tags, i);
      if(json_object_get_type(tag) == json_type_string) {
        set_str_value(&(contentTag->elements[i]), (char*)json_object_get_string(tag));
        //printf("tag : %s\n", json_object_get_string(tag));
      }
    }
  }

  return 0;
}

int deserialize_video(VIDEO *video, struct json_object *video_json) {
  struct json_object *titleObj, *summaryObj, *categoryObj, *lengthObj, *urlObj, *censor_ratingObj;

  if(video != NULL && video_json != NULL) {
    titleObj = json_object_object_get(video_json, "title");
    summaryObj = json_object_object_get(video_json, "summary");
    categoryObj = json_object_object_get(video_json, "category");
    lengthObj = json_object_object_get(video_json, "length");
    urlObj = json_object_object_get(video_json, "url");
    censor_ratingObj = json_object_object_get(video_json, "url");

    set_video_title(video, (char*)json_object_get_string(titleObj));
    set_video_category(video, (char*) json_object_get_string(categoryObj));
    set_video_summary(video, (char*)json_object_get_string(summaryObj));
    set_video_url(video, (char*)json_object_get_string(urlObj));
    set_video_length(video, (char*)json_object_get_string(lengthObj));
    set_video_censor_rating(video, (char*) json_object_get_string(censor_ratingObj));
  }

  return 0;
}

int deserialize_videos(VIDEO_ARRAY *videos, struct json_object *videosObj) {
  struct json_object *videoObj;

  if(videos != NULL && videosObj != NULL && json_object_get_type(videosObj) == json_type_array) {
    for(int i = 0; i < json_object_array_length(videosObj); i++) {
      videoObj = json_object_array_get_idx(videosObj, i);
      if(videoObj != NULL) {
        deserialize_video(&(videos->elements[i]), videoObj);
      }
    }
  }
  return 0;
}

int deserialize_season(SEASON *season, struct json_object *season_json) {
  char *date;
  struct json_object *titleObj, *summaryObj, *numberObj, *dateObj, *videosObj;

  if(season != NULL && season_json != NULL) {
    titleObj = json_object_object_get(season_json, "title");
    summaryObj = json_object_object_get(season_json, "summary");
    numberObj =  getObj_rec(season_json, "/number/$numberInt");
    dateObj = json_object_object_get(season_json, "date");
    videosObj = json_object_object_get(season_json, "videos");

    set_season_title(season,(char*)json_object_get_string(titleObj));
    set_season_summary(season, (char*)json_object_get_string(summaryObj));
    season->number = json_object_get_int(numberObj);
    date = deserialize_date(dateObj);

    if(date != NULL)
      set_season_date(season, date);
    //printf("NUMBER : %ld\n", json_object_get_int(numberObj));
    deserialize_videos(season->videos, videosObj);
    free(date);
  }

  return 0;
}

int numb_of_episodes(struct json_object *seasons_json) {
  int numb = 0;
  struct json_object *season_json, *videosObj;

  if(seasons_json != NULL && json_object_get_type(seasons_json) == json_type_array) {
    for(int i = 0; i < json_object_array_length(seasons_json); i++) {
      season_json = json_object_array_get_idx(seasons_json, i);

      if(season_json != NULL) {
        videosObj = json_object_object_get(season_json, "videos");
        if(videosObj != NULL && json_object_get_type(videosObj) == json_type_array) {
          if(numb < json_object_array_length(videosObj))
            numb = json_object_array_length(videosObj);
        }
      }
    }
  }

  return numb;
}

int numb_of_seasons(struct json_object *seasons_json) {
  int numb = 0;

  if(seasons_json != NULL && json_object_get_type(seasons_json) == json_type_array) {
    numb = json_object_array_length(seasons_json);
  }

  return numb;
}

int deserialize_seasons(SEASON_ARRAY *seasons, struct json_object *seasons_json) {
  struct json_object *season_json;

  if(seasons != NULL && seasons_json != NULL && json_object_get_type(seasons_json) == json_type_array) {
    for(int i = 0; i < json_object_array_length(seasons_json); i++) {
      season_json = json_object_array_get_idx(seasons_json, i);
      if(season_json != NULL) {
        deserialize_season(&(seasons->elements[i]), season_json);
      }
    }
  }

  return 0;
}

int deserialize_bykey(KEY_VALUE_ARRAY *array, struct json_object *obj, char *key, int index) {
  struct json_object *targetObj;

  if(obj != NULL && key != NULL && array != NULL) {
    targetObj = json_object_object_get(obj, key);

    if(targetObj != NULL && json_object_get_type(targetObj) == json_type_string) {
      set_key_value(&(array->elements[index]), key, (char *) json_object_get_string(targetObj));
    }
  }

  return 0;
}

int set_serie_parameters(struct json_object *serie_json, SERIE *serie, int numb_of_keys) {
  int seasons, episodes/*, tags*/;
  struct json_object *seasons_json = getObj_rec(serie_json, "/seasons");
  //struct json_object *tags_json = getObj_rec(serie_json, "/contentTag");
  //puts("set_serie_parameters");
  if(serie != NULL) {
    //tags = numb_of_tags(tags_json); 
    seasons = numb_of_seasons(seasons_json);
    episodes = numb_of_episodes(seasons_json);
    resize_key_value_array_struct(serie->key_value_array, numb_of_keys);
    //resize_str_array_struct(serie->contentTag, tags);
    init_season_array_struct(serie->seasons, seasons, episodes);
  }

  return 0;
}

int bson_to_serie(SERIE *serie, bson_t *document) {
  char *str;
  struct json_object *serie_json = NULL;
  str = bson_as_canonical_extended_json(document, NULL);

  if(str != NULL && serie != NULL) {
    serie_json = getJson(str);
    set_serie_parameters(serie_json, serie, 3);

    deserialize_year(serie, getObj_rec(serie_json, "/year"));
    deserialize_bykey(serie->key_value_array, serie_json, "title", 0);
    deserialize_bykey(serie->key_value_array, serie_json, "img", 1);
    deserialize_bykey(serie->key_value_array, serie_json, "viewCount", 2);

    //deserialize_bykey(serie->key_value_array, serie_json, "summary", 3);
    //deserialize_director(serie->director, getObj_rec(serie_json, "/director"));
    //deserialize_director(serie->producer, getObj_rec(serie_json, "/producer"));
    //deserialize_studio(serie->studio, getObj_rec(serie_json, "/studio"));
    //deserialize_cast(getObj_rec(serie_json, "/cast"));
    //deserialize_tags(serie->contentTag, getObj_rec(serie_json, "/contentTag"));
    deserialize_seasons(serie->seasons, getObj_rec(serie_json, "/seasons"));
    //printf("tag : %s\n", json_object_get_string(serie_json));
    //print_serie(serie);
    bson_free(str);
    json_object_put(serie_json);
  }

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
        printf("Season : %s\n", json_object_get_string(season));
      }
    }

    free(season_title);
  }

  return exist;
}

int exist_serie(mongoc_client_t *client, bson_t *selector, char *dbName, char *documentName, SERIE *serie) {
  int exist = 0;
  const bson_t *document;
  mongoc_cursor_t *cursor = NULL;
  
  if(selector != NULL && client != NULL) {
    find_document(client, dbName, documentName, selector, &cursor);
    if(mongoc_cursor_next(cursor, &document)) {
      //print_bson(document);
      bson_to_serie(serie, (bson_t *)document);
      exist = 1;
    } 
  }

  bson_free(cursor);
  return exist;
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
  //size_t keysLen = 3;
  //struct json_object *titleObj,  *imgObj, *videoObj;
  serie = malloc(sizeof(*serie));

  if(serie != NULL && video != NULL) {
    printf("SaveSerie : \n");
    /*titleObj = getObj_rec(video, TITLE_FIELD);
    imgObj = getObj_rec(video, IMG_FIELD);
    videoObj = getObj_rec(video, VIDEOID_FIELD);*/
    
    //add_value(&(serie)->keys, "videoId", 0);
    //add_value(&(serie)->keys, "title", 1);
    //add_value(&(serie)->keys, "img", 2);
    //add_value(&(serie)->values, (char *)json_object_get_string(videoObj), 0);
    //add_value(&(serie)->values, (char *)json_object_get_string(titleObj), 1);
    //add_value(&(serie)->values, (char *)json_object_get_string(imgObj), 2);
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