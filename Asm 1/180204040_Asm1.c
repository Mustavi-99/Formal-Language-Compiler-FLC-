/* CSE 4130 (Fall 2021)      Assignment - 1    ID:180204040 */
#include<stdio.h>

int main()
{
    FILE *fp,*fp2;
    fp = fopen("input.c","r");
    fp2= fopen("codewithline.txt","w");
    int pf=1,parf=0,prif=1;
    char c,cb;
    while((c=getc(fp))!=EOF)
    {
        if(c=='(')
            parf = 1;
        if(c=='"' && parf)
            prif = 0;
        if(c== ')')
        {
            prif = 1;
            parf = 0;
        }
        if(prif)
        {
            if (c == cb && c==' ')
                pf = 0;
            if(c=='/')
            {
                while(c=getc(fp))
                {
                    if(c=='/')
                    {
                        while((c=getc(fp) )!= '\n');
                        break;
                    }
                    else if(c=='*')
                        while((c=getc(fp) )!= '/');
                    pf=0;
                    break;
                }
            }
        }
        if(c=='\n')
            continue;
        if(pf)
            fputc(c,fp2);
        pf=1;
        cb = c;
    }
    fclose(fp);
    fclose(fp2);
    fp2= fopen("codewithline.txt","r");
    while((c=getc(fp2))!=EOF)
    {
        printf("%c",c);
    }
    fclose(fp2);
    return 0;
}

