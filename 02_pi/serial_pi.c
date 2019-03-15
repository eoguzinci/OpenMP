#include <stdio.h>
#include <time.h>
#include <omp.h>

static long num_steps = 100000;
double step;

void main ()
{ 
	int i; double x, pi, sum = 0.0;
	step = 1.0/(double) num_steps;
    double t = omp_get_wtime();
	for (i=0;i< num_steps; i++){
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}
    t = omp_get_wtime() - t;
	pi = step * sum;
	printf("%f\n", pi);
    printf("Clock Serial: %f\n", t);
}
