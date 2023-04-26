#ifndef YBOT_H_
#define YBOT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../include/fifo.h"

typedef struct _Ybot {
    File *urls_fifo;
    Yfile *data_fifo;
} Ybot;

int run_ybot();
#endif