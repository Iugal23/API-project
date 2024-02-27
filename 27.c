#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    if(i<(length-1)/2){
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
    
};
typedef struct stazione *autostrada;

//QUEUE
struct nodo{
    struct grafo* el;
    struct nodo* next;
    struct nodo* prev;
};
struct queue{
    struct nodo* head;
    struct nodo* tail;
};


struct queue* enqueue(struct queue* Q, struct grafo* new);
struct grafo* dequeue(struct queue* Q);

struct queue* enqueue(struct queue* Q,struct grafo* new){
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
struct grafo* dequeue(struct queue* Q){
    struct grafo* r;
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

struct grafo{
    int km;
    int max_car;
    int dist;
    char col;
    struct grafo* next;
    struct grafo *prev_stop; //puntatore alla tappa precedente del percorso

};
autostrada aggiungi_stazione(autostrada A,int dist,int n, int* bat);
void inserisci_adiacente(autostrada A, autostrada new);
autostrada rimuovi_stazione(autostrada A,int km_del);
void inserisci_auto(autostrada A,int km_staz,int car);
void rimuovi_auto(autostrada A,int km_staz,int car);
void calcolo_percorso_1(autostrada A, int part, int dest);
void calcolo_percorso_2(autostrada A, int part, int dest);
void stampa_percorso(struct grafo* stop, int part);

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
            A=rimuovi_stazione(A,dist);
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
            if(dest>part){
                calcolo_percorso_1(A,part,dest);
            }
            else if(dest<part){
                calcolo_percorso_2(A,part,dest);
            }
            else{
                printf("%d\n",dest);
            }
        }
    }while(x!=EOF);
    free(A);
 
    return 0;

}

autostrada aggiungi_stazione(autostrada A,int dist,int n, int* bat ){
    autostrada curr=A,prec=NULL, new=malloc(sizeof(struct stazione));
    new->km=dist;
    new->car_num=n;
    new->cars=malloc(n*sizeof(int));
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
autostrada rimuovi_stazione(autostrada A , int km_del){
    autostrada curr=A,prec=NULL;
    while(curr!=NULL && curr->km!=km_del){
        prec=curr;
        curr=curr->next;
        if(curr==NULL || curr->km>km_del){
            printf("non demolita\n");
            return A;

        }
    }
    if(curr!=NULL){
        if(curr==A){
            A=A->next;
        }
        else{
            prec->next=curr->next;
        }
        free(curr->cars);
        free(curr);
        printf("demolita\n");
    }
    else{
        printf("non demolita\n");

    }
    return A;
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
    int* temp;
    autostrada curr=A;
    while(curr!=NULL){
        if(curr->km==km_staz){
            for(int i=0;i<curr->car_num;i++){
                if(curr->cars[i]==car){
                    curr->car_num--;
                    curr->cars[i]=curr->cars[curr->car_num];
                    temp=realloc(curr->cars,curr->car_num*sizeof(int));
                    if(temp!=NULL){
                        curr->cars=temp;
                    }
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

void calcolo_percorso_1(autostrada A, int part, int dest){
    // creazione grafo
    autostrada curr1=A ;
    struct grafo *G=malloc(sizeof(struct grafo)), *p=NULL,*p2,*end=NULL, *start=NULL;
    struct queue*  Q=malloc(sizeof(struct queue));
    Q->tail=NULL; Q->head=NULL;

    while(curr1!=NULL && curr1->km<part){
        curr1=curr1->next;
    }
    p=G;
    while(curr1!=NULL && curr1->km<=dest){
        p2=malloc(sizeof(struct grafo));
        p2->km=curr1->km;
        p2->max_car=curr1->cars[0];
        p2->dist=0;
        if(p2->km==part){
            start=p2;
            p2->col='g';
            Q=enqueue(Q,p2);
        }
        else{
            p2->col='w';
        }
        if(p2->km==dest){
            end=p2;
        }
        p->next=p2;
        p=p->next;
        curr1=curr1->next;
    }
    if(end==NULL || start==NULL){
        printf("nessun percorso\n");
        return;
    }
        
    while(Q->tail!=NULL){
        p=dequeue(Q);
        p2=p->next; 
        while(p2!=NULL){
            if(p->km+p->max_car>=p2->km){
                if(p2->col=='w'){
                    p2->col='g';
                    p2->dist=p2->dist+1;
                    p2->prev_stop=p;
                    Q=enqueue(Q,p2);
                    if(p2->km==dest){
                        stampa_percorso(p2,part);
                        printf("\n");
                        free(Q);
                        return;
                    }
                }
                p2=p2->next;
                
            }
            else{
                break;
            }

        }
        
    }
    free(Q);

    
    printf("nessun percorso\n");
}

void calcolo_percorso_2(autostrada A, int part, int dest){
    // creazione grafo
    autostrada curr1=A ;
    struct grafo *G=malloc(sizeof(struct grafo)), *p=NULL,*p2,*end=NULL, *start=NULL,*last_stop=NULL;
    struct queue*  Q=malloc(sizeof(struct queue));
    Q->tail=NULL; Q->head=NULL;

    while(curr1!=NULL && curr1->km<dest){
        curr1=curr1->next;
    }
    p=G;
    while(curr1!=NULL && curr1->km<=part){
        p2=malloc(sizeof(struct grafo));
        p2->km=curr1->km;
        p2->max_car=curr1->cars[0];
        p2->dist=0;
        if(p2->km==part){
            start=p2;
            p2->col='g';
            Q=enqueue(Q,p2);
        }
        else{
            p2->col='w';
        }
        if(p2->km==dest){
            end=p2;
        }
        p->next=p2;
        p2->next=NULL;
        p=p->next;
        curr1=curr1->next;
    }
    if(end==NULL || start==NULL){
        printf("nessun percorso\n");
        return;
    }
        
    while(Q->tail!=NULL){
        p=dequeue(Q);
        p2=end; 
        while(p2!=NULL && p2->km<p->km){
            if(p->km-p->max_car<=p2->km){
                if(p2->col=='w'){
                    p2->col='g';
                    p2->dist=p->dist+1;
                    p2->prev_stop=p;
                    Q=enqueue(Q,p2);
                    if(p2->km==dest){
                        last_stop=p2;
                    }
                }
                else if(p2->col=='g'){
                    if(p->dist+1<=p2->dist && p->km<p2->prev_stop->km){
                        p2->dist=p->dist+1;
                        p2->prev_stop=p;
                    }
                }
    
            }
            p2=p2->next;
        } 
    }
    free(Q);
    if(last_stop!=NULL){
        stampa_percorso(last_stop,part);
        printf("\n");
        free(G);
        return;
    }
    free(G); 
    printf("nessun percorso\n");
}

void stampa_percorso(struct grafo *stop, int part){
    if(stop->km!=part){
        stampa_percorso(stop->prev_stop,part);
        printf(" %d",stop->km);
    }
    else{
        printf("%d",stop->km);
    }
}

