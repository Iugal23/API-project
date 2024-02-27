#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct stazione{
    int km;
    int car_num;
    int *cars;
    struct stazione *next; // puntatore alla prossima stazione della autostrada
    struct stazione *prev; // puntatore alla precedente stazione della autostrada
    
};
typedef struct stazione *autostrada;


struct BSTnode
{
    autostrada stazione;
    struct BSTnode *right;
    struct BSTnode *left;
    struct BSTnode *parent;
    
};
typedef struct BSTnode *BSTtree;

BSTtree BSTtree_delete(BSTtree T, int km);
BSTtree BSTtree_insert(BSTtree T, int km);
BSTtree tree_successor(BSTtree T);
BSTtree tree_predecessor(BSTtree T);
int tree_heigth(BSTtree T);

void printTreeUtil(BSTtree root, int space);
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

int main(){
    BSTtree T=NULL,temp;
    char command[22];
    int dist,battery,*batteries,auto_num,x,part,dest,count=0;
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
                T=BSTtree_insert(T,dist);
                printTreeUtil(T,0);
                printf("------------------------------------------------------------------------------------------------------------\n");
                printf("------------------------------------------------------------------------------------------------------------\n");
                count++;
                free(batteries);
            }
            else{
                x=input(command);
                dist=atoi(command);
                x=input(command);
                battery=atoi(command);
            }

        }
        else if(command[0]=='d'){
            x=input(command);
            dist=atoi(command);
            T=BSTtree_delete(T,dist);
            printTreeUtil(T,0);
            printf("------------------------------------------------------------------------------------------------------------\n");
            printf("------------------------------------------------------------------------------------------------------------\n");
            count--;
        }
        else if(command[0]=='r'){
            x=input(command);
            dist=atoi(command);
            x=input(command);
            battery=atoi(command);
        }
        else if(command[0]=='p'){
            x=input(command);
            part=atoi(command);
            x=input(command);
            dest=atoi(command);
        }
    }while(x!=EOF);



}

BSTtree BSTtree_insert(BSTtree T, int km){
    BSTtree new=malloc(sizeof(struct BSTnode)),curr=T,prev=NULL;
    autostrada staz=malloc(sizeof(struct stazione));
    staz->km=km;
    new->stazione=staz;
    new->left=NULL;  
    new->right=NULL;
    while(curr!=NULL){
        prev=curr;
        if(curr->stazione->km==new->stazione->km){
            return T;
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
        T=new;
    }
    else if(new->stazione->km<prev->stazione->km){
        prev->left=new;
    }
    else{
        prev->right=new;
    }
    return T;
    
}
BSTtree BSTtree_delete(BSTtree T, int km){
    BSTtree del, temp=T, p;
    while(temp!=NULL && temp->stazione->km!=km){
        if(temp->stazione->km<km){
            temp=temp->right;
        }
        else{
            temp=temp->left;
        }
    }
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
            T=p;
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
    }
    return T;
    
}
void printTreeUtil(BSTtree root, int space) {
    if (root == NULL)
        return;

    space += 5;

    printTreeUtil(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");

    printf("%d\n",root->stazione->km);

    printTreeUtil(root->left, space);
}
BSTtree tree_successor(BSTtree T){
    BSTtree curr,r;
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
BSTtree tree_predecessor(BSTtree T){
    BSTtree curr,r;
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
int tree_heigth(BSTtree T){
    int maxL=0,maxR=0;
    if(T!=NULL){
        maxL=tree_heigth(T->left);
        maxR=tree_heigth(T->right);
        if(maxL>maxR){
            return maxL+1;
        }
        else{
            return maxR+1;
        }
    }
    return -1;
}
