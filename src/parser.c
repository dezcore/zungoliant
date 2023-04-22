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

int displayCollection(myhtml_collection_t *collection) {
    if(collection && collection->list && collection->length) {
        myhtml_tree_node_t *text_node = collection->list[0];
        mycore_string_t *str = myhtml_node_string(text_node);
        char *data = mycore_string_data(str);
        printf("data : %s : ", data);
    }

    return 0;
}

bool filter_node(myhtml_tree_node_t* node) {
    myhtml_tag_id_t tag = myhtml_node_tag_id(node);
    return (tag != MyHTML_TAG__TEXT) && (tag != MyHTML_TAG__END_OF_FILE) && (tag != MyHTML_TAG__COMMENT) && (tag != MyHTML_TAG__UNDEF);
}

int walk_subtree(myhtml_tree_t* tree, myhtml_tree_node_t* root, int level){
    if (!root) {
        return 0;
    }

    /* Check if we handle this node type */
    if(!filter_node(root)) {
        return 0;
    }

    /* start sexpr */
    putchar('(');

    /* print this node */
    printf("%s", myhtml_tag_name_by_id(tree, myhtml_node_tag_id(root), NULL));
    myhtml_tree_attr_t* attr = myhtml_node_attribute_first(root);
    while (attr != NULL) {
        /* attribute sexpr (name value)*/
        const char *key = myhtml_attribute_key(attr, NULL);
        const char *value = myhtml_attribute_value(attr, NULL);
        
        if(key == NULL)
            printf("(KEY IS NULL)");
        else if (value)
            printf("(%s \'%s\')", key, value);
        else
            printf("(%s)", key);
        
        attr = myhtml_attribute_next(attr);
    }

    /* left hand depth-first recoursion */
    myhtml_tree_node_t* child = myhtml_node_child(root);
    while (child != NULL) {
        walk_subtree(tree, child, level + 1);
        child = myhtml_node_next(child);
    }

    /* close sexpr */
    putchar(')');
    return 0;
}

int test(myhtml_tree_t* tree) {
    //myhtml_tree_node_t *test = myhtml_tree_get_node_html(tree);
    //myhtml_tree_node_t *test1 = myhtml_tree_get_node_body(tree);
    //myhtml_collection_t *collection = myhtml_get_nodes_by_tag_id(tree, NULL, MyHTML_TAG__TEXT, NULL);

    /*myhtml_collection_t *collection = myhtml_get_nodes_by_name(tree, NULL, "a", 1, NULL);
    for (size_t i = 0; i < collection->length; ++i) {
        // add attribute
        myhtml_attribute_add(collection->list[i], "title", 5, "my value", 8, MyENCODING_UTF_8);
    }*/

    // get text node by index
    /*myhtml_collection_t *collection = myhtml_get_nodes_by_tag_id(tree, NULL, MyHTML_TAG_TABLE, NULL);
    if(collection && collection->list && collection->length) {
        myhtml_tree_node_t *table = collection->list[0];  
        myhtml_tree_node_t* node_a = myhtml_node_create(tree, MyHTML_TAG_A, MyHTML_NAMESPACE_HTML);
        myhtml_node_insert_to_appropriate_place(table, node_a);
    }*/
    
    /*walk_subtree(tree, myhtml_tree_get_node_html(tree), 0);
    printf("\n");*/

    return 0;
}

int print_node_attr(myhtml_tree_node_t *node) {
    myhtml_tree_attr_t *attr = myhtml_node_attribute_first(node);

    while(attr) {
        const char *name = myhtml_attribute_key(attr, NULL);

        if(name) {
            printf(" %s", name);
            
            const char *value = myhtml_attribute_value(attr, NULL);
            
            if(value)
                printf("=\"%s\"", value);
        }
        
        attr = myhtml_attribute_next(attr);
    }

    return 0;
}

int print_tree(myhtml_tree_t* tree, myhtml_tree_node_t *node, size_t inc) {
    while(node) {
        for(size_t i = 0; i < inc; i++)
            printf("\t");
        // print current element
        const char *tag_name = myhtml_tag_name_by_id(tree, myhtml_node_tag_id(node), NULL);

        if(tag_name)
            printf("<%s", tag_name);
        else
            // it can not be
            printf("<!something is wrong!");
        
        // print node attributes
        print_node_attr(node);

        if(myhtml_node_is_close_self(node))
            printf(" /");

        myhtml_tag_id_t tag_id = myhtml_node_tag_id(node);

        if(tag_id == MyHTML_TAG__TEXT || tag_id == MyHTML_TAG__COMMENT) {
            const char* node_text = myhtml_node_text(node, NULL);
            printf(">: %s\n", node_text);
        } else {
            printf(">\n");
        }

        // print children
        print_tree(tree, myhtml_node_child(node), (inc + 1));
        node = myhtml_node_next(node);
    }

    return 0;
}

int test_print_tree(myhtml_tree_t* tree) {
    myhtml_tree_node_t *node = myhtml_tree_get_document(tree);
    print_tree(tree, myhtml_node_child(node), 0);
    //id="contents"
    //id="above-the-fold"
    //id="title"
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