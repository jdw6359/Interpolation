/* Josh Woodward, HW7 for Applied Programming, 4-18-2014 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interp.h"
#include "Dynamic.h"


int main(int argc, char *argv[]){

	/* Check to make sure that not only one arg was supplied to the cmdline */
	if(argc!=1){


		/* Check to see that argv[1] is one of three expected values */
		if( ((strcmp(argv[1], "-nak")==0) || (strcmp(argv[1],"-natural")==0) || (strcmp(argv[1],"-clamped")==0))&&(argc==3)){

			/* Declare pointer to file object */
			FILE* inputFile;

			/* Attempt to open the input file */
			inputFile=fopen(argv[2], "r");

			/* Check to make sure that the input file is not null */
			if(inputFile==NULL){

				fprintf(stdout, "\nFile was not opened properly\n");
				return 2;

			}else{
				/* Declare devivA and derivB values (first two values in file */
				double derivA, derivB;

				/* Declare a points variable */
				Points points;

				/* Declare a splines variable */
				CSplines spline;

				/* Values to be scanned in */
				double xVal, yVal;

				/* Call to create points structure */
				CreatePoints(&points);

				/* Call to Create Splines structure */
				CreateSpline(&spline);

				/* Scan the first two values for deriv at A and B */
				fscanf(inputFile, "%lf %lf", &derivA, &derivB);


				while(fscanf(inputFile, "%lf %lf", &xVal, &yVal)!=EOF){

					PushToPoints(&points, &xVal, &yVal);

				}

				if((strcmp(argv[1], "-nak")==0)){
					cspline_nak(&points, &spline);
					display_spline(&spline, &points);
				}
				if((strcmp(argv[1],"-natural")==0)){
					cspline_natural(&points, &spline);
					display_spline(&spline, &points);
				}
				if((strcmp(argv[1],"-clamped")==0)){
					cspline_clamped(&points,derivA,derivB, &spline); 
					display_spline(&spline, &points);
				}

			}
			/* end check for file opening properly */

		}
		/* end check to see if argv is one of three expected values */



		/* Check to see that argv[1] is "-e" */
		else if((strcmp(argv[1],"-e")==0)&&(argc==4)){

			/* Declare pointer to file objects */
			FILE *splineFile, *evalFile;

			/* attempt to open both files */
			splineFile=fopen(argv[2], "r");
			evalFile=fopen(argv[3], "r");

			/* Check to make sure that both files were opened properly */
			if((splineFile==NULL)||(evalFile==NULL)){
				fprintf(stdout, "\nFiles were not opened properly\n");
			}else{

				/* Declare variables to be read from sparameters file */
				double x, a, b, c, d;

				/* Variable that we are scanning in, but ignoring */
				double maxX;

				/* Variable that we are going to be evaluating at */
				double evalPoint;

				/* Declare and initialize the spline */
				CSplines spline;
				CreateSpline(&spline);

				while(fscanf(splineFile, "%lf %lf %lf %lf %lf %lf",&x,&maxX,&d,&c,&b,&a )!=EOF){

					/* Make call to Push to splines */
					PushToSpline(&spline, &a, &b, &c, &d, &x);
				}

				while(fscanf(evalFile, "%lf", &evalPoint)!=EOF){
					cspline_eval(evalPoint,maxX,&spline);
					/* make call to eval at given point */
				}



			}

		}
		/* end check for "-e" */
		else{
			fprintf(stdout, "Usage: hw7 <-nak, natural, clamped> data.txt\nUsage: hw7 -e sparameters.txt eval.txt\n");

		}

	}else{

		/* one arg was supplied to the user, print usage message */
		fprintf(stdout, "Usage: hw7 <-nak, natural, clamped> data.txt\nUsage: hw7 -e sparameters.txt eval.txt\n");

	}
	/* End arg check */







	return 0;

}
/* End main method */
