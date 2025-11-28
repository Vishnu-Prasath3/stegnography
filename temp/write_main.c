#include <stdio.h>

int main()
{
FILE *fp;

fp = fopen("vishnu.txt","W");

printf("hello world");
fclose(fp);


}
