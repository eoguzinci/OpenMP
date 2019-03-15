#include <stdio.h>
int main() {
  #pragma omp parallel num_threads(3)
  {
    printf("https://helloacm.com\n");
  }
  return 0;
}