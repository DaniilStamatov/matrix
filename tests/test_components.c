#include "test_matrix.h"

START_TEST(test_calc_complements_2x2) {
    matrix_t A, result;
    s21_create_matrix(2, 2, &A);
    A.matrix[0][0] = 1; A.matrix[0][1] = 2;
    A.matrix[1][0] = 3; A.matrix[1][1] = 4;

    int code = s21_calc_complements(&A, &result);

    ck_assert_int_eq(code, SUCCESS);
    ck_assert_int_eq(result.rows, 2);
    ck_assert_int_eq(result.columns, 2);
    ck_assert_double_eq(result.matrix[0][0], 4);
    ck_assert_double_eq(result.matrix[0][1], -3);
    ck_assert_double_eq(result.matrix[1][0], -2);
    ck_assert_double_eq(result.matrix[1][1], 1);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_3x3) {
    matrix_t A, result;
    s21_create_matrix(3, 3, &A);
    A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
    A.matrix[1][0] = 0; A.matrix[1][1] = 1; A.matrix[1][2] = 4;
    A.matrix[2][0] = 5; A.matrix[2][1] = 6; A.matrix[2][2] = 0;

    int code = s21_calc_complements(&A, &result);
    ck_assert_int_eq(code, SUCCESS);
    ck_assert_int_eq(result.rows, 3);
    ck_assert_int_eq(result.columns, 3);
    ck_assert_double_eq(result.matrix[0][0], -24);
    ck_assert_double_eq(result.matrix[0][1], 20);
    ck_assert_double_eq(result.matrix[0][2], -5);
    ck_assert_double_eq(result.matrix[1][0], 18);
    ck_assert_double_eq(result.matrix[1][1], -15);
    ck_assert_double_eq(result.matrix[1][2], 4);
    ck_assert_double_eq(result.matrix[2][0], 5);
    ck_assert_double_eq(result.matrix[2][1], -4);
    ck_assert_double_eq(result.matrix[2][2], 1);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST


START_TEST(test_calc_complements_3x3_2) {
    matrix_t A, expected, result;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &expected);
    A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
    A.matrix[1][0] = 0; A.matrix[1][1] = 4; A.matrix[1][2] = 2;
    A.matrix[2][0] = 5; A.matrix[2][1] = 2; A.matrix[2][2] = 1;

    expected.matrix[0][0] = 0; expected.matrix[0][1] = 10; expected.matrix[0][2] = -20;
    expected.matrix[1][0] = 4; expected.matrix[1][1] = -14; expected.matrix[1][2] = 8;
    expected.matrix[2][0] = -8; expected.matrix[2][1] = -2; expected.matrix[2][2] = 4;

    int code = s21_calc_complements(&A, &result);
    ck_assert_int_eq(code, SUCCESS);
    ck_assert_int_eq(result.rows, 3);
    ck_assert_int_eq(result.columns, 3);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_calc_complements_empty) {
    matrix_t A, result;
    s21_create_matrix(0, 0, &A);

    int code = s21_calc_complements(&A, &result);

    ck_assert_int_eq(code, FAILURE);
}
END_TEST

START_TEST(test_calc_complements_non_square) {
    matrix_t A, result;
    s21_create_matrix(2, 3, &A);
    A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
    A.matrix[1][0] = 4; A.matrix[1][1] = 5; A.matrix[1][2] = 6;

    int code = s21_calc_complements(&A, &result);

    ck_assert_int_eq(code, CALC_FAILURE);
    ck_assert_ptr_null(result.matrix);
    s21_remove_matrix(&A);
}
END_TEST

Suite *components_suite(void) {
    Suite *s = suite_create("\033[45m-=S21_CALC_COMPLEMENTS=-\033[0m");
    TCase *tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_calc_complements_2x2);
    tcase_add_test(tc_core, test_calc_complements_3x3);
    tcase_add_test(tc_core, test_calc_complements_3x3_2);
    tcase_add_test(tc_core, test_calc_complements_empty);
    tcase_add_test(tc_core, test_calc_complements_non_square);

    suite_add_tcase(s, tc_core);
    return s;
}
