#include <omp.h>
#include <time.h>
#include <stdio.h>
static long num_steps = 100000; double step;

#define NUM_THREADS 4
// To avoid false sharing
#define PAD 8 // Assume 64 byte L1 cache line size


void main()
{
    int i, nthreads;
    double pi, sum[NUM_THREADS][PAD];
    step = 1.0 /(double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    
    clock_t t = clock();
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id==0)  nthreads = nthrds;
        for(i=id, sum[id]=0.0; i<num_steps; i=i+nthrds){
            x = (i+0.5)*step;
            sum[id][0]+= 4.0 /(1.0+x*x);
        }
    }
    t = clock() - t;
    for(i=0, pi=0.0; i< nthreads; i++)
        pi += sum[i][0] * step;
    printf("%f\n", pi);
    printf("Clock: %f\n", (double)t);
}
