#include <stdlib.h>
#include <stdio.h>
void build_max_heap(int a[],int length);
void max_heapify(int a[],int i, int length);

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
    int arr[10]={10,9,8,7,6,5,4,3,2,1};
    build_max_heap(arr,10);
    for(int i=0;i<9;i++){
        printf("%d,",arr[i]);
    }
    printf("%d\n",arr[9]);
    return 0;
}