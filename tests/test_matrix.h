#ifndef UNIT_TESTS_S21_MATRIX_H_
#define UNIT_TESTS_S21_MATRIX_H_

#include <check.h>
#include <time.h>
#include <unistd.h>

#include "../s21_matrix.h"
Suite *mult_suite(void);
Suite *create_suite(void);
Suite *sub_suite(void);
Suite *sum_suite(void);
Suite *mult_by_number_suite(void);
Suite *transpose_suite(void);
Suite *determinant_suite(void);
Suite *components_suite(void);
Suite *inverse_suite(void);


void run_tests(void);
void run_testcase(Suite *testcase);

#endif