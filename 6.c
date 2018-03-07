#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	double x,y;
	int inside=0;
	int outside=0;
#pragma omp parallel for
	for (int i=0; i<1000000; i++) {
		x = (double)rand()/(RAND_MAX);
		y = (double)rand()/(RAND_MAX);
		if (((x-0.5)*(x-0.5)+(y-0.5)*(y-0.5)) <= 0.25)
			inside++;
		else
			outside++;
	}

	printf("%f\n",(float)4*(inside/inside+outside));

	return 0;
}
