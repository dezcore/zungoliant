#include "./../include/utility.h"

int init_str_struct(STR *str) {
  if(str != NULL) {
    str->value =(char*) malloc(sizeof(*str->value));
  }
  return 0;
}

int set_str_value(STR *str, char *value) {
  char *new_value;

  if(str != NULL && value != NULL) {
    new_value = (char*) realloc(str->value, (strlen(value)+1) * sizeof(char));
    if(new_value != NULL) {
      str->value = new_value;
      sprintf(str->value, "%s", value);
    }
  }

  return 0;
}

int free_str(STR *str) {
  if(str != NULL) {
    free(str->value);
    free(str);
  }
  return 0;
}

int print_str(STR *str, char *tabs, char *subtabs) {
  if(str != NULL) {
    printf(tabs);
    printf("\"Str\" : {\n");
    printf(subtabs);
    printf("Value : %s\n", str->value);
    printf(tabs);
    printf("}\n");
  }
  return 0;
}

int init_default_str_array_struct(STR_ARRAY *array) {
    if(array != NULL) {
        array->elements = NULL;
        array->length = 0;
    }
    return 0;
}

int init_str_array_struct(STR_ARRAY *array, size_t length) {
    STR *element;
    if(array != NULL && array->elements == NULL && array->length == 0) {
        array->elements = malloc(length * sizeof(array->elements));
        if(array->elements != NULL) {
            for(int i = 0; i < length; i++) {
                element = &(array->elements[i]);
                init_str_struct(element);
            }
            array->length = length;
        }
    }
    return 0;
}

int free_str_array_struct(STR_ARRAY *array) {
    STR *element;
    if(array != NULL) {
        if(0 < array->length) {
            for(int i= 0; i < array->length; i++) {
                element = &(array->elements[i]);
                free(element->value);
            }
        }
        free(array->elements);
    }
    free(array);
  return 0;
}

int resize_str_array_struct(STR_ARRAY *array, size_t length) {
    STR *elements;

    if(array != NULL && array->length < length) {
        elements = (STR*) realloc(array->elements, length * sizeof(*array->elements));
        if(elements != NULL) {
            for(int i = array->length; i < length; i++) {
                init_str_struct(&(elements[i]));
            }
            array->elements = elements;
            array->length = length;
        }
    }
    return 0;
}

int print_array_str(STR_ARRAY *array, char *tabs, char* subtabs, char *str_tabs, char *str_subtabs) {
  if(array != NULL) {
    printf("%s", tabs);
    printf("\"STR_Array\" : [\n");
    for(int i = 0; i < array->length; i++) {
      print_str(&(array->elements[i]), str_tabs, str_subtabs);
      if(i < array->length -1) 
        printf("%s,\n", subtabs);
    }
    printf("%s]\n", tabs);
  }
  return 0;
}

int get_matchIndex(char **str, char *pattern, int *start, int *end, int target) {
    regex_t reg;
    size_t nmatch;

    if(!regcomp(&reg, pattern, REG_EXTENDED)) {
        nmatch = reg.re_nsub;
        regmatch_t m[nmatch + 1];

        if(!regexec(&reg, *str, nmatch + 1, m, 0)) {
            if(target == 0 || target == 3)
                *start = m[0].rm_so;
            
            if(target == 1 || target == 3)
                *end = m[0].rm_eo;
        }
    }
    regfree(&reg);
    return 0;
}

int trim(char **str) {
    char *res = NULL;
    int start = -1, end = -1;
    size_t len = *str != NULL ? strlen(*str) : 0;

    if(*str != NULL) {
        res = (char*) calloc(len, sizeof(char));

        if(res != NULL) {
            get_matchIndex(&(*str), "^[ \t]+", &end, &start, 1);
            get_matchIndex(&(*str), "[ \t]+$", &end, &start, 0);

            if(start != end && start != -1) {
                memcpy(res, &(*str)[start], (end-start));
                sprintf(*str, "%s", res);
            }
        }
    }
    free(res);
    return 0;
}

