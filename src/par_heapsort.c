#include <stdio.h>
#include <stdlib.h>
#include "utils.c"
#include <omp.h>
#include <pthread.h>
#include <math.h>
#include <string.h>

void heap_sort(int);
void shiftDown(int a[], int);

static int *a;
static int size;
static int end;
static int N_threads;
static int level_count;
static pthread_mutex_t *level_locks; 
static pthread_rwlock_t end_lock;
static pthread_mutex_t tree_lock;

void *aux_parallel_tree(void *id){
    while(1){
        pthread_mutex_lock(&tree_lock);
        if(end > 0){
            int cmax = a[0];
            a[0]=a[end];
            a[end]=cmax;
            end--;
            shiftDown_Seq(a,0,end);
            pthread_mutex_unlock(&tree_lock);
        }else{
            pthread_mutex_unlock(&tree_lock);
            break;
        }
    }
    return NULL;
}

void *aux_parallel_level(void *id){
    int max;
    pthread_mutex_lock(level_locks);
    pthread_rwlock_wrlock(&end_lock);
    while(end > 0){
        max = a[0];
        a[0] = a[end];
        a[end] = max;
        end--;
        pthread_rwlock_unlock(&end_lock);        
        shiftDown(a,0);
        pthread_mutex_lock(level_locks);
        pthread_rwlock_wrlock(&end_lock);
    }
    pthread_mutex_unlock(level_locks);
    pthread_rwlock_unlock(&end_lock);
    return NULL;
}

void shiftDown(int a[], int start){
    int cur_level = 0;
    int root = start;
    int child = LEFT(root);
    int swap;
    int tmp;

    pthread_mutex_lock(level_locks+cur_level+1);
    pthread_rwlock_rdlock(&end_lock);
    
    while(child <= end) {
        swap = root;
        
        if(a[swap] < a[child]) 
            swap = child;
        if((child+1) <= end)
            if (a[swap] < a[child+1]) swap = child+1;
        if(swap == root) 
            root = end;
        else {
            tmp = a[swap];
            a[swap] = a[root];
            a[root] = tmp;
            root = swap;
        }
        child = LEFT(root);
        tmp = (child < end);

        pthread_mutex_unlock(level_locks+cur_level);
        pthread_rwlock_unlock(&end_lock);

        cur_level ++;
        if(tmp)
            pthread_mutex_lock(level_locks+cur_level+1);
        pthread_rwlock_rdlock(&end_lock);
    }

    pthread_mutex_unlock(level_locks+cur_level);
    if(tmp)
        pthread_mutex_unlock(level_locks+cur_level+1);
    pthread_rwlock_unlock(&end_lock);
}


void heap_sort(int granularity) {
    void *(*callback)(void*);
    level_count = ceil(log(size) / log(2));
    pthread_t* thread_handles = (pthread_t*)malloc(N_threads*sizeof(pthread_t));

    heapify(a,size);
    
    switch(granularity){
        case 1:         //tree granularity
            pthread_mutex_init(&tree_lock, NULL);
            callback = aux_parallel_tree;
            break;
        case 2:         //level granularity
            pthread_rwlock_init(&end_lock, NULL);
            level_locks = (pthread_mutex_t*)malloc(level_count * sizeof(pthread_mutex_t));
            for(int i=0; i < level_count; i ++)
                pthread_mutex_init(level_locks+i, NULL);
            
            callback = aux_parallel_level;
            break;
        default:
            free(thread_handles);
            return;
    }

    end = size - 1;

    for(long i=0; i<N_threads; i++)
        pthread_create(&thread_handles[i], NULL, callback, (void *)i);

    for(long i=0; i<N_threads; i++)
        pthread_join(thread_handles[i], NULL);

    switch(granularity){
        case 1:         //tree granularity
            pthread_mutex_destroy(&tree_lock);
            break;
        case 2:         //level granularity
            pthread_rwlock_destroy(&end_lock);
            for(int i=0; i < level_count; i ++)
                pthread_mutex_destroy(level_locks+i);
            free(level_locks);
            break;
    }

    free(thread_handles);
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

        heap_sort(atoi(argv[3]));

        end = omp_get_wtime();

        printf("Time: %f\n", end - start);
        if(argc >= 5)
            if(!strcmp(argv[4], "-d"))
                pprint_array(a, size);
        if(is_sorted(a, size))
            printf("\nSorted!\n");
        else
            printf("\nSomething went wrong!\n");
        free(a);
    }else{
        printf("USAGE: %s size threads granularity_level [-d]\n", argv[0]);
    }
    return 0;
}
