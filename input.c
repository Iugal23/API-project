#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int input(char s[]);
int main(){
    int x;
    char command[20],c;
    do{
        x=input(command);
        printf("%d\n",atoi(command));
        strcpy(command,"                   ");
    }while(x!=EOF);
    
}
int input(char s[]){
    int i=0;
    char c;
    do{
        c=getchar();
        s[i]=c;
        i++;
    }while(c!=' ' && c!=EOF);
    if(c==' '){
        return i-1;
    }
    else{
        return EOF;
    }
    
}