int get_pwd(char **res, char *concatPath) {
    *res = (char*) malloc(PWD_STR_LEN * sizeof(char));

    if(*res != NULL) {
        if(getcwd(*res, PWD_STR_LEN) == NULL) {
            perror("getcwd() error");
        }
        sprintf(*res, "%s%s", *res, concatPath); 
    }
    
    return 0;
}

int match_pattern(char *str, char *pattern) {
    int match = 0;
    regex_t reg;
    size_t nmatch;

    if(str != NULL && pattern != NULL && !regcomp(&reg, pattern, REG_EXTENDED)) {
        nmatch = reg.re_nsub;
        regmatch_t m[nmatch + 1];

        if(!regexec(&reg, str, nmatch + 1, m, 0)) {
            match = 1;
        }
        regfree(&reg);
    }
    return match;
}

int dup_str(char **res, char *str) {
    int len = strlen(str) + 1;
    if(*res == NULL)
        *res = (char*) calloc(len, sizeof(char));

    if(*res != NULL) {
        sprintf(*res, "%s", str);
        //strcpy(cpy, str);
    }
    return 0;
}

int sub_str(char **res, char *str, int start, int end) {
    int length = end-start;
    char *tmp = (char*) calloc(length+1, sizeof(char));

    if(*res == NULL)
        *res = (char*) malloc( (length+1) * sizeof(char));  

    if(str != NULL && *res != NULL && tmp) {
        strncpy(tmp, &str[start], length);
        tmp[length] = '\0';
        strcpy(*res, tmp);
        //sprintf(*res, "%s", tmp);
    }

    free(tmp);
    return 0;
}

int get_match(char *str, char *pattern, File *fifo) {
    regex_t reg;
    size_t nmatch;
    int start, end, curs = 0;
    char *strCpy = NULL,  *res = NULL;

    dup_str(&strCpy, str);

    if(strCpy != NULL && fifo != NULL && pattern != NULL  && !regcomp(&reg, pattern, REG_EXTENDED)) {
        nmatch = reg.re_nsub;
        regmatch_t m[nmatch + 1];

        while(!regexec(&reg, strCpy, nmatch + 1, m, 0)) {
            start = m[0].rm_so;
            end = m[0].rm_eo;
            curs += m[0].rm_eo;

            sub_str(&res, strCpy, start, end);
            sub_str(&strCpy, str, curs, strlen(str));

            if(res != NULL) {
                push(fifo, res);
                free(res);
                res = NULL;
            }
        }
        free(strCpy);
    }
    regfree(&reg);
    return 0;
}

int get_str_match(char *str, char *pattern, char **match) {
    char *res; 
    regex_t reg;
    size_t nmatch;
    int start, end;

    if(str != NULL && pattern != NULL && !regcomp(&reg, pattern, REG_EXTENDED)) {
        nmatch = reg.re_nsub;
        regmatch_t m[nmatch + 1];

        if(!regexec(&reg, str, nmatch + 1, m, 0)) {
            start = m[0].rm_so;
            end = m[0].rm_eo;
            res = (char*) malloc((end-start+1) * sizeof(char));

            if(res != NULL) {
                strncpy(res, &str[start], end-start);
                res[end-start] = '\0';
                *match = res;
            }
        }
    }

    return 0;
}

int get_title_episode(char *title) {
    int res = 1;
    char *episode = NULL, *digit = NULL;
    const char *digit_regex = "[0-9]{1,2}";
    const char *episode_regex = "(([EÉeé][Pp][Ii]?[Ss]?[Oo]?[Dd]?[EÉeé]?[ ]?[0-9]{1,2})|([0-9]{1,2}[-&][0-9]{1,2})|([Vv][Oo][Ll][Uu]?[Mm]?[Ee]?[ ]+[0-9]{1,2})|([0-9]{1,2}( |ère )(([Pp][Aa][Rr][Tt][Ii][Ee])|([EÉeé][Pp][Ii]?[Ss]?[Oo]?[Dd]?[EÉeé]?)))|([^(Saison)] [0-9]{1,2}[ ])|(\\([0-9]{1,2}\\)))";
    if(title != NULL) {
        get_str_match(title, (char*) episode_regex, &episode);
        if(episode != NULL) {
            get_str_match(episode, (char*)digit_regex, &digit);
            if(digit != NULL) {
                res = atoi(digit);
                //printf("get_title_episode : %s\n", digit);
            }
        }
    }

    free(digit);
    free(episode);
    return res;
}

