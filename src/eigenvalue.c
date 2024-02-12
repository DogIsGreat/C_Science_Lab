/*
There are 3 Basic Types of Science and Engineering Problems: The First is Equilibrium.
One Example of an equilibrium problem from physics using the GNU Scientific Library (GSL)
is the calculation of the steady-state temperature distrobution in a heat conducting material.

Consider a one-dimensional rod with uniform thermal conductivity and specific heat capacity,  
where heat is being applied at one end and dissipated at the other end. The steady-state 
temperature distribution along the rod can be modeled using the heat equation, which is a 
second-order partial differential equation.

By discretizing the rod into small segments, we can convert the heat equation into a system
of linear equations. Solving this system of equations will give us the temperature distribution
along the rod at steady state. 

GSL provides functions for solving systems of linear equations, such as 'gsl_linalg_HH_solve' 
for solving systems of equations using the Householder transformations, and 'gsl_linalg_LU_solve'
for solving systems of equations using LU decomposition.
*/

#include <stdio.h>
#include <gsl/gsl_linalg.h>

#define N 100 // Number of segments in the rod

int main(){
    // Define Parameters
    double conductivity = 1.0;
    double heatSource = 1.0;
    double ambientTemp = 0.0;

    // Create a matrix and vector for the systems of equations.
    gsl_matrix *A = gsl_matrix_alloc(N, N);
    gsl_vector *b = gsl_vector_alloc(N);

    // Fill matrix A and vector b based on discretized heat equation.
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (i == j){
                gsl_matrix_set(A, i, j, -2.0); // Diagonal Elements
            } else if (i == j -1 || i == j +1){
                gsl_matrix_set(A, i, j, 1.0);
            } else {
                gsl_matrix_set(A, i, j, 0.0);
            }
        }

        if(i==0) {
            gsl_vector_set(b, i, -heatSource);
        } else if (i == N -1 ){
            gsl_vector_set(b, i , -ambientTemp);
        } else {
            gsl_vector_set(b, i, 0.0);
        }

    }


    // Solve system of equations to get temperature distribution.
    gsl_vector *x = gsl_vector_alloc(N);
    gsl_permutation *p = gsl_permutation_alloc(N);
    int signum;

    // Perform LU decomposition
    int dec = gsl_linalg_LU_decomp(A, p, &signum);
    if(!dec){
        printf ("error: %s\n", gsl_strerror (dec));
    }

    // Solve system using LU decomposition
    int sol = gsl_linalg_LU_solve(A, p, b, x);
    if(!sol){
        printf ("error: %s\n", gsl_strerror (sol));
    }

    printf("Steady-state temperature distribution:\n");
    for( int i = 0; i < N; i++){
        printf("Temperatue at segment %d: %f\n", i, gsl_vector_get(x, i));
    }

    // Free allocated Memory
    gsl_matrix_free(A);
    gsl_vector_free(b);
    gsl_vector_free(x);
    gsl_permutation_free(p);

    return 0;

}