#include <stdio.h>
#include <omp.h>

int main(void)
{
#pragma omp parallel
{
#pragma omp single
{
	printf("Programacao "); 
	#pragma omp task
	{
		printf("Paralela  ");
	}
#pragma omp task
	{
	printf("eh ");
	}
#pragma omp task
	{
        printf("muito ");
	}
#pragma omp taskwait
        printf("legal! ");
}
}
    printf("\n");

    return 0;
}
