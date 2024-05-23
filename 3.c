#include <stdio.h>
#include <omp.h>

int main(void)
{
#pragma omp parallel
{
#pragma omp single
{
	printf("Programação  ");
        printf("Paralela  ");
        printf("eh ");
        printf("muito ");
        printf("legal! ");
}
}
    printf("\n");

    return 0;
}
