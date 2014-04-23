/***************************************************
 * Interpolation module
 * Author: Josh Woodward
 **************************************************/
#include <stdlib.h>
#include <stdio.h>

#include "linalg.h"
#include "interp.h"
#include "Dynamic.h"


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

static void tridiagonal();

/* Finds the coefficients of the clamped cubic spline for a given set of data */
extern void cspline_clamped(Points *data, double derivA, double derivB, CSplines *splines){



}


/* Finds the coefficients of the antural cubic spline for a given set of data */
extern void cspline_natural(Points *points, CSplines *spline){

	/* Set numRows equal to number of data points in points struct -1 */
	/* If there are N number of points, then there are N-1 number of splines */
	int numRows=points->N-2;

	/* Declare matrix variable */
	MatElement **matrix;

	/* Declare right vector variable */
	VectorElement *right;

	int row, col, j;

	int startingCol, count;

	double hValue,alpha;


	matrix=matrix_alloc(numRows, numRows);

	right=vector_alloc(numRows);



	for(row=0;row<numRows;row++){

		startingCol=row-1;

		for(count=0;count<3;count++){


			col=startingCol+count;

			if((col>=0)&&(col<numRows)){

				/* if count is zero, h sub row */
				if(count==0){
					hValue=points->X[row+1] - points->X[row];
				}else if(count==1){
					hValue= 2 * ((points->X[row+1]-points->X[row])+(points->X[row+2]-points->X[row+1]));
				}else if(count==2){
					hValue=points->X[row+2] - points->X[row+1];
				}
				matrix[row][col]=hValue;
			}

		}

	}

	for(row=0;row<numRows;row++){

		/* J is the "sub value" */
		j=row+1;



		alpha=3 *(((points->Y[j+1] - points->Y[j])/(points->X[j+1]-points->X[j])) - ((points->Y[j]-points->Y[j-1])/(points->X[j-1] - points->X[j])));

		right[row]=alpha;
	}

	matrix_print(matrix, " %g ", numRows, numRows);

	vector_print(right, " %g ", numRows);

	tridiagonal(points, spline, matrix, right, numRows);
}

/* Finds the coefficients of the not-a-knot cubic cpline for a given set of data */
extern void cspline_nak(Points *data, CSplines *splines){

}


/* Evaluates a cubic spline at a given point */
extern double cspline_eval(double x, CSplines *splines){



	return 0.0;
}



static void tridiagonal(Points *points, CSplines *spline, MatElement **matrix, VectorElement *right, int numRows){

	fprintf(stdout, "tridiagnol called\n");

}
