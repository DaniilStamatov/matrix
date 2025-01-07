#include "test_matrix.h"

START_TEST(test_create_positive) {
    matrix_t mat;
    int code = s21_create_matrix(3, 4, &mat);
    ck_assert_int_eq(code, SUCCESS);
    ck_assert_int_eq(mat.rows, 3);
    ck_assert_int_eq(mat.columns, 4);
    ck_assert_ptr_nonnull(mat.matrix);
    s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_zero_rows) {
    matrix_t mat;
    int code = s21_create_matrix(0, 4, &mat);
    ck_assert_int_eq(code, FAILURE);
}
END_TEST

START_TEST(test_create_zero_columns) {
    matrix_t mat;
    int code = s21_create_matrix(3, 0, &mat);
    ck_assert_int_eq(code, FAILURE);
    ck_assert_ptr_null(mat.matrix);
}
END_TEST

START_TEST(test_create_negative_rows) {
    matrix_t mat;
    int code = s21_create_matrix(-1, 4, &mat);
    ck_assert_int_eq(code, FAILURE);
    ck_assert_ptr_null(mat.matrix);
}
END_TEST

START_TEST(test_create_negative_columns) {
    matrix_t mat;
    int code = s21_create_matrix(3, -1, &mat);
    ck_assert_int_eq(code, FAILURE);
    ck_assert_ptr_null(mat.matrix);
}
END_TEST

START_TEST(test_create_zero_rows_and_columns) {
    matrix_t mat;
    int code = s21_create_matrix(0, 0, &mat);
    ck_assert_int_eq(code, FAILURE);
    ck_assert_ptr_null(mat.matrix);
}
END_TEST

START_TEST(test_create_large_matrix) {
    matrix_t mat;
    int code = s21_create_matrix(1000, 1000, &mat);
    ck_assert_int_eq(code, SUCCESS);
    ck_assert_int_eq(mat.rows, 1000);
    ck_assert_int_eq(mat.columns, 1000);
    ck_assert_ptr_nonnull(mat.matrix);
    s21_remove_matrix(&mat);
}
END_TEST

Suite *create_suite(void) {
    Suite *s = suite_create("\033[45m-=S21_CREATE=-\033[0m");
    TCase *tc_core = tcase_create("create");

    tcase_add_test(tc_core, test_create_positive);
    tcase_add_test(tc_core, test_create_zero_rows);
    tcase_add_test(tc_core, test_create_zero_columns);
    tcase_add_test(tc_core, test_create_negative_rows);
    tcase_add_test(tc_core, test_create_negative_columns);
    tcase_add_test(tc_core, test_create_zero_rows_and_columns);
    tcase_add_test(tc_core, test_create_large_matrix);

    suite_add_tcase(s, tc_core);
    return s;
}