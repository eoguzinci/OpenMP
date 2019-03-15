float* matvec(float* matrix, float* vector, float* result, int size_i, int size_j)
{
   int i,j;

#pragma omp parallel shared(matrix,result,vector) private(i,j) 
   {
#pragma omp for  schedule(static)
   for (i=0; i<size_i; i=i+1){
      result[i]=0.;
      for (j=0; j<size_j; j=j+1){
         result[i]=(result[i])+((matrix[i+size_i*j])*(vector[j]));
      }
   	}
	}
   return result;
}

#include <stdio.h>

int main(int argc, char const *argv[])
{
	float mat[9] = {2,3,7, 5,2,1, 15, 2, 6};
	float vec[3] = {5, 8, 2};
	float res[3];
	int row = 3; int col = 3;
	float* solution;

	solution = matvec(mat, vec, res, row, col);
	unsigned int i;
	for(i=0; i<row; i++){
		printf("%f\n", res[i]);
	}

	return 0;
}