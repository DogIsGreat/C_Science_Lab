#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_math.h> 
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_errno.h>


int main()
{
    /* Example
    double x = 5.0;
    double y = gsl_sf_bessel_J0 (x);

    if(!y){
        printf ("error: %s\n", gsl_strerror (y));
    }

    printf ("J0(%g) = %.18e\n", x, y);
    */
    gsl_matrix *A = gsl_matrix_alloc(2,2);
    gsl_vector *x = gsl_vector_alloc(2);
    gsl_vector *y = gsl_vector_alloc(2);

    gsl_matrix_set(A, 0, 0, 4.0);
    gsl_matrix_set(A, 0, 1, 2.0);
    gsl_matrix_set(A, 1, 0, 1.0);
    gsl_matrix_set(A, 1, 1, 2.0);

    gsl_vector_set(x, 0, 5.0);
    gsl_vector_set(x, 1, 2.0);

    gsl_vector *computation = gsl_vector_alloc(2);
    gsl_permutation *perm = gsl_permutation_alloc(2);
    int signum;
    gsl_linalg_LU_decomp(A, perm, &signum);
    gsl_linalg_LU_solve(A, perm, x, y);

    printf("Vector in the old base (x):\n");
    printf("[ %g, %g ]\n", gsl_vector_get(x,0), gsl_vector_get(x,1));
    printf("Vector in the new base (y):\n");
    printf("[ %g, %g ]\n", gsl_vector_get(y,0), gsl_vector_get(y,1));

    gsl_matrix_free(A);
    gsl_vector_free (x);
    gsl_vector_free (y);
    gsl_permutation_free(perm);
    gsl_vector_free(computation);

    return 0;


}