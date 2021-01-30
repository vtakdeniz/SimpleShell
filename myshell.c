#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include "tekrar.c"
#include "islem.c"
#include <signal.h>

// Clears the shell using escape sequences 
#define clean() printf("\033[H\033[J")

// Max list size
#define MAXLIST 100 

void islem(char ** param);
void tekrar(char ** param);

//Number of total comands
int NoOfCmds;

//List of commands
char* ListOfCmds[5]; 

// Uses the clean() function defined in the beginning;
void clear(){
clean();
}


// Parses the space in given string and returns all the parsed string in a ** list so each command can be taken with it's parameter
void parseSpace(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, " "); 
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
} 

// Parses the pipe sign shown as -> "|" and splits strings before and after pipe and puts them in a ** list.
int parsePipe(char* str, char** strpiped) 
{ 
    int i; 
    for (i = 0; i < MAXLIST; i++) { 
        strpiped[i] = strsep(&str, "|"); 
        if (strpiped[i] == NULL) 
            break; 
    } 
  
    if (strpiped[1] == NULL) 
        return 0; // returns zero if no pipe is found. 
    else { 
        return 1; 
    } 
} 


//Checks whether the given command is in the ListOfCmds list and returns it's position in the list + 1
int findCom(char * com){
int j=-1;    
for (int i = 0; i < NoOfCmds; i++)
{
    int comp= strcmp(com,ListOfCmds[i]);
    if (comp==0)
    {
        j=i;
        break;
    }   
}
return j+1;
}

// terminates the process by killing it.
void terminate(){
    int parent=getppid();
    kill(parent, SIGKILL);
}

// Calls the cat function from the system.
void catcall(char ** param){

if (param[2]!=NULL)
    {
        printf("Yanlış bir komut girdiniz");
        printf("\n");
        exit(0);  
    }
  
execl("/bin/cat","cat",param[1],NULL);
}

// executes the function by position integer that is taken from findCom and takes argument parameter
void execute(int f, char ** param){
     switch (f) { 
    case 1: 
        terminate();
        break;
    case 2: 
        clear();
        break;
    case 3: 
        islem(param);
        break;
    case 4: 
        tekrar(param);
        break;
    case 5: 
        catcall(param); 
        break;
    } 

}

// takes user input and executes it by calling excute function via fork process.
int takeinput(){
     char * c [MAXLIST];
     gets(c);
     char ** piped[MAXLIST];
     parsePipe(c,piped);
     for (int i = 0; i < MAXLIST; i++)
     {
        char ** parsed[MAXLIST];
        if (piped[i]==NULL)
        {
            break;
        }
       
        parseSpace(piped[i],parsed);
        for (int j = 0; j < 10; j++)
        {
           if (parsed[j]==NULL)
           {
               break;
           }

           if (j==0)
           {
               int r = findCom(parsed[0]);
               if (r==0)
               {
                  printf("Yanlış bir komut girdiniz");
                  printf("\n");
                  return -1;
               }
               else{
                   int f = fork();
                   if (f==0)
                   {
                       execute(r,parsed);
                       exit(0);
                   }
                   if (f>0)
                   {
                      int status;
                      wait(&status);
                   }
                   
                   
               }
           }
           
        }
      

     }
}

//main loop of the program.
void loop(){
while(1){
 
 printf("myshell>>");

 int a = takeinput();

 printf("\n");
}
}

//initializes the program by assign values to ListOfCmds list, cleaning the screen and calling the main loop.
void init() 
{   
    clear();
    NoOfCmds=5;
    ListOfCmds[0] = "exit"; 
    ListOfCmds[1] = "clear"; 
    ListOfCmds[2] = "islem"; 
    ListOfCmds[3] = "tekrar"; 
    ListOfCmds[4] = "cat"; 
    loop();
} 




int main(){
  init();
}