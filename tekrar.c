
#define MAXLIST 100 // Max list size

// checks whether the given string is all integer or not for exception control
int tDigitsOnly(char * str)
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

//takes **param as an input. Extracts the integer values and string to be repeated.
void tekrar(char ** param){

char * string[MAXLIST];
char * cnum[MAXLIST];
int num;

for (int i = 0; i < MAXLIST; i++)
{
    if (i==1)
    {
        strcpy(string,param[i]);
    }
    else if(i==2)
    {
        strcpy(cnum,param[i]);
        int isDigit= tDigitsOnly(cnum);
        if (isDigit==0)
        {
           printf("Yanlış bir komut girdiniz");
           printf("\n");
           exit(0);
        }
        else{
          num=atoi(cnum);
        }
        
    }
    
}
printf("\n");
//prints the input num times
for (int i = 0; i < num; i++)
{
    printf(string);
    printf("\n");
}

}