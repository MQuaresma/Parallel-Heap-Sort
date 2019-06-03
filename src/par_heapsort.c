#include <stdio.h>
#include <stdlib.h>
#include "utils.c"
#include <omp.h>
#include <pthread.h>
#include <math.h>
#include <string.h>

void heap_sort();
void heapify(int a[], int);
void shiftDown(int a[], int, int);
void shiftDown_seq(int a[], int start, int end);

static int *a;
static int size;
static int end;
static int N_threads;
static int level_count;
static pthread_mutex_t *level_mutexes; 
static pthread_mutex_t end_mut;

void *aux_parallel_level(void *id){
    int max;
    pthread_mutex_lock(&end_mut);

    while(end > 0){
        pthread_mutex_lock(level_mutexes);
        pthread_mutex_lock(level_mutexes+level_count);
        max = a[0];
        a[0] = a[end];
        a[end] = max;
        pthread_mutex_unlock(level_mutexes);
        pthread_mutex_unlock(level_mutexes+level_count);
        end--;
        shiftDown(a,0,end);
        pthread_mutex_lock(&end_mut);
    }

    pthread_mutex_unlock(&end_mut);
    return NULL;
}

void heap_sort() {
    //level_count = log(size) / log(2);
    level_count = 4;
    pthread_t* thread_handles = (pthread_t*)malloc(N_threads*sizeof(pthread_t));

    heapify(a,size); 
    level_mutexes = (pthread_mutex_t*)malloc(level_count * sizeof(pthread_mutex_t));
    pthread_mutex_init(&end_mut, NULL);
    end = size - 1;

    for(int i=0; i < level_count; i ++)
        pthread_mutex_init(level_mutexes+i, NULL);

    for(long i=0; i<N_threads; i++)
        pthread_create(&thread_handles[i], NULL, aux_parallel_level, (void *)i);

    for(long i=0; i<N_threads; i++)
        pthread_join(thread_handles[i], NULL);

    pthread_mutex_destroy(&end_mut);
    for(int i=0; i < level_count; i ++)
        pthread_mutex_destroy(level_mutexes+i);

    free(level_mutexes);
    free(thread_handles);
}

void shiftDown_seq(int a[], int start, int end) {
  int root = start;
  
  while( (2*root+1) <= end) {
    int child = 2*root+1;
    int swap = root;
    
    if (a[swap]<a[child]) swap = child;
    if ((child+1) <= end)
      if (a[swap]<a[child+1]) swap = child+1;
    if(swap==root) root=end;
    else {
      int tmp = a[swap];
      a[swap]=a[root];
      a[root]=tmp;
      root = swap;
    }
  }
}



void shiftDown(int a[], int start, int end_a) {
    pthread_mutex_unlock(&end_mut);
    int root = start;
    int child;
    int swap;
    int tmp;
    int cur_level = 0;
  
    while( (2*root+1) <= end_a) {
        child = LEFT(root);
        swap = root;
        pthread_mutex_lock(level_mutexes+cur_level);
        pthread_mutex_lock(level_mutexes+cur_level+1);

        if (a[swap]<a[child]) 
            swap = child;
        if ((child+1) <= end_a)
            if (a[swap]<a[child+1]) swap = child+1;
        if(swap==root) 
            root = end_a;
        else {
            tmp = a[swap];
            a[swap] = a[root];
            a[root] = tmp;
            root = swap;
        }
        pthread_mutex_unlock(level_mutexes+cur_level);
        pthread_mutex_unlock(level_mutexes+cur_level+1);
        cur_level ++;
    }
}

void heapify(int a[], int count) {
  int start=(count-1)/2;

  while(start>=0) {
    shiftDown_seq(a,start,count-1);
    start--;
  }
}



int main(int argc, char *argv[]){
    if(argc >= 4){
        size = atoi(argv[1]);
        N_threads = atoi(argv[2]);
        a = (int *)calloc(size, sizeof(int));
        double start, end;

        for(int i=0; i<size; i++)
            a[i]=rand();

        start = omp_get_wtime();

        heap_sort();

        end = omp_get_wtime();

        printf("Time: %f\n", end - start);
        if(argc >= 5)
            if(!strcmp(argv[4], "-d"))
                pprint_array(a, size);
            if(is_sorted(a, size))
                printf("\nSorted!\n");
            else
                printf("\nSomething went wrong!\n");
    }else{
        printf("USAGE: %s size threads exclusionZones [-d]\n", argv[0]);
    }
    return 0;
}
