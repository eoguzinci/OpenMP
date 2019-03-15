#include <stdio.h>
#include <omp.h> 

int main() {
	omp_set_num_threads(4);
	#pragma omp parallel	
  	// #pragma omp parallel num_threads(4)
  	{
  		int ID = omp_get_thread_num();
  		printf("hello from processor: %d\n", ID);
  	}
  	return 0;
}
