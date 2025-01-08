#include "test_matrix.h"

START_TEST(test_mult_positive) {
    matrix_t A, B;
    s21_create_matrix(2, 3, &A);
    s21_create_matrix(3, 2, &B);

    A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
    A.matrix[1][0] = 4; A.matrix[1][1] = 5; A.matrix[1][2] = 6;

    B.matrix[0][0] = 7; B.matrix[0][1] = 8;
    B.matrix[1][0] = 9; B.matrix[1][1] = 10;
    B.matrix[2][0] = 11; B.matrix[2][1] = 12;
    matrix_t result = {0};
    matrix_t check = {0};

    s21_create_matrix(2, 2, &check);
    check.matrix[0][0] = 58;
    check.matrix[0][1] = 64;
    check.matrix[1][0] = 139;
    check.matrix[1][1] = 154;
    ck_assert_int_eq( s21_mult_matrix(&A, &B, &result), SUCCESS);
    ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_mult_empty_matrices) {
    matrix_t A, B, result;
    s21_create_matrix(0, 0, &A);
    s21_create_matrix(0, 0, &B);

    int code = s21_mult_matrix(&A, &B, &result);

    ck_assert_int_eq(code, FAILURE);
    ck_assert_ptr_null(result.matrix);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_different_sizes) {
    matrix_t A, B, result;
    s21_create_matrix(2, 3, &A);
    s21_create_matrix(2, 2, &B); 

    int code = s21_mult_matrix(&A, &B, &result);

    ck_assert_int_eq(code, CALC_FAILURE);
    ck_assert_ptr_null(result.matrix);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_negative_values) {
    matrix_t A, B, result;
    s21_create_matrix(2, 3, &A);
    s21_create_matrix(3, 2, &B);

    A.matrix[0][0] = -1; A.matrix[0][1] = -2; A.matrix[0][2] = -3;
    A.matrix[1][0] = -4; A.matrix[1][1] = -5; A.matrix[1][2] = -6;

    B.matrix[0][0] = -7; B.matrix[0][1] = -8;
    B.matrix[1][0] = -9; B.matrix[1][1] = -10;
    B.matrix[2][0] = -11; B.matrix[2][1] = -12;

    int code = s21_mult_matrix(&A, &B, &result);

    ck_assert_int_eq(code, SUCCESS);
    ck_assert_double_eq(result.matrix[0][0], 58);
    ck_assert_double_eq(result.matrix[0][1], 64);
    ck_assert_double_eq(result.matrix[1][0], 139);
    ck_assert_double_eq(result.matrix[1][1], 154);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

Suite *mult_suite(void) {
    Suite *s = suite_create("\033[42m-=S21_MULT=-\033[0m");
    TCase *tc_core = tcase_create("create");

    tcase_add_test(tc_core, test_mult_positive);
    tcase_add_test(tc_core, test_mult_empty_matrices);
    tcase_add_test(tc_core, test_mult_different_sizes);
    tcase_add_test(tc_core, test_mult_negative_values);

    suite_add_tcase(s, tc_core);
    return s;
}
