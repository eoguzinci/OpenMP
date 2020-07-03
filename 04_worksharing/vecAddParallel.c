#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(void)
{
	int numElements = 10;

	float a[] = {1.0, 2.0, 1.2, 3.4, 7.5, 8.3, 6.7, 7.1, 1.3, 4.5};
	float b[] = {1.0, 2.0, 1.2, 3.4, 7.5, 8.3, 6.7, 7.1, 1.3, 4.5};

	#pragma omp parallel for
	for (int i = 0; i < numElements; i++){
		a[i] = a[i] + b[i];
	}

	for (int i = 0; i < numElements; i++) {
		printf(" %f ", a[i]);
	}
	printf("\n");
	return 0;
}