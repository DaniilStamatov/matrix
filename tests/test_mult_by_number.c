#include "test_matrix.h"
START_TEST(test_mult_number_positive) {
    matrix_t A, result;
    s21_create_matrix(2, 2, &A);
    double number = 3.0;

    A.matrix[0][0] = 1; A.matrix[0][1] = 2;
    A.matrix[1][0] = 3; A.matrix[1][1] = 4;

    s21_create_matrix(2, 2, &result);
    int code = s21_mult_number(&A, number, &result);

    ck_assert_int_eq(code, SUCCESS);
    ck_assert_double_eq(result.matrix[0][0], 3);
    ck_assert_double_eq(result.matrix[0][1], 6);
    ck_assert_double_eq(result.matrix[1][0], 9);
    ck_assert_double_eq(result.matrix[1][1], 12);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_negative) {
    matrix_t A, result;
    s21_create_matrix(2, 2, &A);
    double number = -2.0;

    A.matrix[0][0] = 1; A.matrix[0][1] = 2;
    A.matrix[1][0] = 3; A.matrix[1][1] = 4;

    s21_create_matrix(2, 2, &result);
    int code = s21_mult_number(&A, number, &result);

    ck_assert_int_eq(code, SUCCESS);
    ck_assert_double_eq(result.matrix[0][0], -2);
    ck_assert_double_eq(result.matrix[0][1], -4);
    ck_assert_double_eq(result.matrix[1][0], -6);
    ck_assert_double_eq(result.matrix[1][1], -8);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_zero) {
    matrix_t A, result;
    s21_create_matrix(2, 2, &A);
    double number = 0.0;

    A.matrix[0][0] = 1; A.matrix[0][1] = 2;
    A.matrix[1][0] = 3; A.matrix[1][1] = 4;

    s21_create_matrix(2, 2, &result);
    int code = s21_mult_number(&A, number, &result);

    ck_assert_int_eq(code, SUCCESS);
    ck_assert_double_eq(result.matrix[0][0], 0);
    ck_assert_double_eq(result.matrix[0][1], 0);
    ck_assert_double_eq(result.matrix[1][0], 0);
    ck_assert_double_eq(result.matrix[1][1], 0);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_empty) {
    matrix_t A, result;
    s21_create_matrix(0, 0, &A);
    double number = 5.0;

    int code = s21_mult_number(&A, number, &result);

    ck_assert_int_eq(code, FAILURE);
    ck_assert_ptr_null(result.matrix); 

    s21_remove_matrix(&A);
}
END_TEST

Suite *mult_by_number_suite(void) {
    Suite *s = suite_create("\033[41m-=S21_MULT_NUMBER=-\033[0m");
    TCase *tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_mult_number_positive);
    tcase_add_test(tc_core, test_mult_number_negative);
    tcase_add_test(tc_core, test_mult_number_zero);
    tcase_add_test(tc_core, test_mult_number_empty);

    suite_add_tcase(s, tc_core);
    return s;
}