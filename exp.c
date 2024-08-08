#include<stdio.h>
#include<string.h>
char ch[5][80]={"hi","hola","hello"};
char ch1[5][80]={"hi","hola","hello"};
int d=0;
int main(){
    //a(ch1,d);
    a(ch,d);
    for(int i=0;i<5;i++){
        printf("%s\n%d",ch[i],d);
        
    }
}
void a(char b[5][80],int n){
    strcpy(b[3],"hi");
    n++;
}