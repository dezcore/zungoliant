#ifndef TESTDB_H_
#define TESTDB_H_
#include <stdio.h>
#include <stdlib.h>
#include "./../../include/utility.h"

int test_exist();
int test_serie();
int test_studio();
int test_director();
int test_key_value();
int test_parse_date();
int test_video_array();
int test_str_to_bson();
int test_season_array();
int test_ping_mongodb();
int test_video_struct();
int test_find_document();
int test_season_struct(); 
int test_match_patterns();
int test_matching_title();
int test_delete_document();
int test_update_document();
int test_key_value_array();
int test_find_document_by_regex();
int test_insert_document(SERIE *serie);
#endif