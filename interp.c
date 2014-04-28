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
extern void cspline_clamped(Points *points, double derivA, double derivB, CSplines *spline){

	/* Set numRows equal to data points in struct -1 */
	/* If there are N number of points, then there are N-1 number of splines */
	int numRows=points->N;

	/* N represents num points-1 */

	/* Declare matrix variable */
	MatElement **matrix;

	/* Declare right vector and solution variables */
	VectorElement *right, *solution;

	/* Declare values for counters */
	int row, col, j, startingCol, count;

	/* Declare values that will be put into our linear system as well as C, C+1 */
	double hValue, alpha;

	/* Make calls to allocate memory for matrices and vectors */
	matrix=matrix_alloc(numRows, numRows);
	right=vector_alloc(numRows);
	solution=vector_alloc(numRows);

	for(row=0;row<numRows;row++){

		/* The col that our values will start to be put into */
		startingCol=row-1;

		/* Count represents the basis for the formula that we will be using */
		for(count=0;count<3;count++){

			/* the col we are on is the sum of the column that we start at */
			col=startingCol+count;

			/* Check to make sure [row][col] is in bounds */
			if((col>=0)&&(col<numRows)){

				/* if count is zero, h sub row */
				if(count==0){
					/* hValue is equal to h(row-1) */
					hValue=points->X[row] - points->X[row-1];

				}else if(count==1){
					hValue=2*((points->X[row] - points->X[row-1])+(points->X[row+1] - points->X[row]));
					if(row==0){
						hValue=2*(points->X[row+1] - points->X[row]);
					}



				}else if(count==2){
					hValue=(points->X[row+1] - points->X[row]);

				}

				/* Set value */
				matrix[row][col]=hValue;
			}
		}
	}

	/* Set "right" values */
	for(row=0;row<numRows;row++){

		if(row==0){

			alpha=3*( (points->Y[row+1] - points->Y[row]) / (points->X[row+1] - points->X[row] ) )-derivA;

		}else if(row==numRows-1){

			alpha=3*(derivB - ( (points->Y[row] - points->Y[row-1] )/(points->X[row]-points->X[row-1] ) ) );
		}else{

			alpha=3 * ( ( (points->Y[row+1] - points->Y[row])/(points->X[row+1] - points->X[row])) - ((points->Y[row] - points->Y[row-1])/(points->X[row] - points->X[row-1])      )  );

		}

		right[row]=alpha;

	}

	tridiagonal(points, spline, matrix, right, solution, numRows);

	for(j=0;j<numRows-1;j++){

		solve_coeff(points, spline, solution[j], solution[j+1], j);

	}


}


/* Finds the coefficients of the antural cubic spline for a given set of data */
extern void cspline_natural(Points *points, CSplines *spline){

	/* Set numRows equal to number of data points in points struct -1 */
	/* If there are N number of points, then there are N-1 number of splines */
	int numRows=points->N-2;

	/* N represents num points - 1 */
	int N=points->N-1;

	/* Declare matrix variable */
	MatElement **matrix;

	/* Declare right vector and solution variable */
	VectorElement *right, *solution;

	/* Declare values for counters */
	int row, col, j, startingCol, count;

	/* Declare values that will be put into our linear system as well as C, our Coeficient that we solve for */
	double hValue,alpha, Cj, Cj1;


	/* Make calls to allocate memory for matrices and vectors */
	matrix=matrix_alloc(numRows, numRows);
	right=vector_alloc(numRows);
	solution=vector_alloc(numRows);


	for(row=0;row<numRows;row++){

		/* The col that our values will start to be put into */
		startingCol=row-1;

		/* Count represents the basis for the formula that we will be using */
		for(count=0;count<3;count++){

			/* The col we are on is the sum of the column that we start on and the count */
			col=startingCol+count;

			/* check to make sure [row][col] is in bounds */
			if((col>=0)&&(col<numRows)){

				/* if count is zero, h sub row */
				if(count==0){
					hValue=points->X[row+1] - points->X[row];
				}else if(count==1){
					hValue= 2 * ((points->X[row+1]-points->X[row])+(points->X[row+2]-points->X[row+1]));
				}else if(count==2){
					hValue=points->X[row+2] - points->X[row+1];
				}
				/* Set value */
				matrix[row][col]=hValue;
			}
		}
	}

	/* Set "right" values */
	for(row=0;row<numRows;row++){

		/* J is the "sub value" */
		j=row+1;

		/* compute and set value of alpha */
		alpha=3 *(((points->Y[j+1] - points->Y[j])/(points->X[j+1]-points->X[j])) - ((points->Y[j]-points->Y[j-1])/(points->X[j-1] - points->X[j])));
		right[row]=alpha;
	}

	tridiagonal(points, spline, matrix, right, solution, numRows);

	/* We now have C(1)-C(n-1) */
	for(j=0;j<N;j++){
		if(j==0){
			Cj=0;
			Cj1=solution[j];
		}else{
			Cj=solution[j-1];
			if(j+1==N){
				Cj1=0;
			}else{
				Cj1=solution[j];
			}
		}

		/* Make call to Solve_Coeff */
		solve_coeff(points, spline, Cj, Cj1, j);

	}



}

