#include <stdio.h>
#include <stdlib.h>
void build_max_heap(int a[],int length);
void max_heapify(int a[],int i, int length);


 struct stazione{
    int km;
    int car_num;
    int *cars;
    struct stazione *next; // puntatore alla prossima stazione della autostrada
    int dist;
    char col;
    struct stazione *adj; // puntatore alle stazioni adiacenti
    struct stazione *prev_stop; //puntatore alla tappa precedente del percorso
};

typedef struct stazione *autostrada;

autostrada aggiungi_stazione(autostrada A,int dist,int n, int* bat );
autostrada inserisci_in_ordine(autostrada A,autostrada new);

int main(){
    autostrada A=NULL,curr1,curr2;
    int A1[4]={25,10,15,5},A2[1]={40},A3[1]={30},A4[2]={25,20};
    A=aggiungi_stazione(A,20,4,A1);
    A=aggiungi_stazione(A,30,1,A2);
    A=aggiungi_stazione(A,45,1,A3);
    A=aggiungi_stazione(A,50,2,A4);
    return 0;

}

autostrada aggiungi_stazione(autostrada A,int dist,int n, int* bat ){
    autostrada temp,curr=A,prec=NULL, new=malloc(sizeof(struct stazione));
    new->km=dist;
    new->car_num=n;
    new->cars=calloc(n,sizeof(int));
    new->adj=NULL;
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
        
        }
        else{
            printf("non aggiunta\n");
        }

    }
    else{
        A=new;
        new->next=NULL;
    }
    
    return A;


}

autostrada inserisci_in_ordine(autostrada A,autostrada new){
    autostrada curr=A,prec=NULL;
    if(curr!=NULL){  
        while(curr!=NULL && curr->km<new->km){
            prec=curr;
            curr=curr->next;
        }
        prec->next=new;
        new->next=curr;
    }
    else{
        A=new;
        new->next=NULL;
    }

    return A;
}
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