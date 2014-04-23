/*
 * Header file for dynamic CSplines and points
 * Author: Josh Woodward
 */


#define GROWTH_AMOUNT (5)


void CreatePoints(Points*);

unsigned int PushToPoints(Points*, double*, double*);

void DestroyPoints(Points*);


void CreateSpline(CSplines*);

unsigned int PushToSpline(CSplines*, double*, double*, double*, double*, double*);

void DestroySpline(CSplines*);
