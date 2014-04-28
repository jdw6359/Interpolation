#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interp.h"
#include "Dynamic.h"



void CreatePoints(Points *points){

	/* Set N(entries used) to 0 */
	points->N=0;

	/* Set Size(Size of dynamic arrays to 0 */
	points->Size=0;

	/* No memory needs to be allocated just yet */
	points->X=NULL;
	points->Y=NULL;


}
/* End create points */

void CreateSpline(CSplines *spline){

	/* Set N(entries used) to 0 */
	spline->N=0;

	/* Set Size(Size of dynamic Arrays to 0 */
	spline->Size=0;

	/* No memory needs to be allocated just yet */
	spline->a=NULL;
	spline->b=NULL;
	spline->c=NULL;
	spline->d=NULL;
	spline->X=NULL;

}
/* End create spline */

unsigned int PushToPoints(Points *points, double *X, double *Y){


	/* Do the arrays need to be made larger? */
	if(points->N==points->Size){

		/* Increase the size of the dynamic array */
		points->Size+=GROWTH_AMOUNT;

		/* Reallocate storage for the array elements using a larger size */
		points->X=realloc(points->X, points->Size * sizeof(double));
		points->Y=realloc(points->Y, points->Size * sizeof(double));


		/* Check to make sure that memory was properly reallocated */
		if((points->X==NULL) || (points->Y==NULL)){

			fprintf(stdout, "PushToPoints() realloc() failed!\n");

		}

	}
	/* Realloc completed */

	/* Copy the point value into the array where the insertion index is pointing */
	memcpy(&(points->X[points->N]), X, sizeof(double));
	memcpy(&(points->Y[points->N]), Y, sizeof(double));

	/* Increment the number of elements used in the array */
	points->N++;

	/* Return the index of the last element inserted */
	return (unsigned int) (points->N-1); 



}
/* End push to points */


unsigned int PushToSpline(CSplines *spline, double *a, double *b, double *c, double *d, double *X){

	/* Do the arrays need to be made larger? */
	if(spline->N==spline->Size){

		/* Increase the size of the dynamic arrays */
		spline->Size+=GROWTH_AMOUNT;

		/* Reallocate storage for the array elements using a larger size */
		spline->a=realloc(spline->a, spline->Size * sizeof(double));
		spline->b=realloc(spline->b, spline->Size * sizeof(double));
		spline->c=realloc(spline->c, spline->Size * sizeof(double));
		spline->d=realloc(spline->d, spline->Size * sizeof(double));
		spline->X=realloc(spline->X, spline->Size * sizeof(double));


		/* Check to make sure that memory was properly reallocated */
		if((spline->a==NULL)||(spline->b==NULL)||(spline->c==NULL)||(spline->d==NULL)||(spline->X==NULL)){
			fprintf(stdout, "PushToSpline() realloc() failed!\n");
		}

	}
	/* realloc completed */

	/* copy the point value into the array where the insertion index is pointing */
	memcpy(&(spline->a[spline->N]), a, sizeof(double));
	memcpy(&(spline->b[spline->N]), b, sizeof(double));
	memcpy(&(spline->c[spline->N]), c, sizeof(double));
	memcpy(&(spline->d[spline->N]), d, sizeof(double));
	memcpy(&(spline->X[spline->N]), X, sizeof(double));

	/* increment the number of elements used in the array */
	spline->N++;


	return (unsigned int) (spline->N-1);


}
/* End push to spline */


void DestroyPoints(Points *points){

}
/* End destroy points */


void DestroySpline(CSplines *spline){

}
/* End destroy spline */


