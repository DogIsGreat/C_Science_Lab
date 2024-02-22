#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_errno.h>

int main(){
    
    const int M = 2;
    const int N = 2;
    

    gsl_matrix *A = gsl_matrix_alloc(M,N);
    gsl_matrix *B = gsl_matrix_alloc(M,N);

    //Manual Setting of Matrix values
    gsl_matrix_set(A, 0, 0, 1);
    gsl_matrix_set(A, 0, 1, 2);
    gsl_matrix_set(A, 1, 0, 3);
    gsl_matrix_set(A, 1, 1, 4);

    gsl_matrix_set(B, 0, 0, 2);
    gsl_matrix_set(B, 0, 1, 4);
    gsl_matrix_set(B, 1, 0, 6);
    gsl_matrix_set(B, 1, 1, 8);

    //Patterned automatic setting of Matrix values
    /*
    for (int i = 0; i < M; i++ ){
        for (int j = 0; j < N; j++){
            gsl_matrix_set(A, i, j, value * parameter);
        }
    }
    */

    //gsl_matrix_add(A, B);
    gsl_matrix_mul_elements(A,B);
    double max = gsl_matrix_max(A);


    for (int i = 0; i < M; i++ ){
        printf("( ");
        for (int j = 0; j < N; j++){
            printf(" %g ", gsl_matrix_get(A,i,j));
        }
        printf(" ) \n");
    }
    printf(" maximum value %f ", max);

    gsl_matrix_free(A);
    gsl_matrix_free(B);

    return 0;

}