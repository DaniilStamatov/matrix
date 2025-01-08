#include "test_matrix.h"

START_TEST(test_sum_positive) {
    matrix_t A, B, result;
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);

    A.matrix[0][0] = 1; A.matrix[0][1] = 2;
    A.matrix[1][0] = 3; A.matrix[1][1] = 4;

    B.matrix[0][0] = 5; B.matrix[0][1] = 6;
    B.matrix[1][0] = 7; B.matrix[1][1] = 8;

    int code = s21_sum_matrix(&A, &B, &result);

    ck_assert_int_eq(code, SUCCESS);
    ck_assert_double_eq(result.matrix[0][0], 6);
    ck_assert_double_eq(result.matrix[0][1], 8);
    ck_assert_double_eq(result.matrix[1][0], 10);
    ck_assert_double_eq(result.matrix[1][1], 12);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_empty_matrices) {
    matrix_t A, B, result;
    s21_create_matrix(0, 0, &A);
    s21_create_matrix(0, 0, &B);

    int code = s21_sum_matrix(&A, &B, &result);

    ck_assert_int_eq(code, FAILURE);
    ck_assert_ptr_null(result.matrix);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_different_sizes) {
    matrix_t A, B, result;
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(3, 3, &B);

    int code = s21_sum_matrix(&A, &B, &result);

    ck_assert_int_eq(code, CALC_FAILURE);
    ck_assert_ptr_null(result.matrix);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_negative_values) {
    matrix_t A, B, result;
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);

    A.matrix[0][0] = -1; A.matrix[0][1] = -2;
    A.matrix[1][0] = -3; A.matrix[1][1] = -4;

    B.matrix[0][0] = -5; B.matrix[0][1] = -6;
    B.matrix[1][0] = -7; B.matrix[1][1] = -8;

    int code = s21_sum_matrix(&A, &B, &result);

    ck_assert_int_eq(code, SUCCESS);
    ck_assert_double_eq(result.matrix[0][0], -6);
    ck_assert_double_eq(result.matrix[0][1], -8);
    ck_assert_double_eq(result.matrix[1][0], -10);
    ck_assert_double_eq(result.matrix[1][1], -12);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

Suite *sum_suite(void) {
    Suite *s = suite_create("\033[33m-=S21_SUM=-\033[0m");
    TCase *tc_core = tcase_create("create");

    tcase_add_test(tc_core, test_sum_positive);
    tcase_add_test(tc_core, test_sum_empty_matrices);
    tcase_add_test(tc_core, test_sum_different_sizes);
    tcase_add_test(tc_core, test_sum_negative_values);

    suite_add_tcase(s, tc_core);
    return s;
}