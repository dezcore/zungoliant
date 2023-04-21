#include "./../include/parser.h" 

#define STR_LEN 100

struct res_html load_html_file(const char* filename) {
    FILE *fh = fopen(filename, "rb");

    if(fh == NULL) {
        fprintf(stderr, "Can't open html file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    if(fseek(fh, 0L, SEEK_END) != 0) {
        fprintf(stderr, "Can't set position (fseek) in file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    long size = ftell(fh);
    
    if(fseek(fh, 0L, SEEK_SET) != 0) {
        fprintf(stderr, "Can't set position (fseek) in file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    if(size <= 0) {
        fprintf(stderr, "Can't get file size or file is empty: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    char *html = (char*)malloc(size + 1);

    if(html == NULL) {
        fprintf(stderr, "Can't allocate mem for html file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    size_t nread = fread(html, 1, size, fh);
    
    if (nread != size) {
       // fprintf(stderr, "could not read %ld bytes (" MyCORE_FMT_Z " bytes done)\n", size, nread);
        exit(EXIT_FAILURE);
    }
    
    fclose(fh);
    struct res_html res = {html, (size_t)size};
    return res;
}

mystatus_t serialization_callback(const char* data, size_t len, void* ctx) {
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

int displayDefault(myhtml_tree_t* tree) {
    mycore_string_raw_t str = {0};

    if(tree != NULL) {
         myhtml_serialization_tree_buffer(myhtml_tree_get_document(tree), &str);
        printf("%s\n", str.data);
    }
    
    return 0;
}

int printByKey(myhtml_tree_t* tree, char* attr_key) {
    myhtml_collection_t *collection = myhtml_get_nodes_by_attribute_key(tree, NULL, NULL, attr_key, strlen(attr_key), NULL);

    for(size_t i = 0; i < collection->length; i++)
        myhtml_serialization_node_callback(collection->list[i], serialization_callback, NULL);
    
    printf("Total found: %ld\n", collection->length);

    myhtml_collection_destroy(collection);
    return 0;
}

int parseFile(char *filePath) {
    char *attr_key = (char*) malloc(STR_LEN* sizeof(char));
    struct res_html res = load_html_file(filePath);
    // basic init
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    //init tree
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);

    //parse html
    myhtml_parse(tree, MyENCODING_UTF_8, res.html, res.size);

    //print result
    //sprintf(attr_key, "%s", "div");
    //printByKey(tree, attr_key);

    //release resources
    free(attr_key);
    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
    return 0;
}