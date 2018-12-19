#include "include/oid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char * normalizeIdentifier (char * identifier) {
    char *new_id = NULL;
    size_t len = 0;
    size_t i = 0;
    size_t j = 0;
    int state = 0;
    
    assert(identifier != NULL);

    len = strlen(identifier);
    if (len > 0) {
        new_id = calloc(len + 1, sizeof(*new_id));
        if (new_id != NULL) {
            for (i = 0; i < len; i++) {
                if (identifier[i] == '.') {
                    switch (state) {
                        default:
                        case 0: /* last was begin of string */
                        case 2: /* last was a dot */
                            state = 2;
                            continue;
                        case 1: /* last was a number */
                            state = 2;
                            break;
                    }
                } else if (identifier[i] >= 48 && identifier[i] < 58) {
                    switch (state) {
                        case 0:
                        case 2:
                        case 1:
                            state = 1;
                            break;
                        default: 
                            state = 1;
                            continue;
                    }        
                } else {
                    continue;
                }
                new_id[j] = identifier[i];
                j++;
            }
            if (state != 1 && j > 0) {
                j--;
                new_id[j] = '\0';
            } else {
                new_id[j] = identifier[i];
                new_id[j+1] = '\0';
            }
        }
    }
    return new_id;
}

int * strid2nid (char * identifier) {
    int * nids = NULL;
    int id = 0;
    size_t i = 0;
    size_t len = 0;
    size_t count = 1;

    assert(identifier != NULL);
    identifier = normalizeIdentifier(identifier);

    len = strlen(identifier);
    for (i = 0; i < len; i++) { 
        if (identifier[i] == '.') {
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    nids = calloc(count + 1, sizeof(*nids));
    nids[count] = OID_NUMERIC_END_TAG;
    count = 0;
    if (nids != NULL) {
        for (i = 0; i < len; i++) {
            if (identifier[i] >= 48 && identifier[i] < 58) {
                if (id == OID_NUMERIC_END_TAG) { id = 0; }
                id *= 10;
                id += (identifier[i] - 48);
            } else if (identifier[i] == '.') {
                nids[count] = id;
                id = OID_NUMERIC_END_TAG;
                count++;
            }
        }
        nids[count] = id;
    }

    free(identifier);
    return nids;
}

int nidcmp (int * nid1, int * nid2) {
    int i = 0;

    while (nid1[i] != OID_NUMERIC_END_TAG && nid2[i] != OID_NUMERIC_END_TAG) {
        if (nid1[i] < nid2[i]) { return -1; }
        else if (nid1[i] > nid2[i]) { return 1; }
        i++;
    }

    if (nid1[i] == nid2[i]) { return 0; }
    else if(nid1[i] == OID_NUMERIC_END_TAG) { return -1; }
    return 1;
}

int new_oid(oid ** root, char * identifier) {
    int * nid = NULL;

    assert(root != NULL);

    nid = strid2nid(identifier);
    if (nid == NULL) {
        return -1; /* TODO */
    }

    

    if (*root == NULL) {
        
    }
}
