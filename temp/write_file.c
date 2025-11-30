#include<stdio.h>
#include<ctype.h>

int main(){

    
    FILE *fp;
    // create a file;
    fp = fopen("hello.txt","r");
  
    char ch;
     
    ch =fgetc(fp);
    while(ch!= EOF)
    {printf("%c",ch);}
    
    fclose(fp);




}