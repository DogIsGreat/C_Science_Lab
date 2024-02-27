#include "datafile.h"
#include <stdio.h>
#include <string.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_errno.h>

int main(){
    
    int M = 2;
    int N = 2;
    int O = 0;
    int P = 0;

    

    char file1[256];
    char file2[256];
    
    printf("Please specify the name of the csv for the first matrix. \n");
    scanf("%255s", file1);
    getchar();
    printf("Please specify the name the csv file for the second matrix. \n");
    scanf("%255s", file2);
    getchar();
    printf("%s\n", file1);

    gsl_matrix *A = gsl_matrix_alloc(M,N);
    gsl_matrix *B = gsl_matrix_alloc(O,P);

    /* Manual Setting of Matrix values
    gsl_matrix_set(A, 0, 0, 1);
    gsl_matrix_set(A, 0, 1, 2);
    gsl_matrix_set(A, 1, 0, 3);
    gsl_matrix_set(A, 1, 1, 4);

    gsl_matrix_set(B, 0, 0, 2);
    gsl_matrix_set(B, 0, 1, 4);
    gsl_matrix_set(B, 1, 0, 6);
    gsl_matrix_set(B, 1, 1, 8);
    */

    
    /* Patterned automatic setting of Matrix values
    for (int i = 0; i < M; i++ ){
        for (int j = 0; j < N; j++){
            gsl_matrix_set(A, i, j, value * parameter);
        }
    }
    */

    // File loading of Matrix Values.
    count_rows_cols(&file1, &M, &N);
    count_rows_cols(&file2, &O, &P);

    if( M == N && N == O && N == P){
        load_data(&file1, A);
        load_data(&file2, B);
    } else {
        printf("You must provide 2 square matrixes for this program as of now.\n");
    }

    
    //gsl_matrix_add(A, B);
    gsl_matrix_mul_elements(A,B);
    double max = gsl_matrix_max(A);
    gsl_matrix_transpose(B);

    for (int i = 0; i < M; i++ ){
        printf("( ");
        for (int j = 0; j < N; j++){
            printf(" %g ", gsl_matrix_get(A,i,j));
        }
        printf(" ) \n");
    }
    printf(" maximum value %f \n", max);
    printf(" The transposed matrix B is: \n");

        for (int i = 0; i < M; i++ ){
        printf("( ");
        for (int j = 0; j < N; j++){
            printf(" %g ", gsl_matrix_get(B,i,j));
        }
        printf(" ) \n");
    }

    // Find the determinant.
    gsl_permutation *p = gsl_permutation_alloc(N);
    int s;
    gsl_linalg_LU_decomp(B, p, &s);
    double det = gsl_linalg_LU_det(B, s);

    printf( "The determinant is: %g\n", det);

    // Find the inverse matrix of B
    if(det == 0){
        printf("The matrix is singular and cannot be inverted. \n");
    } else {
        gsl_matrix *inverse = gsl_matrix_alloc(N, N);
        gsl_linalg_LU_invert(B, p, inverse);

        printf("The inverse matrix is: \n");
        for( int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                printf("%g\t", gsl_matrix_get(inverse, i, j));
            }
            printf("\n");
        }
        gsl_matrix_free(inverse);
    }

    gsl_matrix_free(A);
    gsl_matrix_free(B);
    gsl_permutation_free(p);

    return 0;

}