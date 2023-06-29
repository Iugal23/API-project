#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int input(char s[]);
//HEAP
void build_max_heap(int a[],int length);
void max_heapify(int a[],int i, int length);
void heap_insert_fix(int *a,int i);
void heap_delete_fix(int *a,int i,int length);

int input(char s[]){
    int i=0;
    char c;
    strcpy(s,"                    ");
    do{
        c=getchar();
        s[i]=c;
        i++;
    }while(c!=' ' && c!='\n' && c!=EOF);
    if(c==' ' || c=='\n'){
        return i-1;
    }
    else{
        return EOF;
    }
    
}
void max_heapify(int a[],int i, int length){
    int l=2*i+1,r=2*i+2,max;

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
        int temp=a[i];
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

struct stazione{
    int km;
    int car_num;
    int *cars;
    struct stazione *next; // puntatore alla prossima stazione della autostrada
    int dist;
    char col;
    int adj_num;
    struct stazione **graph; // array con le stazioni adiacenti
    struct stazione *prev_stop; //puntatore alla tappa precedente del percorso
};
typedef struct stazione *autostrada;

//QUEUE
struct nodo{
    autostrada el;
    struct nodo* next;
    struct nodo* prev;
};
struct queue{
    struct nodo* head;
    struct nodo* tail;
};
struct queue* enqueue(struct queue* Q,autostrada new);
autostrada dequeue(struct queue* Q);

struct queue* enqueue(struct queue* Q,autostrada new){
    struct nodo* n=malloc(sizeof(struct nodo));
    n->el=new;
    n->next=NULL;
    n->prev=NULL;
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
autostrada dequeue(struct queue* Q){
    autostrada r;
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
        return NULL;
    }
}

autostrada aggiungi_stazione(autostrada A,int dist,int n, int* bat);
void inserisci_adiacente(autostrada A,autostrada nodo);
void rimuovi_stazione(autostrada A,int km_del);
void inserisci_auto(autostrada A,int km_staz,int car);
void rimuovi_auto(autostrada A,int km_staz,int car);
void calcolo_percorso(autostrada A, int part, int dest);
void stampa_percorso(autostrada stop, int part);

int main(){ 
    autostrada A=NULL;
    int dist,auto_num,*batteries, battery,part,dest,x=0;
    char command[21];
    do{    
        x=input(command);
        if(command[0]=='a'){
            if(command[9]=='s'){
                x=input(command);
                dist=atoi(command);
                x=input(command);
                auto_num=atoi(command);
                batteries=malloc(auto_num*sizeof(int));
                for(int i=0;i<auto_num;i++){
                    x=input(command);
                    batteries[i]=atoi(command);
                }
                A=aggiungi_stazione(A,dist,auto_num,batteries);
                free(batteries);
            }
            else{
                x=input(command);
                dist=atoi(command);
                x=input(command);
                battery=atoi(command);
                inserisci_auto(A,dist,battery);
            }

        }
        else if(command[0]=='d'){
            x=input(command);
            dist=atoi(command);
            rimuovi_stazione(A,dist);
        }
        else if(command[0]=='r'){
            x=input(command);
            dist=atoi(command);
            x=input(command);
            battery=atoi(command);
            rimuovi_auto(A,dist,battery);
        }
        else if(command[0]=='p'){
            x=input(command);
            part=atoi(command);
            x=input(command);
            dest=atoi(command);
            calcolo_percorso(A,part,dest);
        }
    }while(x!=EOF);
 
    free(A);
    return 0;

}

autostrada aggiungi_stazione(autostrada A,int dist,int n, int* bat ){
    autostrada curr=A,prec=NULL, new=malloc(sizeof(struct stazione));
    new->km=dist;
    new->car_num=n;
    new->cars=calloc(n,sizeof(int));
    new->adj_num=0;
    new->graph=NULL;
    for(int i=0;i<n;i++){
        new->cars[i]=bat[i];
    }
    build_max_heap(new->cars, new->car_num); // uso un heap in modo tale che il primo elemento sia sempre il max
    
    if(curr!=NULL){
        while(curr!=NULL && curr->km<new->km){
        prec=curr;
        curr=curr->next;
        }
        if(curr==NULL || curr->km!= new->km){    
            new->next=curr;
            if(prec!=NULL){  // new NON è la nuova testa della list
                prec->next=new;
            }
            else{
                A=new;
            }
            printf("aggiunta\n");
        
        }
        else{
            printf("non aggiunta\n");
        }

    }
    else{
        A=new;
        new->next=NULL;
        printf("aggiunta\n");
    }
    return A;


}
void rimuovi_stazione(autostrada A , int km_del){
    autostrada curr=A,prec=NULL;
    while(curr!=NULL && curr->km!=km_del){
        prec=curr;
        curr=curr->next;
        if(curr==NULL || curr->km>km_del){
            printf("non demolita\n");
            return;

        }
    }
    if(curr!=NULL){
        prec->next=curr->next;
        free(curr);
        printf("demolita\n");
        
    }
    else{
        printf("non demolita\n");
    }
}
void inserisci_adiacente(autostrada A, autostrada new){
    A->adj_num++;
    if(A->adj_num>1){
        A->graph=realloc(A->graph,A->adj_num*sizeof(struct stazione));
        A->graph[A->adj_num-1]=new;
    }
    else{
        A->graph=malloc(sizeof(struct stazione));
        A->graph[0]=new;
    }
}
void inserisci_auto(autostrada A,int km_staz,int car){
    autostrada curr=A;
    while(curr!=NULL){
        if(curr->km==km_staz){
            curr->car_num++;
            curr->cars=realloc(curr->cars,curr->car_num*sizeof(int));
            curr->cars[curr->car_num-1]=car;
            heap_insert_fix(curr->cars,curr->car_num-1);
            printf("aggiunta\n");
            return;
        }
        curr=curr->next;
    }
    printf("non aggiunta\n");
    return;
}
void rimuovi_auto(autostrada A,int km_staz,int car){
    autostrada curr=A;
    while(curr!=NULL){
        if(curr->km==km_staz){
            for(int i=0;i<curr->car_num;i++){
                if(curr->cars[i]==car){
                    curr->car_num--;
                    curr->cars[i]=curr->cars[curr->car_num];
                    curr->cars=realloc(curr->cars,curr->car_num*sizeof(int));
                    heap_delete_fix(curr->cars,i,curr->car_num);
                    printf("rottamata\n");
                    return;
                }
            }
            printf("non rottamata\n");
            return;  
        }
        curr=curr->next;
    }
    printf("non rottamata\n");
    return;
}

/*  INSERIMENTO ADIACENTI
while(curr1!=NULL){
                if(curr1->km<curr2->km){
                    if(curr1->km+curr->cars[0]>=curr2->km){
                        inserisci_adiacente(curr1, curr2);
                    }
                    if(curr2->km-curr2->cars[0]<=curr1->km){
                        inserisci_adiacente(curr2,curr);
                    }
                }
                if(curr1->km>curr2->km){
                    if(curr1->km-curr->cars[0]<= curr2->km){
                        inserisci_adiacente(curr1,curr2);
                    }
                    if(curr2->km+curr2->cars[0]>=curr1->km){
                        inserisci_adiacente(curr2,curr1);
                    }
                }
                curr1=curr1->next;
            }
*/

void calcolo_percorso(autostrada A, int part, int dest){
    // creazione grafo;
    autostrada curr1=A, curr2;
    struct queue*  Q=malloc(sizeof(struct queue));
    Q->tail=NULL; Q->head=NULL;

    while(curr1!=NULL){
        curr1->adj_num=0;
        curr1->graph=NULL;
        curr1->dist=0;
        if(curr1->km!=part){
            curr1->col='w';
        }
        else{
            curr1->col='g';
            Q=enqueue(Q,curr1);
        }
        curr1=curr1->next;
    }
    curr1=A;
    while(curr1!=NULL){
        if((part<=dest && curr1->km>=part) || (part>=dest && curr1->km<=part)){
            curr2=curr1->next;
            while(curr2!=NULL){
                if((part<=dest && curr2->km<=dest) || (part>=dest && curr2->km>=dest)){
                    if(curr1->km<curr2->km){
                        if(curr1->km+curr1->cars[0]>=curr2->km){
                            inserisci_adiacente(curr1,curr2);
                        }
                        if(curr2->km-curr2->cars[0]<=curr1->km){
                            inserisci_adiacente(curr2,curr1);
                        }
                    }
                    else if(curr1->km>curr2->km){
                            if(curr1->km-curr1->cars[0]<= curr2->km){
                                inserisci_adiacente(curr1,curr2);
                            }
                            if(curr2->km+curr2->cars[0]>=curr1->km){
                                inserisci_adiacente(curr2,curr1);
                            }
                        }
                }
                curr2=curr2->next;
            }
        }
        curr1=curr1->next;
    }
    while(Q->tail!=NULL){
        curr1=dequeue(Q);
        for(int i=0;i<curr1->adj_num;i++){
            if(curr1->graph[i]->col=='w'){
                curr1->graph[i]->col='g';
                curr1->graph[i]->dist=curr1->dist+1;
                curr1->graph[i]->prev_stop=curr1;
                Q=enqueue(Q,curr1->graph[i]);
                if(curr1->graph[i]->km==dest){
                    stampa_percorso(curr1->graph[i],part);
                    printf("\n");
                    free(Q);
                    return;
                }
            }
        }
    }
    free(Q);
    printf("nessun percorso\n");
}

void stampa_percorso(autostrada stop, int part){
    if(stop->km!=part){
        stampa_percorso(stop->prev_stop,part);
        printf(" %d",stop->km);
    }
    else{
        printf("%d",stop->km);
    }
}

/*
percorsi sbagliati
9
15
17
21
24
*/