#include<stdio.h>
int main()
{
    FILE *fp;
    fp = fopen("input.c","r");
    char c;
    while((c=getc(fp))!=EOF)
    {
        printf("%c",c);
    }
    fclose(fp);
}
