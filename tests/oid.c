#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "../include/oid.h"

START_TEST(test_strid2nid) {
    int i = 0;
    int j = 0;
    char * ids[] = {"1.2.3.1", "9999.9999.9999", "22.22.333...", NULL};
    int nids[][10] = {{1, 2, 3, 1, -1}, {9999, 9999, 9999, -1} , {22, 22, 333, -1}, {-1}};
    int * _nids = NULL;

    for (i = 0; nids[i][0] != -1; i++) {
        _nids = strid2nid(ids[i]);
        
        for (j = 0; nids[i][j] != -1; j++) {
            ck_assert_int_ne(_nids[j], -1);
            ck_assert_int_eq(nids[i][j], _nids[j]);
        }

        free(_nids);
    }
}
END_TEST

START_TEST(test_nidcmp) {
    int nids1[][10] = {{1, 2, 3, 4, 5, -1}, {1, -1}, {2, 1, -1}, {-1}};
    int nids2[][10] = {{1, 2, 3, 4, 5, -1}, {2, -1}, {1, 2, -1}, {-1}};

    ck_assert_int_eq(nidcmp(nids1[0], nids2[0]), 0);
    ck_assert_int_eq(nidcmp(nids1[1], nids2[1]), -1);
    ck_assert_int_eq(nidcmp(nids1[2], nids2[2]), 1);
}
END_TEST

START_TEST(test_normalizeIdentifier) {
    char * str = NULL;
    int i = 0;
    char * in[] = {"....1...", "1.1", "asdf1.1", ". 1.  1.1", NULL};
    char * out[] = { "1", "1.1", "1.1", "1.1.1", NULL};

    while(in[i] != NULL) {
        str = normalizeIdentifier(in[i]);
        ck_assert_str_eq(str, out[i]);
        free(str);
        str = NULL;
        i++;
    }
}
END_TEST

Suite * oid_suite(void) {
    Suite * s = NULL;
    TCase * tc = NULL;

    s = suite_create("OID");

    tc = tcase_create("OID Manipulation");
    tcase_add_test(tc, test_normalizeIdentifier);
    tcase_add_test(tc, test_strid2nid);
    tcase_add_test(tc, test_nidcmp);
    suite_add_tcase(s, tc);

    return s;
}

int main (int argc, char ** argv) {
    int failed = 0;
    Suite * s = NULL;
    SRunner * r = NULL;

    s = oid_suite();
    r = srunner_create(s);

    srunner_run_all(r, CK_NORMAL);
    failed = srunner_ntests_failed(r);
    srunner_free(r);

    return failed == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
