#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_errno.h>



int main()
{
  
    double x = 5.0;
    double y = gsl_sf_bessel_J0 (x);

    if(!y){
        printf ("error: %s\n", gsl_strerror (y));
    }

    printf ("J0(%g) = %.18e\n", x, y);
    return 0;


}