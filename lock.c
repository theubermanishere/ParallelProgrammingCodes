#include <omp.h>
#include <stdio.h>

omp_lock_t my_lock;
int main() {
  	omp_init_lock(&my_lock);
#pragma omp parallel
  	{
    	int tid = omp_get_thread_num();
    	int i, j;
    	for (i = 0; i < 3; ++i) {
      		//      omp_set_lock(&my_lock);
      		printf("Thread %d --starting lock region\n", tid);

      		printf("Thread %d --finishing lock region\n", tid);
      		//omp_unset_lock(&my_lock);
    	}
  	}
  	omp_destroy_lock(&my_lock);
}
