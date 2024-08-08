#include<stdio.h>
#include<string.h>
char a[5][60]={"hi","hola","hello","oyeah","ahh"};
char team_select(){
    int ch;
    printf("Enter 1 for Team A, 2 for Team B\n");
    printf("Enter your choice: ");
    scanf("%d",&ch);
    if(ch==1)
    return a;
    else if(ch==2)
    return 'h';
    else{
        printf("Invalid input\n");
        return team_select();
    }
}
int main(){
    char s[5][60];
    strcpy(s,team_select());
    printf("hhello w");
    for(int i=0;i<5;i++){
        printf("%s\n",s[i]);
    }
    printf("hhello w");
}