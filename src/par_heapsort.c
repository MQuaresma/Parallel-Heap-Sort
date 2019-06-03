#include <stdio.h>
#include <stdlib.h>
#include "utils.c"
#include <omp.h>
#include <pthread.h>

void heap_sort();
void heapify(int a[], int);
void shiftDown(int a[], int, int);

static int *a;
static int size;
static int end;
static int N_threads;
static pthread_mutex_t lock;

void *aux_parallel_tree(void *id){

  while ( 1 ) { // do in parallel
    pthread_mutex_lock(&lock);
    if (end > 0){
        // do in sequential order
        int cmax = a[0];
        a[0]=a[end];
        a[end]=cmax; //swap
        end--; // decrease heap size
        // repair heap : do with locking of parent and child
        shiftDown(a,0,end);
        pthread_mutex_unlock(&lock);
    }else{
        pthread_mutex_unlock(&lock);
        break;
    }
  }
}

//--------- skeleton code for parallel version with locks
void heap_sort(int v_lock) {
  heapify(a,size); // build max-heap (sequential)

  end=size-1;

  pthread_mutex_init(&lock, NULL);
  pthread_t* thread_handles = (pthread_t*)malloc(N_threads*sizeof(pthread_t));

  for(long i=0; i<N_threads; i++){
    pthread_create(&thread_handles[i],NULL,aux_parallel_tree, (void *)i);
  }

  for(long i=0; i<N_threads; i++)
        pthread_join(thread_handles[i],NULL);

  free(thread_handles);
  pthread_mutex_destroy(&lock);
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
    int child = LEFT(root);
    int swap = root;
    
    if (a[swap]<a[child]) swap = child;
    if ((child+1) <= end)
      if (a[swap]<a[child+1]) swap = RIGHT(root);
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

        heap_sort(atoi(argv[3]));

        end = omp_get_wtime();

        free(a);
        printf("Time: %f\n", end - start);
    }else{
        printf("USAGE: %s size threads exclusionZones\n", argv[0]);
    }
    return 0;
}
