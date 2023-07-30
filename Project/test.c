#include<stdio.h>
int main()
{
    FILE *fp;
    fp = fopen("input.c","w");
    char c,userip[10000];
    int uf = 1,sf = 0,ui=0;
    while(uf)
    {
        scanf("%c",&c);
        if(c == '\n' && sf)
        {
          uf = 0;
        }
        else if(c == '\n')
        {
            userip[ui] = c;
            sf = 1;
            ui++;
        }
        else
        {
            sf=0;
            userip[ui] = c;
            ui++;
        }
    }
    printf("%s",userip);
    for(int i = 0;i<ui;i++)
        fputc(userip[i],fp);
    fclose(fp);

}
