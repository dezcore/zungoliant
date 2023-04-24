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

int regex_replace(char **str, const char *pattern, const char *replace) {
    regex_t reg;

    //if regex can't commpile pattern, do nothing
    if(!regcomp(&reg, pattern, REG_EXTENDED)) {
        size_t nmatch = reg.re_nsub; 
        regmatch_t m[nmatch + 1];
        const char *rpl, *p;
        // count back references in replace
        int br = 0;
        p = replace;
        while(1) { 
            while(*++p > 31); 
            if(*p) br++; 
            else break;
        } // if br is not equal to nmatch, leave
        if(br != nmatch) return 0;
        // look for matches and replace
        char *new;
        while(!regexec(&reg, *str, nmatch + 1, m, REG_NOTBOL)) {
            // make enough room
            new = (char *)malloc(strlen(*str) + strlen(rpl));
            if(!new) exit(EXIT_FAILURE);
            *new = 0;
            p = rpl = replace;
            int c;
            strncat(new, *str, m[0].rm_so); // test before pattern
            for(int k=0; k<nmatch; k++) {
                while(*++p > 16); // skip printable char
                c = *p;  // back referenc (e.g. \1, \2, ...)
                strncat(new, rpl, p - rpl); // add head of rpl
                // concat match
                strncat(new, *str + m[c].rm_so, m[c].rm_eo - m[c].rm_so);
                rpl = p++; // skip back reference, next match
            }
            strcat(new, p ); // trailing of rpl
            strcat(new, *str + m[0].rm_eo); // trainling text in *str
            free(*str);
            *str = strdup(new);
            free(new);
        }
        // ajust size
        *str = (char *)realloc(*str, strlen(*str) + 1);
    } else {
        printf("Could not compile regex: %s\n", replace);
    }

    return 0;
}