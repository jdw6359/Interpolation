/***********************************************************************************
 Purpose : Show how to call gnuplot from C to generate  a plots
 Requires: curve.txt (text file name with data for plots)
           gnuplot   (tested with version 4.4 )
           pipes     (Not ANSI C, tested under Linux)
 Author  : Juan C. Cockburn Nov 2014
 Revised : April 15, 2014
 Warning : popen is not part of standard C; expect warnings if using -ansi !

 To view the png figure use "display" (do not forget to set your X11 terminal first)
 ***********************************************************************************/
#include <stdio.h>

int main(void) {
/* Declare variables */
  FILE *pipe; /* pipe is a pointer to a a pipe process */

  printf(" ----------------------------------------------------------\n");
  printf(" Example: Using gnuplot to draw figures within C programs   \n");
  printf(" ----------------------------------------------------------\n");

/* Open pipe to communicate with gnuplot */
  if( (pipe = (FILE *) popen("gnuplot -persist","w")) == NULL ) {
    fprintf(stderr,"Unable to open pipe to gnuplot\n");
    return -1;
  }
    
/* Send gnuplot commands through pipe */
#if 0
  /* gnuplot: send output to X11 terminal with desired font */
  fprintf(pipe,"set terminal x11 font 'Vera.ttf'\n");
#endif
  /* gnuplot: send output to png file with desired font */
  fprintf(pipe,"set terminal png enhanced font 'Vera.ttf'\n"); 
  fprintf(pipe,"set output 'splines.png' \n"); 

  /* gnuplot: set title, labels, legend  and line styes */
  fprintf(pipe,"set title 'Cubic spline interpolation result '\n");
  fprintf(pipe,"set xlabel 'x'\n");
  fprintf(pipe,"set ylabel 'f(x)'\n");
  fprintf(pipe,"set style data lines\n"); /* draw lines between data pts  */

  /* gnuplot: set parameters to draw multiple plots in the same figure 	  */
  fprintf(pipe,"set xrange [-2:2]\n");		/* set x range		  */ 
  /* gnupolot: read deata file plot each curve */
  fprintf(pipe,"plot 'curve.txt' using 1:2 lt 1 lw 2 t 'cubic spline' \n");

/* Close pipe */
  pclose(pipe);

  return 0 ;
}
