void heapsort(int a[], int);
void heapify(int a[], int);
void shiftDown(int a[], int, int);


//--------- skeleton code for parallel version with locks
void heapsort(int a[], int count) {
  heapify(a,count); // build max-heap (sequential)

  int end=count-1;

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
  return 0;
}