/* Finds the coefficients of the not-a-knot cubic cpline for a given set of data */
extern void cspline_nak(Points *points, CSplines *spline){

	/* Set number of rows to number of data points in the struct -2 */
	/* If there are N+1 number of points, there are N number of splines */
	int numRows=points->N-2;

	/* N represente num points - 1 */
	int N=points->N-1;

	/* Declare matrix variables */
	MatElement **matrix;

	/* Declare right vector a nd solution variable */
	VectorElement *right, *solution;

	/* Declare values for counters */
	int row, col, j, startingCol, count;

	/* Declare values that will be put into our linear system as well as C, and C1 */
	double hValue, alpha, Cj, Cj1;

	/* Make calls to allocate memory for matruces and vectors */
	matrix=matrix_alloc(numRows, numRows);
	right=vector_alloc(numRows);
	solution=vector_alloc(numRows);

	for(row=0;row<numRows;row++){

		/* The col that our values will start to be put into */
		startingCol=row-1;

		/* Count represents the basis for the formula that we will be using */
		for(count=0;count<3;count++){

			/* The col we are on is the sum of the column that we start at + count */
			col=startingCol+count;

			/* Check to make sure [row][col] is in bounds */
			if((col>=0)&&(col<numRows)){

				hValue=5;


				if(count==0){
					if(row+1==numRows){
						hValue=(points->X[row+1] - points->X[row]) - (((points->X[row+2]-points->X[row+1])*(points->X[row+2]-points->X[row+1]))/(points->X[row+1]-points->X[row]));
					}else{
						hValue=points->X[row+1] - points->X[row];
					}
				}else if(count==1){
					if(row==0){
						hValue=(3*(points->X[row+1] - points->X[row])) + (2*(points->X[row+2] - points->X[row+1])) + (((points->X[row+1] - points->X[row])*(points->X[row+1] - points->X[row]))/(points->X[row+2] - points->X[row+1]));
					}else if(row+1==numRows){
						hValue=((3*(points->X[row+2]-points->X[row+1]))+(2*(points->X[row+1]-points->X[row]))+(((points->X[row+2]-points->X[row+1])*(points->X[row+2]-points->X[row+1]))/(points->X[row+1]-points->X[row])));
					}else{
						hValue=2*((points->X[row+1]-points->X[row])+(points->X[row+2] - points->X[row+1]));
					}


				}else if(count==2){
					if(row==0){
						hValue=(points->X[row+2] - points->X[row+1])-(((points->X[row+1] - points->X[row])*(points->X[row+1] - points->X[row]))/(points->X[row+2] - points->X[row+1]));
					}else{
						hValue=points->X[row+2] - points->X[row+1];
					}


				}

				/* Set value */
				matrix[row][col]=hValue;

			}
		}
	}

	/* Set "right" values */
	for(row=0;row<numRows;row++){

		/* j is the "sub" value to index into other structs */
		j=row+1;

		/* Compute and set value of alpha */

		alpha=3*(((points->Y[j+1]-points->Y[j])/(points->X[j+1]-points->X[j]))-((points->Y[j]-points->Y[j-1])/(points->X[j]-points->X[j-1])));
		right[row]=alpha;

	}

	/* make call to tridiagonal to solve for c values */
	tridiagonal(points, spline, matrix, right, solution, numRows);


	/* We now have c(1) -> C(n-1) */
	for(j=0;j<N;j++){
		if(j==0){
			Cj=((1+((points->X[2]-points->X[2])/(points->X[1]-points->X[0])))*(solution[j]))-(((points->X[1]-points->X[0])/(points->X[2]-points->X[1]))*(solution[1]));
			Cj1=solution[j];

		}else{
			Cj=solution[j-1];
			if(j+1==N){
				Cj1=(((points->X[j+1]-points->X[j])/(points->X[j]-points->X[j-1]))*(solution[j-2]))+((1+((points->X[j+1]-points->X[j])/(points->X[j]-points->X[j-1])))*(solution[j-1]));
			}else{
				Cj1=solution[j];
			}
		}

		/* Make call to solve_coeff */
		solve_coeff(points, spline, Cj, Cj1, j);
	}

}


