#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<time.h>

char Names[2][22][5][60];                               //3D array of all the plalyer details
char team_name[2][60];                                  //array of characters which contains the team name
char ejected_players[2][11][3]; int rp1=0,rp2=0;        //array which contains the players who have received a red card
char teamtA[60];                                        //stores the team name
char teamtB[60];                                        //stores the team name
int goal1=0,goal2=0;

char attribute[5][20]={"Player_Name", "Jersey_Number", "Goals", "Yellow_Card", "Red_Card"};     //column headings

FILE *team_A;                   //file extraction from Excel
FILE *team_B;                   

void team_initialize(){
    printf("Enter the name of the 1st Team: ");
    scanf(" %[^\n]",team_name[0]);                  //team name input
    strcpy(teamtA,team_name[0]);                    //copying team name to teamtA
    printf("Enter the name of the 2nd Team: ");
    scanf(" %[^\n]",team_name[1]);
    strcpy(teamtB,team_name[1]);
}

void initialize(char n[2][22][5][60]){     //initializing the array
    for(int i=1;i<22;i++){
        for(int j=2;j<5;j++){
            strcpy(n[0][i][j],"0");       // goal,red_card,yellow_card as 0
            strcpy(n[1][i][j],"0");
        }
    }
    strcpy(n[0][21][2]," ");            //to initialize null values to coach
    strcpy(n[1][21][2]," ");
}

void extract_A(){                                   //extracting Team_A's Excel file 
    int p=0;                                        //in csv format to C array
    team_A = fopen(strcat(teamtA,".csv"), "r");
    char line[200], *token; int i=1,j=0;
    while(fgets (line, sizeof(line), team_A)) {
        j=0;
        if(p==0){
            p++;
            continue;
        }
        token=strtok(line,",");
        while(token!=NULL){
            strcpy(Names[0][i][j],token);
            token=strtok(NULL,",");
            j++;
        }
        i++;
    }
}

void extract_B(){                                      //extracting Team_B's Excel file 
    int p=0;                                           //in csv format to C array
    team_B = fopen(strcat(teamtB,".csv"), "r");        //"r"- represents that the file is readable
    char line[200], *token; int i=1,j=0;
    while(fgets (line, sizeof(line), team_B)) {
        j=0;
        if(p==0){
            p++;
            continue;
        }
        token=strtok(line,",");
        while(token!=NULL){
            strcpy(Names[1][i][j],token);
            token=strtok(NULL,",");
            j++;
        }
        i++;
    }
}

int team_select(){                                  //to select on which team the further functions
    int ch;
    printf("Enter 1 for Team %s, 2 for Team %s\n",team_name[0],team_name[1]);
    printf("Enter your choice: ");
    scanf("%d",&ch);
    printf("\n");
    do{
        if(ch==1 || ch==2)                      //checks for invalid input
        {
            break;
        }
        else{
            printf("Invalid Input\n\n");
            printf("Enter 1 for Team %s, 2 for Team %s\n",team_name[0],team_name[1]);       //returns back for input
            printf("Enter your choice: ");                                                  //after the invalid input
            scanf("%d",&ch);
            printf("\n");
        }
    }while(ch!=1 && ch!=2);
    if(ch==1)
        return 0;
    else
        return 1;
}

int jersey_number(int n){                       //selecting a particular player for further functions
    int j_no, p , pos;int rp;
    if(n==0)
        rp=rp1;
    else
        rp=rp2;
    do{
        p=0;
        printf("Enter the Jersey Number of the player: ");
        scanf("%d",&j_no);
        printf("\n");
        for(int i=1;i<12;i++){
            if(atoi(Names[n][i][1])==j_no){                 //"atoi"-converts the string in the array 
                pos=i;                                      //to integer datatype for conditional checking
                p=1;
                break;
            }
        }

        if(p==0){                                           //checks for invalid input
            printf("Invalid Input\n\n");
        }
        
        for(int i=0;i<rp;i++){                              //checks if the selected player has
            if(atoi(ejected_players[n][i])==j_no){          //got a red card
                p=0;
                printf("Player has got a red card\n\n");
                break;
            }            
        }
        
    }while(p==0);  
    return pos;  
}

void goal(int n){                                               //this function awards the goal to the respective
    int pos=jersey_number(n);                                   //team and player
    sprintf(Names[n][pos][2],"%d",(atoi(Names[n][pos][2])+1));
    if(n==0)
        goal1++;
    else
        goal2++;
}

void yellow_card(int n){                        //this function inputs the yellow card to a particular player,
    int pos=jersey_number(n);                   //and automatically puts him to the ejectes players array if 
    if((atoi(Names[n][pos][3])+1)!=2)           //the player has received 2 consecutive yellow cards
    sprintf(Names[n][pos][3],"%d",(atoi(Names[n][pos][3])+1));
    else{
        sprintf(Names[n][pos][3],"%d",(atoi(Names[n][pos][3])+1));
        strcpy(Names[n][pos][4],"1");
        if(n==0){
            strcpy(ejected_players[n][rp1],Names[n][pos][1]);
            rp1++;
        }
        else{
            strcpy(ejected_players[n][rp2],Names[n][pos][1]);
            rp2++;
        }
    }
}

