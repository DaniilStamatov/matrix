#ifndef S21_MATRIX
#define S21_MATRIX

#define SUCCESS 0
#define FAILURE 1
#define CALC_FAILURE 2
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

//INITIALIZATION
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

//COMPARATION
int s21_eq_matrix(matrix_t *A, matrix_t *B);

//ARIPHMETICS
int s21_calculate(matrix_t *A, matrix_t *B, matrix_t *result, int sign);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

//OPERATIONS
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
double s21_determinant_util(matrix_t *A);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

//UTILS
int s21_is_empty(matrix_t* A);
 void s21_fill_submatrix(int row, int column, matrix_t* A, matrix_t* result);
void s21_print_matrix(matrix_t *A);
#endif
