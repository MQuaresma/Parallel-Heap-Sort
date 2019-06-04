#include<stdio.h>
#define LEFT(i) 2*i+1
#define RIGHT(i) LEFT(i)+1

int is_sorted(int l[], int n){
    int i;

    for(i = 0; (i < n-1) && (l[i] <= l[i+1]); i ++);

    return (i == n-1); 
}


void pprint_array(int l[], int n){
    for(int i=0; i<n; i++){
        printf("%d\t", l[i]);
        if(!((i+1) % 5)) printf("\n");
    }
}

void shiftDown_Seq(int a[], int start, int end) {
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

void heapify(int a[], int count) {
  int start=(count-1)/2;

  while(start>=0) {
    shiftDown_Seq(a,start,count-1);
    start--;
  }
}
