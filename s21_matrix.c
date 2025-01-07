#include "s21_matrix.h"

//INITIALIZATION
int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int code = SUCCESS;
    if(rows < 1 || columns < 1) {
        code = FAILURE;
        result->matrix = NULL;
    } else {
        result->matrix = (double**)calloc(rows, sizeof(double*));
    }
    if(result->matrix != NULL){ 
        for(int i = 0; i < rows && code == SUCCESS; i++) {
            result->matrix[i] = (double*)calloc(columns, sizeof(double));
            if(result->matrix[i] == NULL) {
                for(int k = 0; k < i; k++) free(result->matrix[k]);
                free(result->matrix);
                result->matrix = NULL;
                code = FAILURE;
            }
        }
        result->rows = rows;
        result->columns = columns;
    }
    return code;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

//COMPARATION
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int code = SUCCESS;
     if (s21_is_empty(A) || s21_is_empty(B) || A->rows != B->rows || A->columns != B->columns) {
        code =  FAILURE;
    } else {
        for(int i = 0; i < A->rows && code == SUCCESS; i++) {
            for(int j = 0; j < A->columns && code == SUCCESS; j++) {
                if (round(A->matrix[i][j] * pow(10, 7)) !=
                    round(B->matrix[i][j] * pow(10, 7))) {
                    code = FAILURE;
                }
            }
        }
    }
    return code;
}

//ARIPHMETICS
int s21_calculate(matrix_t *A, matrix_t *B, matrix_t *result, int sign) {
    int code = SUCCESS;
    if(s21_is_empty(A) && s21_is_empty(B)){
        code = FAILURE;  
    } else if(A->rows != B->rows && A->columns != B->columns) {
        code = CALC_FAILURE;
    } else {
        code = s21_create_matrix(A->rows, A->columns, result);
        if(code != FAILURE) {
             for(int i = 0; i < A->rows; i++) {
                for(int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = sign == 1 ? A->matrix[i][j] + B->matrix[i][j] : A->matrix[i][j] - B->matrix[i][j];
                }
            }
        }
    }
    if(code != SUCCESS) result->matrix = NULL;
    return code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    return s21_calculate(A, B, result, 1);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    return s21_calculate(A, B, result, 0);
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int code = SUCCESS;
    if(!s21_is_empty(A)) {
        code = s21_create_matrix(A->rows, A->columns, result);
        if(code != FAILURE) {
            for(int i = 0; i < A->rows; i++) {
                for(int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] * number;
                }
            }
        }
    } else {
        code = FAILURE;
        result->matrix = NULL;
    }
    return code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int code = SUCCESS;
    if(s21_is_empty(A) && s21_is_empty(B)) {
        code = FAILURE;
    } else if(A->columns != B->rows) {
        code = CALC_FAILURE;
    } else {
        code = s21_create_matrix(A->rows, B->columns, result);
        if(code == SUCCESS) {
            for(int i = 0; i < A->rows; i++) {
                for(int j = 0; j < B->columns; j++) {
                    double res = 0;
                    for(int k = 0; k < A->columns; k++) {
                        res += A->matrix[i][k] * B->matrix[k][j];
                    }
                    result->matrix[i][j] = res;
                }
            }
        }
    }
    if(code != SUCCESS) result->matrix = NULL;
    return code;
}

//OPERATIONS
int s21_transpose(matrix_t *A, matrix_t *result) {
    int code = SUCCESS;
    if(!s21_is_empty(A)) {
        code = s21_create_matrix(A->columns, A->rows, result);
        if(code == SUCCESS) {
            for(int i = 0; i < A->rows; i++) {
                for(int j = 0; j < A->columns; j++) {
                    result->matrix[j][i] = A->matrix[i][j];
                }
            }
        }
    } else {
        code = FAILURE;
        result->matrix = NULL;
    }
    return code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int code = SUCCESS;
    if(s21_is_empty(A)) {
        code = FAILURE;
    } else if(A->columns != A->rows) {
        code = CALC_FAILURE;
    } else {
        s21_create_matrix(A->rows, A->columns, result);
        for(int i = 0; i < A->rows; i++) {
            for(int j = 0; j < A->columns; j++) {
                matrix_t minor = {0};
                double determinant = 0.0;
                s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
                s21_fill_submatrix(i, j, A, &minor);
                s21_determinant(&minor, &determinant);
                result->matrix[i][j] = (i + j) % 2 == 0 ? determinant : -determinant;
                s21_remove_matrix(&minor);
            }
        }
    }
    if(code != SUCCESS) result->matrix = NULL;

    return code;
}

int s21_determinant(matrix_t *A, double *result) {
    int code = SUCCESS;
    
    if(s21_is_empty(A)) {
        code = FAILURE;
        if(A->columns != A->rows) {
            code = CALC_FAILURE;
        }
    }
    if(code == SUCCESS) {
        *result = s21_determinant_util(A);
    }

    return code;
}

double s21_determinant_util(matrix_t *A) {
    double result = 0.0;
    if(A->rows == 1) {
        result = A->matrix[0][0];
    } else if(A->rows == 2) {
        result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
        matrix_t temp = {0};
        s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
        for(int x = 0; x < A->rows; x++) {
            s21_fill_submatrix(0, x, A, &temp);
            result += (x % 2 == 0 ? 1 : -1) * A->matrix[0][x] * s21_determinant_util(&temp);
        }
        s21_remove_matrix(&temp);
    }
    return result;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int code = SUCCESS;
    double determinant = 0.0;
    s21_determinant(A, &determinant);
    if(determinant == 0) {
        code = FAILURE;
    } else {
        matrix_t temp = {0};
        s21_create_matrix(A->rows, A->columns, &temp);
        code = s21_calc_complements(A, &temp);
        if(code == SUCCESS) {
            matrix_t transposed = {0};
            s21_transpose(&temp, &transposed);
            s21_create_matrix(A->rows, A->columns, result);
            s21_mult_number(&transposed, 1.0 / determinant, result);
            s21_remove_matrix(&transposed);
        }
        s21_remove_matrix(&temp);
    }
    return code;
}

void s21_fill_submatrix(int row, int column, matrix_t* A, matrix_t* result) {
   int subi = 0;
   for (int i = 0; i < A->rows; i++) {
       if (i != row) {
           int subj = 0;
           for (int j = 0; j < A->columns; j++) {
               if (j != column) {
                   result->matrix[subi][subj] = A->matrix[i][j];
                   subj++;
               }
           }
           subi++;
       }
   }
}
//UTILS
int s21_is_empty(matrix_t* A) {
    int result = 0;
    if(A->matrix == NULL || A == NULL || A->columns <= 0 || A->rows <= 0) {
        result = 1;
    }

    return result;
}

void s21_print_matrix(matrix_t *A) {
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            printf("%lf ", A->matrix[i][j]);
        }
        printf("\n");
    }
}