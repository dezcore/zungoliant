#ifndef TESTDB_H_
#define TESTDB_H_

#include <stdio.h>
#include <stdlib.h>

#include "../youtube/page.h"
#include "../utility.h"

int test_str();
int test_exist();
int test_studio();
int test_director();
int test_str_array();
int test_key_value();
int test_parse_date();
int test_title_regex();
int test_video_array();
int test_str_to_bson();
int test_season_array();
int test_ping_mongodb();
int test_video_struct();
int test_find_document();
int test_season_struct();
int test_serie_to_bson();
int test_bson_to_serie(); 
int test_match_patterns();
int test_matching_title();
int test_delete_document();
int test_update_document();
int test_key_value_array();
int test_title_episode_regex();
int test_find_document_by_regex();
int test_insert_document(SERIE *serie);
int test_create_serie(SERIE **res, int save);
#endif