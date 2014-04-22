/* Josh Woodward, HW7 for Applied Programming, 4-18-2014 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interp.h"

int main(int argc, char *argv[]){

	/* Check to make sure that not only one arg was supplied to the cmdline */
	if(argc!=1){


		/* Check to see that argv[1] is one of three expected values */
		if( (strcmp(argv[1], "-nak")==0) || (strcmp(argv[1],"-natural")==0) || (strcmp(argv[1],"-clamped")==0)){

			/* Declare pointer to file object */
			FILE* inputFile;

			/* Attempt to open the input file */
			inputFile=fopen(argv[2], "r");

			/* Check to make sure that the input file is not null */
			if(inputFile==NULL){

				fprintf(stdout, "\nFile was not opened properly\n");
				return 2;

			}else{
				if((strcmp(argv[1], "-nak")==0)){
					fprintf(stdout, "Starting nak\n");


				}
				if((strcmp(argv[1],"-natural")==0)){
					fprintf(stdout,"Starting natural\n");


				}
				if((strcmp(argv[1],"-clamped")==0)){
					fprintf(stdout,"Starting clamped\n");

				}


			}
			/* end check for file opening properly */

		}
		/* end check to see if argv is one of three expected values */



		/* Check to see that argv[1] is "-e" */
		else if(strcmp(argv[1],"-e")==0){

		}
		/* end check for "-e" */
		else{
			fprintf(stdout,"hw7 takes agruments of -nak, -natural, -clamped, and -e\n");

		}



	}else{

		/* one arg was supplied to the user, print usage message */
		fprintf(stdout, "Usage: hw7 <-nak, natural, clamped> data.txt\nUsage: hw7 -e sparameters.txt eval.txt\n");

	}
	/* End arg check */







	return 0;

}
/* End main method */
