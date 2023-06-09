#include "./../include/curl.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int downloadPage(char **url, char *output) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        trim(url);     
        curl_easy_setopt(curl, CURLOPT_URL, *url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);        
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Dark Secret Ninja/1.0");
        //curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1L);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
        fp = fopen(output,"wb");

        if(fp) {
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);

            if(res == CURLE_OK)
                printf("CURLE_OK (downloadPage)\n");
            else
                printf("curl error (downloadPage): %d\n", res);

            fclose(fp);
        }

        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
    
    return 0;
}

int downloadPage_withsystem(char *url, char *output) {
    char *command = (char*) malloc(COMMAND_SIZE * sizeof(char));

    if(url != NULL && command != NULL) {
        sprintf(command, "curl %s -L -o %s", url, output);

        if(system(command) != 0 ) {
            fprintf(stderr, "Impossible de lancer la commande : %s\n", command);
        }

        system(command);
        free(command);
    }

    return 0;
}

int downloadPage_bycontains(char **url, char *output, char* contains) {
    char *contents = NULL;  
    if(url != NULL && output != NULL) {
        downloadPage(url, output);
        getfileContents(&contents, output);
        if(contents != NULL && strstr(contents, contains) == NULL) {
            write_file(output, "", "w+");
            downloadPage_withsystem(*url, output);
        }
        free(contents);
    }

    return 0;
}