#include <stdio.h>
#include <stdlib.h>
void build_max_heap(int a[],int length);
void max_heapify(int a[],int i, int length);
void heap_insert_fix(int *a,int i);
void heap_delete_fix(int *a,int i,int length);


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

autostrada aggiungi_stazione(autostrada A,int dist,int n, int* bat);
void inserisci_adiacente(autostrada A,autostrada nodo);
void rimuovi_stazione(autostrada A,int km_del);
void inserisci_auto(autostrada A,int km_staz,int car);

int main(){ 
    autostrada A=NULL,curr1;
    int A1[4]={25,10,15,5},A2[1]={40},A3[1]={30},A4[1]={40},A5[2]={25,20};
    A=aggiungi_stazione(A,20,4,A1);
    A=aggiungi_stazione(A,30,1,A2);
    A=aggiungi_stazione(A,40,1,A3);
    A=aggiungi_stazione(A,45,1,A4);
    A=aggiungi_stazione(A,50,2,A5);
    rimuovi_stazione(A,40);
    inserisci_auto(A,50,40);
    inserisci_auto(A,20,35);
    inserisci_auto(A,10,90);
    curr1=A;
    while(curr1!=NULL){
        printf("%d:",curr1->km);
        for(int i=0;i<curr1->adj_num;i++){
            printf("%d->",curr1->graph[i]->km);
        }
        curr1=curr1->next;
        printf("END\n");
    }
    free(curr1);
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
            prec->next=new;
            new->next=curr;
            // inserimento adiacenti
            curr=A;
            while(curr!=NULL){
                if(curr->km<new->km){
                    if(curr->km+curr->cars[0]>=new->km){
                        inserisci_adiacente(curr, new);
                    }
                    if(new->km-new->cars[0]<=curr->km){
                        inserisci_adiacente(new,curr);
                    }
                }
                if(curr->km>new->km){
                    if(curr->km-curr->cars[0]<= new->km){
                        inserisci_adiacente(curr,new);
                    }
                    if(new->km+new->cars[0]>=curr->km){
                        inserisci_adiacente(new,curr);
                    }
                }
                curr=curr->next;
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
    autostrada curr=A,prec=NULL,curr2;
    while(curr!=NULL && curr->km!=km_del){
        prec=curr;
        curr=curr->next;
        if(curr->km>km_del){
            printf("non demolita\n");
            return;

        }
    }
    if(curr!=NULL){
        prec->next=curr->next;
        curr2=A;
        while(curr2!=NULL){
            for(int i=0;i<curr2->adj_num;i++){
                if(curr2->graph[i]->km==km_del){
                    curr2->adj_num--;
                    curr2->graph[i]=curr2->graph[curr2->adj_num];
                    curr2->graph=realloc(curr2->graph,curr2->adj_num*sizeof(struct stazione));
                }
            }
            curr2=curr2->next;
        }

        free(curr);
        printf("demolita\n");
        
    }
    else{
        printf("non demolita\n");
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
            heap_insert_fix(curr->cars,curr->car_num);
            
            printf("aggiunta\n");
            return;
        }
        curr=curr->next;
    }
    printf("non aggiunta\n");
    return;
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