#include "./../include/ybot.h"

int init_ybot(Ybot **bot) {
    *bot = malloc(sizeof(*bot));

    if(*bot != NULL) {
        (*bot)->urls_fifo = init();
        init_yfile(&(*bot)->data_fifo);
    }

    return 0;
}

int free_ybot(Ybot *bot) {
    if(bot != NULL) {
        freeFile(bot->urls_fifo);
        free_yfile(&(bot->data_fifo));
        free(bot);
    }

    return 0;
}

int run_ybot() {
    //char * str = (char *) malloc(STR_SIZE * sizeof(char*));
    Ybot *bot = NULL; 
    Ydata *data = NULL;

    init_ybot(&bot);
    //sprintf(str, "%s", "test");
    //push(bot->urls_fifo, str);
    //display(bot->urls_fifo);

    push_ydata(&bot->data_fifo, "title1", "img1", "videoId1");
    push_ydata(&bot->data_fifo, "title2", "img2", "videoId2");
    push_ydata(&bot->data_fifo, "title3", "img3", "videoId3");
    push_ydata(&bot->data_fifo, "title4", "img4", "videoId4");
    pop_yfile(&bot->data_fifo, &data);
    print_yfile(bot->data_fifo);
    //print_ydata(data);
    //free(str);
    free_ydata(data);
    free_ybot(bot);
    return 0;
}