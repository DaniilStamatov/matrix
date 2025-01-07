#include "test_matrix.h"
START_TEST(test_transpose_regular) {
    matrix_t A, result;
    s21_create_matrix(2, 3, &A);

    A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
    A.matrix[1][0] = 4; A.matrix[1][1] = 5; A.matrix[1][2] = 6;

    int code = s21_transpose(&A, &result);

    ck_assert_int_eq(code, SUCCESS);
    ck_assert_int_eq(result.rows, 3);
    ck_assert_int_eq(result.columns, 2);
    ck_assert_double_eq(result.matrix[0][0], 1);
    ck_assert_double_eq(result.matrix[0][1], 4);
    ck_assert_double_eq(result.matrix[1][0], 2);
    ck_assert_double_eq(result.matrix[1][1], 5);
    ck_assert_double_eq(result.matrix[2][0], 3);
    ck_assert_double_eq(result.matrix[2][1], 6);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_zero_values) {
    matrix_t A, result;
    s21_create_matrix(2, 2, &A);

    A.matrix[0][0] = 0; A.matrix[0][1] = 0;
    A.matrix[1][0] = 0; A.matrix[1][1] = 0;

    int code = s21_transpose(&A, &result);

    ck_assert_int_eq(code, SUCCESS);
    ck_assert_int_eq(result.rows, 2);
    ck_assert_int_eq(result.columns, 2);
    ck_assert_double_eq(result.matrix[0][0], 0);
    ck_assert_double_eq(result.matrix[0][1], 0);
    ck_assert_double_eq(result.matrix[1][0], 0);
    ck_assert_double_eq(result.matrix[1][1], 0);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_negative_values) {
    matrix_t A, result;
    s21_create_matrix(2, 2, &A);

    A.matrix[0][0] = -1; A.matrix[0][1] = -2;
    A.matrix[1][0] = -3; A.matrix[1][1] = -4;

    int code = s21_transpose(&A, &result);

    ck_assert_int_eq(code, SUCCESS);
    ck_assert_int_eq(result.rows, 2);
    ck_assert_int_eq(result.columns, 2);
    ck_assert_double_eq(result.matrix[0][0], -1);
    ck_assert_double_eq(result.matrix[0][1], -3);
    ck_assert_double_eq(result.matrix[1][0], -2);
    ck_assert_double_eq(result.matrix[1][1], -4);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_empty) {
    matrix_t A, result;
    s21_create_matrix(0, 0, &A);

    int code = s21_transpose(&A, &result);

    ck_assert_int_eq(code, FAILURE);
    ck_assert_ptr_null(result.matrix);

    s21_remove_matrix(&A);
}
END_TEST

Suite *transpose_suite(void) {
    Suite *s = suite_create("\033[40m-=S21_TRANSPOSE=-\033[0m");
    TCase *tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_transpose_regular);
    tcase_add_test(tc_core, test_transpose_zero_values);
    tcase_add_test(tc_core, test_transpose_negative_values);
    tcase_add_test(tc_core, test_transpose_empty);

    suite_add_tcase(s, tc_core);
    return s;
}