/*
 * Header file for dynamic CSplines and points
 * Author: Josh Woodward
 */

/* Data types */
typedef struct{
	int N;     /* Number of elements in the array */
	double *a; /* Pointer to constant coefficients */
	double *b; /* Pointer to linear coefficients */
	double *c; /* Pointer to quadratic coefficients */
	double *d; /* Pointer to cubic coefficients */
	double *X; /* pointer interpolation interval partition */
} CSplines;

typedef struct{
	int N;    /* number of elements in the array */
	double *X;/* Pointer to X data */
	double *Y;/* Pointer to Y data */
	int Size; /* Size of dynamic arrays */
	int Next; /* Index to next point in the array */
} Points
