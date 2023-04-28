#include <stdio.h>
#include <stdlib.h>
#include "./../include/testfile.h"
#include "./../include/testfifo.h"
#include "./../include/testzregex.h"

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
    test_regex_replace(); 
    //test_downloadPage_and_replace();
    return 0;
}

int main() {    
    test_regex();
    return 0;
}