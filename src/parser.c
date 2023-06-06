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

int printNode(myhtml_tree_t* tree, myhtml_tree_node_t* root) {
    printf("%s", myhtml_tag_name_by_id(tree, myhtml_node_tag_id(root), NULL));
    myhtml_tree_attr_t* attr = myhtml_node_attribute_first(root);
    
    while(attr != NULL) {
        /* attribute sexpr (name value)*/
        const char *key = myhtml_attribute_key(attr, NULL);
        const char *value = myhtml_attribute_value(attr, NULL);

        if(key == NULL)
            printf("(KEY IS NULL)");
        else if (value)
            printf("(%s \'%s\')\n", key, value);
        else
            printf("(%s)\n", key);
        
        attr = myhtml_attribute_next(attr);
    }

    return 0;
}

int walk_subtree(myhtml_tree_t* tree, myhtml_tree_node_t* root, int level) {
    if(!root) {
        return 0;
    }

    /* Check if we handle this node type */
    if(!filter_node(root)) {
        return 0;
    }

    /* start sexpr */
    putchar('(');

    /* print this node */
    printNode(tree, root);

    /* left hand depth-first recoursion */
    myhtml_tree_node_t* child = myhtml_node_child(root);
    while(child != NULL) {
        walk_subtree(tree, child, level + 1);
        child = myhtml_node_next(child);
    }

    /* close sexpr */
    putchar(')');
    return 0;
}

int print_tree(myhtml_tree_t* tree, myhtml_tree_node_t *node, size_t inc) {
    while(node) {
        for(size_t i = 0; i < inc; i++)
            printf("\t");
        //print current element
        const char *tag_name = myhtml_tag_name_by_id(tree, myhtml_node_tag_id(node), NULL);

        if(tag_name)
            printf("<%s", tag_name);
        else
            // it can not be
            printf("<!something is wrong!");
        
        //print node attributes
        printNode(tree, node);

        if(myhtml_node_is_close_self(node))
            printf(" /");

        myhtml_tag_id_t tag_id = myhtml_node_tag_id(node);

        if(tag_id == MyHTML_TAG__TEXT || tag_id == MyHTML_TAG__COMMENT) {
            const char* node_text = myhtml_node_text(node, NULL);
            printf(">: %s\n", node_text);
        } else {
            printf(">\n");
        }

        //print children
        print_tree(tree, myhtml_node_child(node), (inc + 1));
        node = myhtml_node_next(node);
    }
    
    printf("\n");

    return 0;
}

int getTagName(myhtml_tree_t* tree,  myhtml_tree_node_t *root) {
    if(tree != NULL && root != NULL) {
        printf("%s\n", myhtml_tag_name_by_id(tree, myhtml_node_tag_id(root), NULL));
    }
    return 0;
}

int saveText(const char* node_text, char *fileName) {
    char *filePath;

    if(node_text != NULL && fileName != NULL) {
        filePath = (char*) malloc(STR_SIZE * sizeof(char));
        getCurrentDir(filePath, STR_SIZE);
        strcat(filePath, FILES_PATH);
        strcat(filePath, fileName);
        //var ytInitialData =
        //;
        appendStrToFile(filePath, node_text);  
        free(filePath);
    }

    return 0;
}

int getNodeText(myhtml_tree_t* tree, myhtml_tree_node_t *node, size_t inc, char *playerdata_file, char *yinitdata_file) {
    while(node) {
        myhtml_tag_id_t tag_id = myhtml_node_tag_id(node);

        if(tag_id == MyHTML_TAG__TEXT || tag_id == MyHTML_TAG__COMMENT) {
            const char* node_text = myhtml_node_text(node, NULL);
            if(strstr(node_text, YINITPLAYERDATA_FILE) != NULL) {
                saveText(node_text, playerdata_file);
            } else if(strstr(node_text, YINITDATA_FILE) != NULL) {
                saveText(node_text, yinitdata_file);
            }
        }
        //print children
        getNodeText(tree, myhtml_node_child(node), (inc + 1), playerdata_file, yinitdata_file);
        node = myhtml_node_next(node);
    }
    return 0;
}

int getTargetNodesByName(myhtml_tree_t* tree, char *tag_name) {
    //tag_name : div, script, etc ...
    myhtml_collection_t *collection;
    myhtml_tree_node_t *root;

    if(tree != NULL) {
        collection = myhtml_get_nodes_by_name(tree, NULL, tag_name, 1, NULL);
        for(size_t i = 0; i < collection->length; ++i) {
            root = collection->list[i];  
            getNodeText(tree, root, 0, YINITPLAYERDATA_FILE, YINITDATA_FILE);
        }
        printf("getTargetNodes (collection->length) : %lu\n", collection->length); 
    }

    return 0;
}

int extract_nodetext(myhtml_tree_t* tree, myhtml_collection_t *collection) {
    myhtml_tree_node_t *root;

    if(collection != NULL) {
        for(size_t i = 0; i < collection->length; ++i) {
            root = collection->list[i];  
            getNodeText(tree, root, 0, YINITPLAYERDATA_FILE, YINITDATA_FILE);
        }
    }

    return 0;
}

int getTargetNodes(myhtml_tree_t* tree, myhtml_tag_id_t tag_id, myhtml_collection_t **collection) {
    //tag_id : MyHTML_TAG_BODY, MyHTML_TAG_DIV,  MyHTML_TAG_SCRIPT, , etc ...
    if(tree != NULL) {
        *collection = myhtml_get_nodes_by_tag_id(tree, NULL, tag_id, NULL);
        if(*collection != NULL)
            printf("getTargetNodes (collection->length) : %lu\n", (*collection)->length); 
    }
    return 0;
}

int parseYFile(char *filePath) {
    myhtml_collection_t *collection = NULL;
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
    getTargetNodes(tree, MyHTML_TAG_BODY, &collection);

    if(collection != NULL)
        extract_nodetext(tree, collection);

    //release resources
    //myhtml_collection_clean(collection);
    myhtml_collection_destroy(collection);
    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
    free(res.html);
    return 0;
}

int parseFile(char *filePath) {
    struct res_html res = load_html_file(filePath);
    // basic init
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

    //init tree
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);

    //parse html
    myhtml_parse(tree, MyENCODING_UTF_8, res.html, res.size);

    //print walk_subtree
    walk_subtree(tree, myhtml_tree_get_node_html(tree), 6);

    //print tree
    //myhtml_tree_node_t *node = myhtml_tree_get_document(tree);
    //print_tree(tree, myhtml_node_child(node), 0);

    //release resources
    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
    return 0;
}