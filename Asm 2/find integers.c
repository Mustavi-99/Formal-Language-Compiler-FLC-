#include<stdio.h>
#include<string.h>

int checkint(char* lex)
{
    int s=1;
    for(int i=0;i<strlen(lex);i++)
    {
        if(!isdigit(lex[i]))
        {
            s=0;
            break;
        }
    }
    return s;
}

int main()
{
    FILE *fp,*fp2;
    fp = fopen("input.c","r");
    fp2= fopen("output1.c","w");
    int i=1;
    char c,cb;
    printf("Input:\n");
    while((c=getc(fp))!=EOF)
    {
        printf("%c",c);
        if(c == '<' || c == '>' || c == '!' || c == '=')
        {
            cb = c;
            c=getc(fp);
            printf("%c",c);
            if(c == '=')
            {
                fprintf(fp2," %c%c ",cb,c);
            }
            else if( c == '\'')
            {
                fprintf(fp2," %c %c ",cb,c);
            }
            else
            {
                fprintf(fp2," %c %c",cb,c);
            }
        }
        else if(c == ',' || c == ';' || c == '+' || c == '-' || c == '/' || c == '*' || c == '(' || c == '"' || c == ')' || c == '\'')
        {
            fprintf(fp2," %c ",c);
        }
        else
            fputc(c,fp2);
    }
    fclose(fp);
    fclose(fp2);
    fp2= fopen("output1.c","r");
    printf("\nOutput 1:\n");
    while((c=getc(fp2))!=EOF)
    {
        printf("%c",c);
    }
    fclose(fp2);

    fp2= fopen("output1.c","r");
    char lex[100],*l;
    i=0;
    int sp = 0,ucheck = 0;
    while((c=fgetc(fp2))!=EOF)
    {
        if(!isspace(c))
        {
            lex[i]=c;
            i++;
            sp=0;
        }
        else if(sp != 1)
        {
            sp = 1;
            l = lex;
            if(checkint(l) == 1)
            {
                printf("int %s\n",lex);
            }
            i = 0;
            memset(lex,0,strlen(lex));
        }
    }
    fclose(fp2);
    return 0;
}
