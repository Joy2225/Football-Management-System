#include<stdio.h>
#include <string.h>

int main(void){
    FILE *fp1,*fp2;
    char a[80], b[80];
    printf("Enter name of the First Team\n");
    scanf("%s",a);
    printf("Enter name of the Second Team\n");
    scanf("%s",b);

    strcat(a,".csv");
    strcat(b,".csv");

    fp1 = fopen(a,"w");
    fp2= fopen(b,"w");

    if(fp1 == NULL || fp2 == NULL){
        printf("The file couldn't be opened for some reason");
    
        return 1;
    }
    fclose(fp1);
    fclose(fp1);
    fp1 = 0, fp2=0;
    return 0;
}