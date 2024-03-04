/*
There are 3 Basic Types of Science and Engineering Problems: The Second is Eigenvalue.
One Example of an eigenvalue problem from physics using the GNU Scientific Library (GSL)
Is to consider a mechanical system, such as a vibrating string or a vibrating beam, that can
be modeled as a linear system with mass, damping, and stiffness.  The vibrational modes of such
a system correspond to its eigenmodes, and the frequencies at which these modes occur are the
eigenfrequencies or resonant frequencies.

The equation governing the vibrational modes of such a system is typically a second-order
ordinary differential equation (ODE). By discretizing the system and converting the ODE
into a matrix eigenvalue problem, we can use GSL to compute the eigenvalues (frequencies) and
eigenvectors (mode shapes) of the system.
*/

#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>

#define N 100 // Number of discretization points.

int main(){
    // Define paramters of the vibrating system
    double mass = 1.0;  // Mass of the system
    double stiffness = 1.0; // Stiffness of the system
    double damping = 0.1;   // Damping coefficient of the system

    // Define the matrix for the eigenvalue problem.
    gsl_matrix *A = gsl_matrix_alloc(N, N);
    gsl_matrix *B = gsl_matrix_alloc(N, N);
    gsl_vector *eval = gsl_vector_alloc(N); // Eigenvalues
    gsl_matrix *evec = gsl_matrix_alloc(N, N); // Eigenvectors

    // Fill Matrix A based on the discretized ODE governing the vibrating system.
    for (int i = 0; i < N; i++){
        for ( int j = 0; j < N; j++){
            if (i == j){// Diagonal Elements
                gsl_matrix_set(A, i, j, 2.0 * stiffness / mass);
                gsl_matrix_set(B, i, j, mass + damping);
            } else if (i == j -1 || i == j + 1){// Off Diagonal Elements
                gsl_matrix_set(A, i, j, -stiffness /mass);
            } else { // Other elements are zero

            }
        }
    }

    // Solve eigenvalue problem
    gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc(N);
    gsl_eigen_symmv(A, eval, evec, w);
    gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_VAL_ASC); // Sort eigenvalues in ascending order

    // Print eigenvalues (resonant frequencies)
    for (int i = 0; i < N; i++){
        double frequency = sqrt(gsl_vector_get(eval, i)) / (2 * M_PI);
        printf("Mode %d: %.2f Hz\n", i + 1, frequency);
    }

    // Print mode shapes (eigenvectors)
    printf("\nMode shapes (eigenvectors):\n");
    for (int i = 0; i < N; i++){
        printf("Mode %d: [", i+1);
        for (int j = 0; j < N; j++){
            printf("%.2f ", gsl_matrix_get(evec, j, i));
        }
        printf("]\n");
    }

    gsl_matrix_free(A);
    gsl_matrix_free(B);
    gsl_vector_free(eval);
    gsl_matrix_free(evec);
    gsl_eigen_symmv_free(w);

    return 0;

}