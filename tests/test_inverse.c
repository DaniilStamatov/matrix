#include "test_matrix.h"

START_TEST(test_inverse_matrix_3x3) {
    matrix_t A, expected, result;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &expected);
    
    A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
    A.matrix[1][0] = 0; A.matrix[1][1] = 1; A.matrix[1][2] = 4;
    A.matrix[2][0] = 5; A.matrix[2][1] = 6; A.matrix[2][2] = 0;

    expected.matrix[0][0] = -24; expected.matrix[0][1] = 18; expected.matrix[0][2] = 5;
    expected.matrix[1][0] = 20; expected.matrix[1][1] = -15; expected.matrix[1][2] = -4;
    expected.matrix[2][0] = -5; expected.matrix[2][1] = 4; expected.matrix[2][2] = 1;

    int code = s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(code, SUCCESS);
    ck_assert_int_eq(result.rows, 3);
    ck_assert_int_eq(result.columns, 3);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_inverse_matrix_no_inverse) {
    matrix_t A, result;
    s21_create_matrix(2, 2, &A);
    
    A.matrix[0][0] = 1; A.matrix[0][1] = 2;
    A.matrix[1][0] = 2; A.matrix[1][1] = 4;

    int code = s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(code, FAILURE);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_3x3_2) {
    matrix_t A, expected, result;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &expected);
    
    A.matrix[0][0] = 2; A.matrix[0][1] = 5; A.matrix[0][2] = 7;
    A.matrix[1][0] = 6; A.matrix[1][1] = 3; A.matrix[1][2] = 4;
    A.matrix[2][0] = 5; A.matrix[2][1] = -2; A.matrix[2][2] = -3;

    expected.matrix[0][0] = 1; expected.matrix[0][1] = -1; expected.matrix[0][2] = 1;
    expected.matrix[1][0] = -38; expected.matrix[1][1] = 41; expected.matrix[1][2] = -34;
    expected.matrix[2][0] = 27; expected.matrix[2][1] = -29; expected.matrix[2][2] = 24;

    int code = s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(code, SUCCESS);
    ck_assert_int_eq(result.rows, 3);
    ck_assert_int_eq(result.columns, 3);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_inverse_matrix_identity) {
    matrix_t A, expected, result;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &expected);
    
    A.matrix[0][0] = 1; A.matrix[0][1] = 0; A.matrix[0][2] = 0;
    A.matrix[1][0] = 0; A.matrix[1][1] = 1; A.matrix[1][2] = 0;
    A.matrix[2][0] = 0; A.matrix[2][1] = 0; A.matrix[2][2] = 1;

    expected.matrix[0][0] = 1; expected.matrix[0][1] = 0; expected.matrix[0][2] = 0;
    expected.matrix[1][0] = 0; expected.matrix[1][1] = 1; expected.matrix[1][2] = 0;
    expected.matrix[2][0] = 0; expected.matrix[2][1] = 0; expected.matrix[2][2] = 1;

    ck_assert_int_eq(s21_inverse_matrix(&A, &result), SUCCESS);
    ck_assert_int_eq(result.rows, 3);
    ck_assert_int_eq(result.columns, 3);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}

START_TEST(test_inverse_matrix_2x2) {
    matrix_t A, expected, result;
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &expected);
    
    A.matrix[0][0] = 4; A.matrix[0][1] = 7;
    A.matrix[1][0] = 2; A.matrix[1][1] = 6;

    expected.matrix[0][0] = 0.6; expected.matrix[0][1] = -0.7;
    expected.matrix[1][0] = -0.2; expected.matrix[1][1] = 0.4;

    int code = s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(code, SUCCESS);
    ck_assert_int_eq(result.rows, 2);
    ck_assert_int_eq(result.columns, 2);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

Suite *inverse_suite(void) {
    Suite *s = suite_create("\033[45m-=S21_INVERSE_MATRIX=-\033[0m");
    TCase *tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_inverse_matrix_3x3);
    tcase_add_test(tc_core, test_inverse_matrix_3x3_2);
    tcase_add_test(tc_core, test_inverse_matrix_no_inverse);
    tcase_add_test(tc_core, test_inverse_matrix_identity);
    tcase_add_test(tc_core, test_inverse_matrix_2x2);
    
    suite_add_tcase(s, tc_core);
    return s;
}