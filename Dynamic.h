/*
 * Header file for dynamic CSplines and points
 * Author: Josh Woodward
 */


#define GROWTH_AMOUNT (10)


void CreatePoints(Points *points);

unsigned int PushToPoints(Points *points, double *X, double *Y);

void DestroyPoints(Points *points);

