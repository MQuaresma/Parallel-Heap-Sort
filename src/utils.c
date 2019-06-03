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