/* Evaluates a cubic spline at a given point */
extern void cspline_eval(double x, double maxX, CSplines *spline){

	/* loop counter */
	int i,j;

	double minX,value;

	minX=spline->X[0];

	/* Check to make sure that point is not less than min */
	if(x<minX){

		printf("%f  X Value beyond lower bound\n",x);
		return;
	}

	/* Check to make sure that point is not greater than max */
	if(x>maxX){

		printf("%g  X Value beyond upper bound of %g\n",x,maxX);
		return;
	}

	/* perform evaluation loop */
	for(i=0;i< spline->N;i++){
		if(i+1==spline->N){
			j=i;
			break;
		}else if((x>=spline->X[i])&&(x<= spline->X[i+1])){
			j=i;
			break;
		}


	}

	value=(spline->a[j]) + (spline->b[j] * (x-spline->X[j])) + (spline->c[j] * ((x-spline->X[j])*(x-spline->X[j]))) + (spline->d[j] * ((x-spline->X[j])*(x-spline->X[j])*(x-spline->X[j])));

	fprintf(stdout,"%g %g\n",x,value);


}



static void tridiagonal(Points *points, CSplines *spline, MatElement **matrix, VectorElement *right, VectorElement *solution, int numRows){


	/* Declare perm vector */
	MatElement **perm;

	/* Create permutation matrix */
	perm=matrix_identity(numRows);

	linalg_LU_decomp(matrix, perm, numRows);

	linalg_LU_solve(matrix, perm, right, solution, numRows);


}


void solve_coeff(Points *points, CSplines *spline, double Cj, double Cj1, int j){

	/* Declare values of coefficients */
	double A, B, D;

	/* Solve for D */
	D=(Cj1-Cj)/(3 *(points->X[j+1]-points->X[j]));

	/* Solve for B */
	B=((points->Y[j+1]-points->Y[j])/(points->X[j+1]-points->X[j])) - ((((2*Cj)+Cj1)/3)*(points->X[j+1] - points->X[j]));

	/* Solve for A */
	A=points->Y[j];

	/* Make push to spline */
	PushToSpline(spline, &A, &B, &Cj, &D, &points->X[j]);

}

void display_spline(CSplines *spline, Points *point){

	int j;

	double x1;

	int N=spline->N;


	for(j=0;j<N;j++){

		if(j==(N-1)){
			x1=point->X[j+1];
		}else{
			x1=spline->X[j+1];
		}
		fprintf(stdout, "%g  %g  %g  %g  %g  %g\n", spline->X[j],x1, spline->d[j], spline->c[j], spline->b[j], spline->a[j]);

	}
	/* End for loop */

}
/* end display spline */
