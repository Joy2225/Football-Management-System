#include<stdio.h>
#include<string.h>
char c[80]="java,python,c++,hi,jgh";
int main(){
    char *a;
    a=strtok(c, ",");
    while(a!= NULL){
        printf("%s ",a);
        a=strtok(NULL,",");
    }
}