int get_title_season(char *title) {
    int res = 1;
    char *season = NULL, *digit = NULL;
    const char *season_regex = "(([Ss]aison))[ ]+[0-9]{1,2}";
    const char *digit_regex = "[0-9]{1,2}";
    
    if(title != NULL) {
        get_str_match(title, (char*) season_regex, &season);
        if(season != NULL) {
            get_str_match(season, (char*)digit_regex, &digit);
            if(digit != NULL) {
                res = atoi(digit);
                //printf("get_title_season : %s\n", digit);
            }
        }
    }

    free(digit);
    free(season);
    return res;
}

int join_file_element(File *file, char **str, char *delimiter, int start_delimiter, int numb_of_words) {
    Element *current;
    int cpt_words = 0;
    char *res = (char*) calloc(JOIN_STR_LEN, sizeof(char));

    if(file != NULL && res != NULL) {
        current = file->head;
        
        if(start_delimiter)
            sprintf(res, "%s", delimiter);

        while(current != NULL) {
            strcat(res, current->value);
            strcat(res, delimiter);

            if(0 < numb_of_words) {
                cpt_words++;
                if(cpt_words == numb_of_words)
                    break;
            }
            
            current = current->next;
        }

        *str = (char*)realloc(*str, (strlen(res)+1) * sizeof(char));
        
        if(*str != NULL)
            strcpy(*str, res);
    }
    free(res);
    return 0;
}

int fifoToArray(File *fifo, STR_ARRAY *array) {
    int cpt = 0;
    Element *current;

    if(fifo != NULL && array != NULL) {
        current = fifo->head;
        init_str_array_struct(array, fifo->size);

        while(current != NULL) {
            set_str_value(&(array->elements[cpt]), current->value);
            cpt++;
            current = current->next;
        }
    }

    return 0;
}

int parseDate(char *str_date, char *datePartRegex, char *datePartDelimiter, STR_ARRAY *array) {
    char *part = NULL;
    File *fifo = malloc(sizeof(*fifo));
    get_str_match(str_date, datePartRegex, &part); 
    fifo_init(fifo);

    if(part != NULL) {
        get_match(part, datePartDelimiter, fifo);
        if(fifo != NULL) {
            //display(fifo);
            fifoToArray(fifo, array);
            freeFile(fifo);
        }
        free(part);
    }

    return 0;
}

char* complete_number(int numb) { 
    char *res = malloc(20 *sizeof(char));

    if(9 < numb)
        sprintf(res, "%d", numb);
    else 
        sprintf(res, "0%d", numb);

    return res;  
}

int timestamp_to_utc(char *date, char **res) {
    char *eptr;
    long time_long;
    struct tm * time;
    char *month, *day, *hour, *min, *sec;

    *res = (char*) malloc(100 *sizeof(char));

    if(date != NULL) {
        time_long = strtol(date, &eptr, 10)/1000;
        time = gmtime(&time_long);
        month = complete_number(time->tm_mon+1);
        day = complete_number(time->tm_mday);
        hour = complete_number(time->tm_hour+1);
        min = complete_number(time->tm_min+1);
        sec = complete_number(time->tm_sec);
        sprintf(*res, "%d-%s-%sT%s:%s:%sZ\n", (time->tm_year + 1900),month, day, hour, min, sec);
        free(month);
        free(day);
        free(hour);
        free(min);
        free(sec);
        
    }

    return 0;
}