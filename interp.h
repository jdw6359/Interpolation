/*
 ================================================================= 
 Header File for (Spline) Interpolation Module 
 Revised: JCCK. 11/18/2013
 ================================================================= 
*/

#ifndef _INTERP_H_
#define _INTERP_H_

/* Data Types */
typedef struct
  {
   int     N;    /* Number of Elements in array         */
   double *a;    /* Pointer to Constant coefficients   	*/
   double *b;    /* Pointer to Linear coefficients      */
   double *c;    /* Pointer to Quadratic coefficients   */
   double *d;    /* Pointer to Cubic coefficients       */
   double *X;    /* Pointer interpolation interval  partition */
   } CSplines;

typedef struct
  {
   int     N;    /* Number of Elements in array  */
   double *X;    /* Pointer to X data            */
   double *Y;    /* Pointer to Y data            */
   int  Size;    /* Size of dynamic arrays       */
   int  Next;    /* Index to next point in array */
  } Points;
  
/* Function Prototypes, add more if needed */

extern void cspline_clamped( Points*, double, double, CSplines*);
/***************************************************************************************
 cspline_clamped
        Finds the coefficients of the clamped cubic spline for a given set of data points
     SYNTAX:
	   cspline_clamped ( Data, fpa, fpb , Splines)
     INPUTS:
          Data	    Pointer to Data Points array
          fpa	    derivative of function at x=a
          fpb	    derivative of function at x=b
          Splines   Pointer to Spline Structure
     OUTPUTS: 
          Splines Coefficients of Cubic Spline Interpolants
*****************************************************************************************/

extern void cspline_natural( Points*, CSplines* );
/***************************************************************************************
 cspline_natural
        Finds the coefficients of the natural cubic spline for a given set of data points
     SYNTAX:
	   cspline_natural ( Data, Splines )
     INPUTS:
          Data	    Pointer to Data Points array
          Splines   Pointer to Spline Structure
     OUTPUTS: 
          Splines Coefficients of Cubic Spline Interpolants 
*****************************************************************************************/

extern void cspline_nak( Points*, CSplines* );
/***************************************************************************************
 cspline_nak
        Finds the coefficients of the not-a-knot cubic spline for a given set of data points
     SYNTAX:
	   cspline_nak ( Data, Splines )
     INPUTS:
          Data	    Pointer to Data Points array
          Splines   Pointer to Spline Structure
     OUTPUTS: 
          Splines Coefficients of Cubic Spline Interpolants 
*****************************************************************************************/

extern double cspline_eval( double, CSplines* );
/***************************************************************************************
 cspline_eva
       Evaluates a cubic spline at a give point 
     SYNTAX:
	   cspline_eval ( x, Splines )
     INPUTS:
          x         Point at which splines should be evaluated
          Splines   Pointer to Spline Structure
     OUTPUTS: 
          value of spline at desired point x
*****************************************************************************************/

#endif /*  _INTERP_H_ */