void red_card(int n){                           //inputs a red card for a particular player
    int pos=jersey_number(n);                   //and puts the player to the ejected players list
    strcpy(Names[n][pos][4],"1");
    if(n==0){
        strcpy(ejected_players[n][rp1],Names[n][pos][1]);
        rp1++;
    }
    else{
        strcpy(ejected_players[n][rp2],Names[n][pos][1]);
        rp2++;
    }
}

void substitute(int n){                                 //function for substituting players
    int pos1=jersey_number(n); int pos2,p=0,j_no;int rp;
    if(n==0)
        rp=rp1;
    else
        rp=rp2;
    do{
        printf("Enter the jersey number of the player with which you want the previous player to be substituted:");
        scanf("%d",&j_no);
        printf("\n");
        for(int i=12;i<21;i++){
            if(atoi(Names[n][i][1])==j_no){
                pos2=i;
                p=1;
                break;
            }
        }

        if(p==0){
            printf("Invalid Input\n\n");                //checks for invalid input
        }
        for(int i=0;i<rp;i++){
            if(atoi(ejected_players[n][i])==j_no){
                p=0;
                printf("Player has got a red card\n");      //checks for redcard
                break;
            }            
        }
    }while(p==0);

    char temp[80];
    for(int j=0;j<5;j++){
        strcpy(temp,Names[n][pos1][j]);
        strcpy(Names[n][pos1][j],Names[n][pos2][j]);
        strcpy(Names[n][pos2][j],temp);
    }
}

void view_details(){                                    //to view the details during the match
    printf("\t\t\t\tTeam %s\n\n",team_name[0]);         //prints Team A details
    for(int i=0;i<22;i++){
        for(int j=0;j<5;j++){
            printf("%10s\t",Names[0][i][j]);
        }
        printf("\n");
    }

    printf("\n\n\n");
    printf("\t\t\t\tTeam %s\n\n",team_name[1]);         //prints Team B details
    for(int i=0;i<22;i++){
        for(int j=0;j<5;j++){
            printf("%10s\t",Names[1][i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void sort_goals(int n){                     //sorts the player based on the no. of goals scored
    char temp[60];
    for(int i=0;i<19;i++){
        for(int j=0;j<19-i;j++){
            if( atoi(Names[n][j+1][2]) < atoi(Names[n][j+2][2])){
                for(int k=0;k<5;k++){
                    strcpy(temp,Names[n][j+1][k]);
                    strcpy(Names[n][j+1][k],Names[n][j+2][k]);
                    strcpy(Names[n][j+2][k],temp);
                }
            }
        }
    }
}

void update_A(){                                //updates the Excel file with the final array values
    team_A = fopen(teamtA, "w");                //"w"- represents that the the file is writeable
    
    for(int i=0;i<22;i++){
        for(int j=0;j<5;j++){
            fprintf(team_A, Names[0][i][j]);
            fprintf(team_A, ",");
        }
        fprintf(team_A, "\n");
    }
    fclose(team_A);
    team_A=0;
}

void update_B(){
    team_B = fopen(teamtB, "w");
    for(int i=0;i<22;i++){
        for(int j=0;j<5;j++){
            fprintf(team_B, Names[1][i][j]);
            fprintf(team_B, ",");
        }
        fprintf(team_B, "\n");
    }
    fclose(team_B);
    team_B=0;
}

void menu(){                //this functions offers us the list of operations that can be performed
    char ch;
    printf("\nMatch has started\n");
    do{
        printf("G: For Goal\n");
        printf("Y: For Yellow Card\n");
        printf("R: For Red Card\n");
        printf("S: For Substituting Player\n");
        printf("V: View the current details of the match\n");
        printf("C: Completion of the match\n\n");
        printf("Enter your choice:");        
        scanf(" %c",&ch);
        printf("\n");
        ch=toupper(ch);
        switch(ch){                         //switch statements to select particlular operations
            case 'G':
                goal(team_select());
            break;

            case 'Y':
                yellow_card(team_select());
            break;

            case 'R':
                red_card(team_select());
            break;

            case 'S':
                substitute(team_select());                
            break;

            case 'V':
                view_details();
            break;

            case 'C':
                sort_goals(0);
                sort_goals(1);
                update_A();
                update_B();
                view_details();
                printf("\nScore: %d-%d\n\n",goal1,goal2);      //prints the total no. of goals scored by
                if(goal1>goal2)                                //each team and compares them
                    printf("Winner: %s", team_name[0]);
                else if(goal1<goal2)
                    printf("Winner: %s", team_name[1]);        //declares the winner 
                else                                            
                    printf("Draw");                            //prints draw if total no. of goals are equal
                exit(0);
            break;

            default:
            printf("Invalid Input\n\n");                       //checks for invalid input
        }
    }while(1);
}

int main(){
    for(int i=0;i<5;i++){
        strcpy(Names[0][0][i], attribute[i]);
        strcpy(Names[1][0][i], attribute[i]);
    }
    team_initialize();                         //line No. 20
    extract_A();                               //line No. 40
    extract_B();                               //line No. 60
    initialize(Names);                         //line No. 29
    menu();                                    //line No. 280
    view_details();                            //line No. 218
    return 0;
}