#include "./../include/ybot.h"

int init_ybot(Ybot **bot) {
    *bot = malloc(sizeof(*bot));

    if(*bot != NULL) {
        (*bot)->urls_fifo = init();
    }
    return 0;
}

int free_ybot(Ybot *bot) {
    if(bot != NULL) {
        free(bot);
    }

    return 0;
}

int run_ybot() {
    return 0;
}