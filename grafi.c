#include <stdlib.h>
#include <stdio.h>
struct stazione{
    int x;
    int y;
    struct stazione *next;
    struct grafo *graph;
};
typedef struct stazione* autostrada;

struct grafo{
    struct stazione *nodo;
    struct grafo *adj;
};


int main(){
    autostrada A=malloc(sizeof(struct stazione)),B=malloc(sizeof(struct stazione)),C=malloc(sizeof(struct stazione));
    A->x=10;
    A->y=25;
    A->graph=malloc(sizeof(struct grafo));
    B->x=30;
    B->y=15;
    B->graph=malloc(sizeof(struct grafo));
    A->next=B;
    C->x=50;
    C->y=30;
    C->graph=malloc(sizeof(struct grafo));
    B->next=C;
    A->graph->nodo=B;
    A->graph->adj->nodo=C;
    printf("%d %d\n",A->graph->nodo->x,A->graph->adj->nodo->x);
    
    return 0;
}
