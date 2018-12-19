#ifndef OID_H__
#define OID_H__

#define OID_NUMERIC_END_TAG -1 /* end of integer array as oids have no negative value */

#define OID_INVALID 0
#define OID_OBJECTLCASS 1
#define OID_ATTRIBUTETYPE   2

#define OID_TYPE_INVALID    0
#define OID_TYPE_ABSTRACT   1
#define OID_TYPE_STRUCTURAL 2
#define OID_TYPE_AUXILIARY  3

#define OID_USAGE_INVALID   0
#define OID_USAGE_USER_APPLICATION  1
#define OID_USAGE_DIRECTORY_OPERATION   2
#define OID_USAGE_DISTRIBUTED_OPERATION 3
#define OID_USAGE_DSA_OPERATION 4

typedef struct _s_oid oid;
struct _s_oid {
    int what; /* object class, attributetype, ...*/

    unsigned int * p_nids;
    unsigned int nid;

    char * description;

    char * equality;
    char * substr;
    char * syntax;

    int obsolete; /* 0 if not, !0 if */
    int singleValue; /* 0 if not, !0 if */
    int collective; /* 0 if not, !0 if */
    int userModifiable; /* 0 if not, !0 if */

    char * sup; /* schema sup */
    int type; /* OID_TYPE_* */
    int usage; /* OID_USAGE_* */

    char ** may;
    char ** must;

    oid * parent;
    oid * nextSibling;
    oid * firstChild;    
};

int * strid2nid (char * identifier);
int nidcmp(int * nid1, int * nid2);
char * normalizeIdentifier (char * identifier);

#endif /* OID_H__ */
