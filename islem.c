#include "topla.c"
#include "cikar.c"
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 

// Max list size
#define MAXLIST 100 

int topla(int num1 ,int num2);
int cikar(int num1 ,int num2);

// checks whether the given string is all integer or not for exception control
int DigitsOnly(char * str)
{
    for (int i = 0; i < MAXLIST; i++)
    {
         if(str[i]==NULL){
           break;
         }
         if (str[i] < '0' || str[i] > '9')
         {
           return 0;
         }
            
    }
    return 1;
}

// seperates the parameter into arguments of type, number 1 and number 2. Then assigns them to variables for later calculation.
void islem(char ** param){

char  tip[MAXLIST];
char * cnum1[MAXLIST];
char * cnum2[MAXLIST];

int num1;
int num2;





for (int i = 0; i < MAXLIST; i++)
{
   if (param[i]==NULL)
   {
       break;
   }
   if (i==1)
   {
       strcpy(tip,param[i]);
   }
    if(i==2){
       strcpy(cnum1,param[i]);
       int isDigit1 =  DigitsOnly(cnum1);
       if (isDigit1==0)
{
   printf("Yanlış bir komut girdiniz");
   printf("\n");
   exit(0);
}

       num1 = atoi(cnum1);
   }
    if (i==3){
       strcpy(cnum2,param[i]);
       int isDigit2 =  DigitsOnly(cnum2);

       if (isDigit2==0)
{
   printf("Yanlış bir komut girdiniz");
   printf("\n");
   exit(0);
}
       num2 = atoi(cnum2);
   }
   
}



  

//Checks the calculation type to detect whether it's substraction or addition. Than calls the function.
 char islem1[6]="cikar";   
 int compc = strncmp(tip,islem1,5);   
 if (compc==0)
{
    int fo=fork();
    if (fo==0)
    {
    int a = cikar(num1,num2);
    printf("\n");
    printf("%d",a);
    printf("\n"); 
    }
    else{
        int status;
        wait(status);
         }
    
   
}
char islem2[5]="topla";    
int compt = strncmp(tip,islem2,5);
 if(compt==0){
     int fo= fork();
     if (fo==0)
     {
    int a = topla(num1,num2);
    printf("\n");
    printf("%d",a);
    printf("\n"); 
     }
     else{
         int status;
         wait(status);
     }
     
   
}   

 if (compt!=0&&compc!=0){
printf("Yanlış bir komut girdiniz");
printf("\n");
}
 
}