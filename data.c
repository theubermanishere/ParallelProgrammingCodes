#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
  	int i;
  	int n = 10;

  	printf("shared n\n");
  	/* shared by default */
#pragma omp parallel
  	{
    	printf("thread %d: n = %d\n", omp_get_thread_num(), n);
    	/* n = omp_get_thread_num(); */
  	}
  	printf("n = %d\n", n);

  	printf("\n\nshared n\n");
#pragma omp parallel default(none) shared(n)
  	{
    	printf("thread %d: n = %d\n", omp_get_thread_num(), n);
    	/* n = omp_get_thread_num(); */
  	}
  	printf("n = %d\n", n);

  	n = 20;
  	printf("\n\nprivate n\n");
#pragma omp parallel private(n)
  	{
    	printf("thread %d: n = %d\n", omp_get_thread_num(), n);
    	n = omp_get_thread_num();
  	}
  	printf("n = %d\n", n);

  	n = 30;
  	printf("\n\nfirstprivate n\n");
#pragma omp parallel firstprivate(n)
  	{
    	printf("thread %d: n = %d\n", omp_get_thread_num(), n);
    	n = omp_get_thread_num();
  	}
  	printf("n = %d\n", n);

#if 1
  	printf("\n\nlastprivate n\n");
#pragma omp parallel for lastprivate(n)
  	for(i = 0; i <= 100; ++i)
  	{
    	n = i*i;
  	}
  	printf("n = %d\n", n);
#endif

  	return 0;
}
