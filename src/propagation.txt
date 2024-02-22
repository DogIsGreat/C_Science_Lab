/*
There are 3 Basic Types of Science and Engineering Problems: The Third is Propogation.
One Example of a propogation problem from physics using the GNU Scientific Library (GSL)
is the diffusion equation, which describes how a quantity (e.g., heat, concentration of a 
substance) diffuses through a medium over time. du/dt = D * (d^2u)/(dx)^2

To solve this equation numerically, we can use finite difference methods, where we discretize 
both space and time and approximate the derivatives. We then update the solution at each step
using a numerical scheme such as the forward Euler method, backward Euler method, or the 
Crank-Nicolson method.
*/

#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

#define NX 100 // Number of spatial grid points
#define NT 100 // Number of time steps
#define DX 0.1 // Spatial step size
#define DT 0.01 // Time step size
#define D 0.1 // Diffusion coefficient

int main(){

    gsl_matrix *u = gsl_matrix_alloc(NX, NT); // Solution Matrix
    gsl_vector *u_old = gsl_vector_alloc(NX);

    // Set initial condition, in this case a gaussian profile
    for (int i = 0; i < NX; i++){
        double x = (i - (NX -1) / 2) * DX;
        gsl_matrix_set(u, i, 0 exp(-x * x));
    }

    // Forward Euler time-stepping scheme
    for (int t= 1; t < NT; t++){
        // Copy the solution at the previous time step
        gsl_vector_memcpy(u_old, gsl_matrix_column(u, t -1));

        for (int i = 1; i < NX -1; i++){
            double laplacian = gsl_vector_get(u_old, i - 1) - 2 * gsl_vector_get(u_old, i) + gsl_vector_get(u_old, i+1);
            double diffusionTerm = D * laplacian / (DX * DX);
            gsl_matrix_set(u, i, t, gsl_vector_get(u_old, i) + DT * diffusionTerm );
        }   
    }

    gsl_matrix_free(u);
    gsl_vector_free(u_old);
}