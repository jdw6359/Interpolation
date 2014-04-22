/***************************************************
 * Interpolation module
 * Author: Josh Woodward
 **************************************************/
#include <stdlib.h>
#include <stdio.h>


#include "interp.h"

/* CSplines Struct:
 * int N       number of elements in array
 * double *a   pointer to constant coefficients
 * double *b   pointer to linear coefficients
 * double *c   pointer to quadratic coefficients
 * double *d   pointer to cubic coefficients
 * double *X   pointer interpolation interval partition
 */

/* Points struct:
 * int N       number of Elements in array
 * double *X   pointer to X Data
 * double *Y   pointer to Y Data
 * int Size    size of dynamic arrays
 * int NExt    index to next point in array
 */



/* Finds the coefficients of the clamped cubic spline for a given set of data */
extern void cspline_clamped(Points *data, double derivA, double derivB, CSplines *splines){

	fprintf(stdout, "Setting up clamped system of equations\n");

	fprintf(stdout, "Calling solve tridiagnol\n");

	tridiagonal();

	fprintf(stdout, "Evaluating function\n");


}


/* Finds the coefficients of the antural cubic spline for a given set of data */
extern void cspline_natural(Points *data, CSplines *splines){

}

/* Finds the coefficients of the not-a-knot cubic cpline for a given set of data */
extern void cspline_nak(Points *data, CSplines *splines){

}


/* Evaluates a cubic spline at a given point */
extern double cspline_eval(double x, CSplines *splines){



	return 0.0;
}



static void tridiagonal(){

	fprintf(stdout, "tridiagnol called\n");

}
