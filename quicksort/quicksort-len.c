// PPGCA 2020-1
// PPA - Programação Paralela avançada
// Tarefa: OMP2 - Quicksort com tasks
// Nome: Flavio Bayer / Vitor Gauer
// Contém trechos de códigos de quicksort provenientes de: https://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int partition(int *arr, size_t len) {
    int pivot = arr[len/2];
    size_t i, j;
    for (i=0, j=len-1; ; i++, j--) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i >= j) break;

        size_t temp = arr[i];
        arr[i]   = arr[j];
        arr[j]   = temp;
    }
    return i;
}

void quicksort(int *arr, size_t len) {
    if (len<2) return;
    size_t i = partition(arr, len);
    if (len<24) { // Mais barato não criar task se o número for muito pequeno
        quicksort(arr, i);
        quicksort(arr+i, len-i);
    } else {
        #pragma omp task
        {
            quicksort(arr, i);
        }
        #pragma omp task
        {
            quicksort(arr+i, len-i);
        }
    }
}

int main(void) {
    srand(time(NULL));
    const size_t n = 1000000000L;
    size_t i;
    // Build array with random values
    int *arr = (int*)malloc(n*sizeof(int));
    for (i=0; i<n; i++) {
        arr[i] = rand();
    }
    // Sort!
    double timeStart = omp_get_wtime();
    #pragma omp parallel
    {
	#pragma omp single
        {
            quicksort(arr, n);
        }
    }
    double timeEnd = omp_get_wtime();
    //printf("Sort took %.6lf seconds\n", timeEnd - timeStart);
    printf("%.6lf\n", timeEnd - timeStart);
    // Print sorted array
    for (i=0; i<n; i++) {
        if (i>0 && arr[i-1]>arr[i]) printf("Errrrou!");
        //printf("%d ", arr[i]);
    }
    // Destroy array
    free(arr);
    // The end
    return 0;
}
