#include <stdio.h>
#include <stdlib.h>
#include "utils.c"
#include <omp.h>
#include <pthread.h>

void heapsort();
void heapify(int a[], int);
void shiftDown(int a[], int, int);

static int *a;
static int size;
static int end;
static int N_threads;

void *aux_parallel(void *id){
  while ( end>0 ) { // do in parallel
    // do in sequential order
    int cmax = a[0];
    a[0]=a[end];
    a[end]=cmax; //swap
    end--; // decrease heap size
    // repair heap : do with locking of parent and child
    shiftDown(a,0,end);
  }
}

//--------- skeleton code for parallel version with locks
void heapsort() {
  heapify(a,size); // build max-heap (sequential)

  end=size-1;

  pthread_t* thread_handles = (pthread_t*)malloc(N_threads*sizeof(pthread_t));

  for(long i=0; i<N_threads; i++)
        pthread_create(&thread_handles[i],NULL,aux_parallel, (void *)i);

  for(long i=0; i<N_threads; i++)
        pthread_join(thread_handles[i],NULL);

  free(thread_handles);
}

void heapify(int a[], int count) {
  int start=(count-1)/2;

  while(start>=0) {
    shiftDown(a,start,count-1);
    start--;
  }
}

void shiftDown(int a[], int start, int end) {
  int root = start;
  
  while( (2*root+1) <= end) {
    int child = 2*root+1;
    int swap = root;
    
    if (a[swap]<a[child]) swap = child;
    if ((child+1) <= end)
      if (a[swap]<a[child+1]) swap = child+1;
    if(swap==root) root=end; // return
    else {
      int tmp = a[swap];
      
      a[swap]=a[root];
      a[root]=tmp;
      root = swap;
    }
  }
}

int main(int argc, char *argv[]){
    if(argc == 4){
        size = atoi(argv[1]);
        N_threads = atoi(argv[2]);
        a = (int *)calloc(size, sizeof(int));
        double start, end;

        for(int i=0; i<size; i++)
            a[i]=rand();

        start = omp_get_wtime();

        heapsort();

        end = omp_get_wtime();

        printf("Time: %f\n", end - start);
    }else{
        printf("USAGE: ./par_heapsort size threads exclusionZones\n");
    }
    return 0;
}
