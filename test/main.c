#include <stdio.h>
#include <stdlib.h>
#include "./../include/testfile.h"
#include "./../include/testfifo.h"
#include "./../include/testy.h"
#include "./../include/testzregex.h"
#include "./../include/test/testdb.h"

int test_fifo() {
    test_init();
    //test_push();
    //test_pop();
    //test_filetoFifo();
    //test_loadFile();
    //test_printContent();    
    //test_createFile();
    //test_appendStrToFile();
    return 0;
}

int test_dowload() {
    test_downloadPage();
    //test_parseFile();
    return 0;
}

int test_regex() {
    //test_regex_replace(); 
    test_downloadPage_and_replace();
    return 0;
}

int test_json() {
    //test_video_page_items();
    //test_video_page_channel();
    test_channel_page_home();
    return 0;
}

int test_db() {
    //test_ping_mongodb();
    //test_str_to_bson();
    //test_insert_document();
    test_matching_title();
    return 0;
}

int main() {
    //while(1);    
    //test_regex();
    //test_json();
    test_db();
    return 0;
}