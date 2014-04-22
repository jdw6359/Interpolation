#include <stdio.h>
#include <stdlib.h>


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

unsigned int PushToPoints(Points *points, double X, double Y){


	return 0;
}
/* End push to points */

void DestroyPoints(Points *points){

}
/* End destroy points */
