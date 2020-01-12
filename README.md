# OpenMP: An API for Writing Multithreaded Applications

* Parallel Application for Shared Memory
* Multi-threaded(MT) programs in Fortran, C/C++
* Standardizes last 20 years SMP practice

## Shared Memory
Any computer composed of multiple processing elements that share an address space. There are two classes:

1. Symmetric Multiprocessor (SMP): Assumes that OS treats each processor equally and a shared address space is in equal distance to each processor. Everything is plain. No processor or data unit is special.
2. Non-Uniform Address Space Multiprocessor (NUMA): Different memory regions have different access costs. Some memory segmented as "Near" or "Far" to a specific processor.

Of course, NUMA approach is more realistic due to cache hiearchy, but needs more programming effort.

## Environment
Include the OpenMP library if you want to use it.
```c
#include <omp.h>
```

To compile a code with omp structures:
` gcc -o omp_helloc -fopenmp omp_hello.c`

If you haven't specified the number of threads to be used:
`export OMP_NUM_THREADS=2`

Sample Code:
```c
#include <stdio.h>
#include <omp.h> 

int main() {
  #pragma omp parallel
  {
      int ID = omp_get_thread_num();
      printf("hello from processor: %d\n", ID);
  }
  return 0;
}
```

## Introduction

* OpenMP is a multi-threading, shared address model. This means that threads communicates by sharing variables.

But,

* Unintended sharing of variables causes race conditions: when the program's outcome changes as the threads are scheduled differently.
* To avoid race conditions -> use synchronization to protect data conflicts.
* Synchronization is expensive, therefore, change how data is accessed to minimize the need of synchronization.

## Creating Threads

* You can create threads with the parallel construct
```c
omp_set_num_threads(4);
#pragma omp parallel
{
 ...   
}
```

## Synchronization
Synchronization is used to impose order constraints and to protect access to shared data. This is in order to prevent __false sharing__.

### What is false sharing? 
The threads trying to use the same cache line at the same time, therefore, each update will cause the same cache line to "slosh back and forth" between the threads. 

If you promote scalars to an array to support creation of an SPMD program, the array elements are contagious in memory and hence share cache lines. This results to __poor scalability__.

* High level synchronization
    - critical
    - atomic
    - barrier
    - ordered
* Low level synchronization
    - flush
    - locks (both simple and nested)

### Synchronization: critical
Mutual exclusion: Only one thread at a time can enter __critical__ region.

```c
float res
#pragma omp parallel
{
    float B; int i, id, nthrds;
    id = omp_get_thread_num();
    nthrds = omp_get_num_threads();
    for(i=id; i<niters;i+nthrds){
        B = big_job(i);
    #pragma omp critical // threads wait their turn - only one at a time calls consume()
        consume(B, res); 
    }
}
```

Be sure that not a lot of things happening in the `critical` section because only a single thread can access the critical section at a time and therefore, the CPU time will be multiplied by the number of threads at this section due to serialized processing.

__Note:__ Do not put a `critical` section inside a loop! This will serialize whole loop.

### Synchronization: atomic
Atomic provides mutual exclusion but only applies to the update of a memory location (the update of X in the following example)
```c
#pragma omp parallel
{
    double tmp, B;
    B = do_it();
    tmp = big_ugly(B);
#pragma omp atomic
    X += tmp; //atomic only protects the read/update of X
}
```
In essence, `atomic` directive provides a mini-`critical` section. But, the statement inside the `atomic` section must be one of the following forms:

```c
x <binary_operation> = expr
x++;
++x;
x--;
--x;
```

### Synchronization: barrier

Each thread wait at the barrier until all threads arrive. When all threads arrive the barrier, they are allowed to go on.

```c
#pragma omp parallel
{
  int id = omp_get_thread_num();
  A[id] = big_cal1(id);

#pragma omp barrier //wait until all the A[id]'s calculated.
  B[id] = big_cal2(id,A);  
}
```

## Parallel Loops

Is it 
