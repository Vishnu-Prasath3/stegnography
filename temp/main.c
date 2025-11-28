#include <stdio.h>

int main()
{

// int magic_str =(sizeof(char)*8)*2;
FILE *fptr;

// open in read mode
fptr = fopen("file_pointer.txt","r");
char content[1000];
if(fptr != NULL)
{

while(fgets(content,1000,fptr)){
    printf("%s",content);
// fgets reads a line at a time
}
printf("%s",content);

}
else{
    printf("File does not-exist");
}
// fget for reading content in the file
fclose(fptr);

(fptr);

}
