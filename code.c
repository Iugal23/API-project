#include <stdio.h>
#include <stdlib.h>

struct nodo{
    int el;
    struct nodo* next;
    struct nodo* prev;
};
struct queue{
    struct nodo* head;
    struct nodo* tail;
};
struct queue* enqueue(struct queue* Q,int new);
int dequeue(struct queue* Q);

int main(){
    struct queue* Q=malloc(sizeof(struct queue));
    printf("%d\n",dequeue(Q));
    Q=enqueue(Q,10);
    printf("%d ",dequeue(Q));
    Q=enqueue(Q,20);
    printf("%d ",dequeue(Q));
    Q=enqueue(Q,11);
    
    printf("%d ",dequeue(Q));
    printf("\n");
    free(Q);
}

struct queue* enqueue(struct queue* Q,int new){
    struct nodo* n=malloc(sizeof(struct nodo));
    n->el=new;
    n->next=NULL;
    if(Q->tail==NULL){
        Q->tail=n;
        Q->head=n;
        return Q;
    }
    else{
        Q->head->prev=n;
        n->next=Q->head;
        Q->head=n;
        return Q;
    }
}
int dequeue(struct queue* Q){
    int r;
    struct nodo* temp;
    if(Q->tail!=NULL){
        r=Q->tail->el;
        temp=Q->tail;
        if(Q->tail->prev!=NULL){
            Q->tail=Q->tail->prev;
        }
        else{
            Q->tail=NULL;
        }
        free(temp);
        return r;
    }
    else{
        return -1;
    }
    
    
}