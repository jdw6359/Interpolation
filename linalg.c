 /*********************************************************
 * Linear Algebra Module
 * Rev: 10/24/2013,  Juan C. Cockburn  (jcck@ieee.org)
 *********************************************************/

#include "linalg.h"
#include <math.h>

/* Allocate memory space for matrix, all at once */
MatElement **matrix_alloc(int nr, int nc) {
  int i;
  MatElement *ptr;
  MatElement **A;

  A = malloc( nr * sizeof(MatElement *));    /* array of ptrs   */
  ptr = calloc( nr*nc, sizeof(MatElement) ); /* matrix elements */
  for (i=0; i<nr; i++)             /* set row pointers properly */
    A[i] = ptr + nc*i;
  return A;
}

/* Allocate memory space for vector, all at once */
VectorElement *vector_alloc(int size){

	/* Declare pointer variable to vector */
	VectorElement *v;

	/* Allocate the memory */
	v=malloc(size * sizeof(VectorElement));

	/* Return pointer to the allocated vector */
	return v;
}

/* Release memory used by matrix */
void matrix_free(MatElement **A) {
  free(A[0]);
  free(A);
}

/* Release memory used by the vector */
void vector_free(VectorElement *p){
	free(p);
}

/* Print matrix elements */
void matrix_print(MatElement **A, char * format, int nr, int nc) {
	int i,j;
	for (i=0; i<nr; i++) {
		for (j=0; j<nc; j++){
			fprintf(stdout,format, A[i][j]);

		}
		fprintf(stdout, "\n");
	}
}

/* Print vector elements */
void vector_print(VectorElement *v, char * format, int size){
	int i;
	for(i=0;i<size;i++){
		fprintf(stdout,format,v[i]);
	}
	fprintf(stdout,"\n");
}


/* Create and Identity Matrix */
MatElement **matrix_identity(int n) {
  int i;
  MatElement **A=matrix_alloc(n, n);
  for (i=0; i<n; ++i)
    A[i][i] = (MatElement) 1;
  return A;
}

int linalg_LU_decomp(MatElement **A, MatElement **p, int dim){

	/* Declare variables */
	int k,row,col,pivotCounter, pivotIndex, pivotSwapCounter;
	double pivot, maxPivot;

	/* iterate once for every row of the matrix */
	for(k=0;k<dim;k++){

		/* Initially set pivotIndex to k, will stay here unless changed */
		pivotIndex=k;
		maxPivot=A[k][k];
		for(pivotCounter=k;pivotCounter<dim;pivotCounter++){

			/* Set pivot to value at kth row, in the set column */
			pivot=A[pivotCounter][k];
			if(fabs(pivot)>fabs(maxPivot)){
				/* Determine the largest value of pivot */
				maxPivot=pivot;

				/* keep track of row of largest pivot */
				pivotIndex=pivotCounter;
			}
		}

		/* The final pivot is equal to the largest value */
		pivot=maxPivot;

		/* Only perform swap operations if necessary. I.E.
		   the iteration row is not equal to the row of largest index */
		if(k!=pivotIndex){

			/* swap elements in rows k and pivot index */
			for(pivotSwapCounter=0;pivotSwapCounter<dim;pivotSwapCounter++){

				double temp, tempPermValue;
				temp=A[k][pivotSwapCounter];
				A[k][pivotSwapCounter]=A[pivotIndex][pivotSwapCounter];
				A[pivotIndex][pivotSwapCounter]=temp;


				/* Swap each col value for the kth and pivotIndex(th) rows of the perm matrix */
				tempPermValue=p[k][pivotSwapCounter];
				p[k][pivotSwapCounter]=p[pivotIndex][pivotSwapCounter];
				p[pivotIndex][pivotSwapCounter]=tempPermValue;

			}



		}

		/* Set the in-place "pivot factor" */
		for(row=k+1;row<dim;row++){
			A[row][k]=A[row][k]/pivot;
		}

		/* Go through each row and perform factor based operations */
		for(row=k+1;row<dim;row++){

			for(col=k+1;col<dim;col++){
				A[row][col]=A[row][col] - A[row][k] * A[k][col];
			}

		}

	}

	return 0;


}
/* Implements the in place Gaussian Elimination process with
 * partial pivoting. It should take as input arguments the
 * matrix A and return the results in the overwritten matrix A
 * that encodes the lower part of L and U matrices and the
 * permutaion vector p that defines the permutation matrix P
 */

int linalg_LU_solve(MatElement **A, MatElement **p, VectorElement *b, VectorElement *x, int size){


	/* b represents the right hand side matrix, and x represents
	 * the matrix that we will be putting the values of x into
	 */


	/* Declare variables here */
	int vectorLooper, k, innerK, permLooper, permIndex;

	VectorElement *f;

	f=vector_alloc(size);

	for(vectorLooper=0;vectorLooper<size;vectorLooper++){
		f[vectorLooper]=0;
	}

	/* Set values of vector F here. F represents the intermediate
	 * values obtained by L(Ux)=b, forward substitution
	 */

	for(k=0;k<size;k++){
		double fValue;

		/* get index into right vector */
		for(permLooper=0;permLooper<size;permLooper++){
			if(p[k][permLooper]==1){
				/* Set index to permLooper */
				permIndex=permLooper;
			}
		}

		/* get access to f value */
		fValue=b[permIndex];

		/* continually decrement fValue by
		 * values of matrix in row k and columns prior to k
		 */
		for(innerK=0;innerK<k;innerK++){
			fValue=fValue -(A[k][innerK] * f[innerK]) ;
		}
		f[k]=fValue;
	}

	for(k=size-1;k>=0;k--){
		double xValue;
		/* get the initial x value from f[k] */

		xValue=f[k];

		for(innerK=size-1;innerK>k;innerK--){
			/* this is where the subtraction will take place */
			xValue=xValue - (x[innerK] *A[k][innerK]);
		}

		/* Perform the division here */
		xValue=xValue / A[k][k];

		/* Set the value of x[k] here */
		x[k]=xValue;
	}

	/* Set values of vector x here. x is the vector that contains
	 * the values of x that we will provide as a solution
	 */

	return 0;
}
/* Finds the solution to the system Ax=b given packed LU matrix
 * obtained by the Elimination step in decomp. Should take as input
 * arguments the overwritten matrix A (generated by linalg_LU_decomp),
 * the pivot vector p, the right hand side vector b, and "return"
 * the solution in vector x.
 */

void print_plu(MatElement **A, MatElement **p, int size){

	int k, innerK;

	fprintf(stdout, "\nPrinting L Matrix: \n");

	for(k=0;k<size;k++){
		for(innerK=0;innerK<size;innerK++){
			if(k==innerK){
				fprintf(stdout," 1 ");
			}else if(innerK>k){
				fprintf(stdout," 0 ");
			}else{
				fprintf(stdout," %g ",A[k][innerK]);
			}
		}
		fprintf(stdout,"\n");
	}

	fprintf(stdout, "\nPrinting U Matrix: \n");

	for(k=0;k<size;k++){
		for(innerK=0;innerK<size;innerK++){
			if(innerK<k){
				fprintf(stdout," 0 ");
			}else{
				fprintf(stdout," %g ", A[k][innerK]);
			}
		}
		fprintf(stdout,"\n");

	}

	fprintf(stdout, "\nPrinting Permutation Matrix: \n");

	for(k=0;k<size;k++){
		for(innerK=0;innerK<size;innerK++){
			fprintf(stdout," %g ",p[k][innerK]);
		}
		fprintf(stdout,"\n");
	}


}
/* unpack the matrices L, U, and P, and print them as well */
