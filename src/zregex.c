#include "./../include/zregex.h"

//char *expression = malloc(EXPRESSION_SIZE * sizeof(char));// "^(-)?([0-9]+)((,|.)([0-9]+))?\n$"
int search(char *filePath, char *expression) {
    int reti;
    regex_t regex;
    char msgbuf[100];
    char* fileContent = (char*) malloc(sizeof(char));
    reti = regcomp(&regex, expression, 0);

    if(reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    fileContent = load_file(filePath, fileContent);
    reti = regexec(&regex, fileContent, 0, NULL, 0);

    if(!reti) {
        printf("Match : %s\n", fileContent);
    } else if (reti == REG_NOMATCH) {
        printf("No match\n");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);
    free(fileContent); 
    return 0;
}