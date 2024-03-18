#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_odeiv2.h>
#include <time.h>

struct params{
    double g;
    int startPosition;
    int startVelocity;
};

int func(double t, const double y[], double f[], void *params){
    (void) (t);
    struct params *init  = (struct params*)params;
    // Starting velocity
    f[0] = y[1];
    // Free Fall
    f[1] = -(init->g);
    return GSL_SUCCESS;
}

int main(){
    // Paramter initialization
    struct params *inputs = malloc(sizeof(struct params));
    
    if (inputs != NULL){
        inputs->g=9.8;
        inputs->startPosition = 10;
        inputs->startVelocity = 50;
    }

    double t = 0.0, t1 = 100;

    clock_t start_time = clock(); //Record Start Time
    double timeout = 5.0; // Timeout in seconds

    // System initialization
    gsl_odeiv2_system system = {func, NULL, 2, inputs};

    // ODE solver initialization
    const gsl_odeiv2_step_type *type = gsl_odeiv2_step_rk8pd;
    gsl_odeiv2_step *step = gsl_odeiv2_step_alloc(type, 2);
    gsl_odeiv2_control *control = gsl_odeiv2_control_y_new(1e-6,0.0);
    gsl_odeiv2_evolve *evolve = gsl_odeiv2_evolve_alloc(2);

    //gsl_odeiv2_driver * driver = gsl_odeiv2_driver_alloc_y_new(&system, type, 1e-2, 1e-6,1e-6);

    double y[2] = {inputs->startPosition, inputs->startVelocity};

    printf ( " Step method is '%s'\n", gsl_odeiv2_step_name(step));

    while(t < t1){
        
        //int status = gsl_odeiv2_driver_apply_fixed_step(driver, &t, 1, 1, y);
        int status = gsl_odeiv2_evolve_apply_fixed_step(evolve, control, step, &system, &t, 1, y);

        if (status != GSL_SUCCESS){
            printf("error, return value=%d\n", status);
            break;
        }
        if (y[0] <= 0) break;
        printf("At time t=%.3f s, position=%.3f m, velocity=%.3f m/s\n", t, y[0], y[1]);

        clock_t current_time = clock();
        double elapsed_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;
        if (elapsed_time > timeout){
            printf(" Infinite loop timeout reached. \n");
            break;
        } 

  
    }

    //int reset = gsl_odeiv2_driver_reset(driver);

    gsl_odeiv2_control_free(control);
    gsl_odeiv2_step_free(step);
    gsl_odeiv2_evolve_free(evolve);
    //gsl_odeiv2_driver_free(driver);
    free(inputs);
    return 0;

}