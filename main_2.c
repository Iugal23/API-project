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
};

// TREE
struct BSTnode
{
    struct stazione* stazione;
    struct BSTnode *right;
    struct BSTnode *left;
    struct BSTnode *parent;
    
};
typedef struct BSTnode *autostrada;

autostrada tree_search(autostrada T, int km){
    autostrada temp=T;
    while(temp!=NULL && temp->stazione->km!=km){
        if(temp->stazione->km<km){
            temp=temp->right;
        }
        else{
            temp=temp->left;
        }
    }
    return temp;
}
autostrada tree_successor(autostrada T){
    autostrada curr,r;
    if(T->right!=NULL){
        curr=T->right;
        while(curr->left!=NULL){
            curr=curr->left;
        }
        return curr;
    }
    r=T->parent;
    curr=T;
    while(r!=NULL && curr==r->right){
        curr=r;
        r=r->parent;
    }
    return r;
}
autostrada tree_predecessor(autostrada T){
    autostrada curr=T,r;
    if(T->left!=NULL){
        curr=T->left;
        while(curr->right!=NULL){
            curr=curr->right;
        }
        return curr;
    }
    r=T->parent;
    curr=T;
    while(r!=NULL && curr==r->left){
        curr=r;
        r=r->parent;
    }
    return r;
}

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
    autostrada new=malloc(sizeof(struct BSTnode)),curr=A,prev=NULL;
    struct stazione *staz=malloc(sizeof(struct stazione));
    staz->km=dist;
    staz->cars=malloc(n*sizeof(int));
    staz->car_num=n;
    for(int i=0;i<n;i++){
        staz->cars[i]=bat[i];
    }
    build_max_heap(staz->cars, staz->car_num); // uso un heap in modo tale che il primo elemento sia sempre il max
    new->stazione=staz;
    new->left=NULL;  
    new->right=NULL;

    while(curr!=NULL){
        prev=curr;
        if(curr->stazione->km==new->stazione->km){
            printf("non aggiunta\n");
            return A;
        }
        if(curr->stazione->km>new->stazione->km){
            curr=curr->left;
        }
        else{
            curr=curr->right;
        }
    }
    new->parent=prev;
    if(prev==NULL){
        A=new;
    }
    else if(new->stazione->km<prev->stazione->km){
        prev->left=new;
    }
    else{
        prev->right=new;
    }
    printf("aggiunta\n");
    return A;
    

}
autostrada rimuovi_stazione(autostrada A , int km_del){
    autostrada temp,del=NULL,p;
    temp=tree_search(A,km_del);
    if(temp!=NULL){
        if (temp->left==NULL || temp->right==NULL){
            del=temp;
        }
        else{
            del=tree_successor(temp);
        }
        if(del->left!=NULL){
            p=del->left;
        }
        else{
            p=del->right;
        }
        if(p!=NULL){
            p->parent=del->parent;
        }
        if(del->parent==NULL){
            A=p;
        }
        else if(del==del->parent->left){
            del->parent->left=p;
        }
        else{
            del->parent->right=p;
        }
        if(del!=temp){
            temp->stazione=del->stazione;
        }
        printf("demolita\n");
    }
    else{
        printf("non demolita\n");
    }
    return A;
}

void inserisci_auto(autostrada A,int km_staz,int car){
    autostrada curr;
    curr=tree_search(A,km_staz);
    if(curr!=NULL){
        curr->stazione->car_num++;
        curr->stazione->cars=realloc(curr->stazione->cars,curr->stazione->car_num*sizeof(int));
        curr->stazione->cars[curr->stazione->car_num-1]=car;
        heap_insert_fix(curr->stazione->cars,curr->stazione->car_num-1);
        printf("aggiunta\n");
    }
    else{
        printf("non aggiunta\n");
    }
}
void rimuovi_auto(autostrada A,int km_staz,int car){
    int* temp;
    autostrada curr=tree_search(A,km_staz);

    if(curr!=NULL){
        for(int i=0;i<curr->stazione->car_num;i++){
            if(curr->stazione->cars[i]==car){
                curr->stazione->car_num--;
                curr->stazione->cars[i]=curr->stazione->cars[curr->stazione->car_num];
                temp=realloc(curr->stazione->cars,curr->stazione->car_num*sizeof(int));
                if(temp!=NULL){
                    curr->stazione->cars=temp;
                }
                heap_delete_fix(curr->stazione->cars,i,curr->stazione->car_num);
                printf("rottamata\n");
                return;
            }
        }
        printf("non rottamata\n");
        
    }
    else{
        printf("non rottamata\n");
    }
}

void calcolo_percorso_1(autostrada A, int part, int dest){
    // creazione grafo
    autostrada curr1=A ;
    struct grafo *G=malloc(sizeof(struct grafo)), *p=NULL,*p2,*end=NULL, *start=NULL;
    struct queue*  Q=malloc(sizeof(struct queue));
    Q->tail=NULL; Q->head=NULL;

    curr1=tree_search(A,part);
    p=G;
    while(curr1!=NULL && curr1->stazione->km<=dest){
        p2=malloc(sizeof(struct grafo));
        p2->km=curr1->stazione->km;
        if(curr1->stazione->car_num!=0){
            p2->max_car=curr1->stazione->cars[0];
        }
        else{
            p2->max_car=0;
        }
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
        curr1=tree_successor(curr1);
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
    autostrada curr1=tree_search(A,part) ;
    struct grafo *G=malloc(sizeof(struct grafo)), *p=NULL,*p2,*end=NULL, *start=NULL,*last_stop=NULL;
    struct queue*  Q=malloc(sizeof(struct queue));
    Q->tail=NULL; Q->head=NULL;
    
    p=G;
    while(curr1!=NULL && curr1->stazione->km>=dest){
        p2=malloc(sizeof(struct grafo));
        p2->km=curr1->stazione->km;
        if(curr1->stazione->car_num!=0){
            p2->max_car=curr1->stazione->cars[0];
        }
        else{
            p2->max_car=0;
        }
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
        curr1=tree_predecessor(curr1);
    }
    if(end==NULL || start==NULL){
        printf("nessun percorso\n");
        return;
    }
    
    while(Q->tail!=NULL){
        p=dequeue(Q);
        p2=p->next; 
        while(p2!=NULL){
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
                p2=p2->next;
            }
            else{
                break;
            }
            
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

