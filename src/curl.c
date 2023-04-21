#include "./../include/curl.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int trim(char * s) {
    char * p = s;
    int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
    return 0;
} 

int downloadPage(char *url, char *output) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        trim(url); 
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        fp = fopen(output,"wb");

        if(fp) {
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);

            if(res == CURLE_OK)
                printf("CURLE_OK\n");
            else
                printf("curl error : %d\n", res);

            fclose(fp);
        } else {
            printf("test in else : %s\n", output);
        }  

        curl_easy_cleanup(curl);
        curl_global_cleanup();
    } else {
        printf("test in else (curl) : %s\n", output);
    }
    
    return 0;
}