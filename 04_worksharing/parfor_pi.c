#include <stdio.h>
#include <time.h>
#include <omp.h>

static long num_steps = 100000;
// static long num_steps = 20;
double step;

void main ()
{ 
	double pi, sum = 0.0;
	step = 1.0/(double) num_steps;
    double t = omp_get_wtime();
    #pragma omp parallel
    {
    	double x;
    	#pragma omp for reduction(+:sum)
		for (int i = 0;i < num_steps; i++){
			// int id = omp_get_thread_num();
			x = (i+0.5)*step;
			sum += 4.0/(1.0+x*x);
			// printf("Thread: %d iter = %d x = %f\n",id,i,x);
		}
	}
	pi = step * sum;
    t = omp_get_wtime() - t;
	printf("PI: %f\n", pi);
    printf("Clock ParFor: %f\n", t);

} 
