#include <stdio.h>
#include <omp.h>
#include <time.h>

static long num_steps = 100000;
double step;

void main ()
{
	omp_set_num_threads(4);
	
	unsigned int i; double x, pi, sum = 0.0;
	step = 1.0/(double) num_steps;
  double t;
  t = omp_get_wtime();
  // SPMD type of program
	#pragma omp parallel private(i,x) 
	{
    #pragma omp for reduction(+:sum)
		for (i=0;i< num_steps; i++){
			x = (i+0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}
	}
	t = omp_get_wtime() - t;
	pi = sum * step;
	printf("%f\n", pi);
  printf("Clock Parallel: %f\n", (double)t);

}
