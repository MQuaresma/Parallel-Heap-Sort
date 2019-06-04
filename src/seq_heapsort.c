#include <stdio.h>
#include <stdlib.h>
#include "utils.c"
#include <omp.h>

void heap_sort(int a[], int count) {
  heapify(a,count);

  int end=count-1;

  while ( end>0 ) {
    int cmax = a[0];
    a[0]=a[end];
    a[end]=cmax;
    end--;
    shiftDown_Seq(a,0,end);
  }
}

int main(int argc, char *argv[]){
    if(argc == 2){
        int size = atoi(argv[1]);
        int a[size];
        double start, end;

        for(int i=0; i<size; i++)
            a[i]=rand();

        start = omp_get_wtime();

        heap_sort(a,size);
        
        end = omp_get_wtime();

        printf("Time: %f\n", end - start);
    }else{
        printf("USAGE: ./seq_heap_sort size\n");
    }
    return 0;
}
