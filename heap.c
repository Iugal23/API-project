#include <stdlib.h>
#include <stdio.h>
void build_max_heap(int a[],int length);
void max_heapify(int a[],int i, int length);
void heap_insert_fix(int *a,int i);
void heap_delete_fix(int*a,int i,int length);
void max_heapify(int a[],int i, int length){
    int l=2*i+1,r=2*i+2,max,temp;

    if(l<length && a[l]>a[i]){
        max=l;
    }
    else{
        max=i;
    }
    if(r<length && a[r]>a[max]){
        max=r;
    }
    if(max!=i){
        temp=a[i];
        a[i]=a[max];
        a[max]=temp;
        max_heapify(a,max,length);
    }
}
void build_max_heap(int a[], int length){
    for(int i=length/2;i>=0;i--){
        max_heapify(a,i,length);
    }
}

int main(){
    int *a;
    a=calloc(10,sizeof(int));
    for(int i=0;i<10;i++){
        a[i]=i+1;
    }
    build_max_heap(a,10);
    a=realloc(a,11*sizeof(int));
    a[10]=13;
    heap_insert_fix(a,10);
    for(int i=0;i<11;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
    //heap_delete_fix(a,5,9);

    return 0;
}

void heap_insert_fix(int *a,int i){
    int temp;
    if(a[(i-1)/2]<a[i]){
        temp=a[i];
        a[i]=a[(i-1)/2];
        a[(i-1)/2]=temp;
        heap_insert_fix(a,(i-1)/2);
    }
    
}
void heap_delete_fix(int *a,int i,int length){
    int temp;
    if(i<length/2){
        if(a[2*i+1]>a[i]){
            temp=a[i];
            a[i]=a[2*i+1];
            a[2*i+1]=temp;
            heap_delete_fix(a,2*i+1,length);
        }
        if(a[2*i+2]>a[i]){
            temp=a[i];
            a[i]=a[2*i+2];
            a[2*i+2]=temp;
            heap_delete_fix(a,2*i+2,length);
        }
    }
}