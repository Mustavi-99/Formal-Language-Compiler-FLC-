/* CSE 4130 (Fall 2021)     Assignment - 2     ID:180204040 */
#include<stdio.h>
#include<string.h>
int checkkw(char lex[])
{
    FILE *kw;
    kw = fopen("kw.txt","r");
    char c,lexstr[100];
    int i=0,result=0;
    while((c = getc(kw))!=EOF)
    {
        if(!isspace(c))
        {
            lexstr[i] = c;
            i++;
        }
        else
        {
            for(int j=0; j<strlen(lexstr); j++)
            {
                if(lexstr[j]!=lex[j])
                {
                    result = 0;
                    break;
                }
                result = 1;
            }
            i = 0;
            if(result==1)
            {
                return result;
            }
            memset(lexstr,0,strlen(lexstr));
        }
    }
    fclose(kw);
    return result;
}

int sep(char lex)
{
    if(lex == '\'' || lex == ',' || lex == ';' || lex == '\"')
        return 1;
    return 0;
}

int op(char lex[])
{
    FILE *op;
    op = fopen("op.txt","r");
    char c,lexstr[100];
    int i=0,result=0;
    while((c = getc(op))!=EOF)
    {
        if(!isspace(c))
        {
            lexstr[i] = c;
            i++;
        }
        else
        {
            for(int j=0; j<strlen(lexstr); j++)
            {
                if(lexstr[j]!=lex[j])
                {
                    result = 0;
                    break;
                }
                result = 1;
            }
            i = 0;
            if(result==1)
            {
                return result;
            }
            memset(lexstr,0,strlen(lexstr));
        }
    }
    fclose(op);
    return result;
}
int id(char lex[])
{
    int i = 0,l,s;
    if(isalpha(lex[i]) || (lex[i]=='_'))
    {
        s=1;
        i++;
    }else
        s=0;
    l=strlen(lex);
    if(s)
    {
        for(;i<l;i++)
        {
            if(isalpha(lex[i]) || (lex[i]=='_') || isdigit(lex[i]))
            {
                s=1;
            }
            else
            {
                s=0;
                break;
            }
        }
    }
    return s;
}
int num(char lex[])
{
    int i = 0, l, s;
    if(isdigit(lex[i]))
    {
        s=1;
        i++;
    }
    else if(lex[i]=='.')
    {
        s=2;
        i++;
    }
    else s=0;
    l=strlen(lex);
    if(s==1)
        for( ; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=1;
            else if(lex[i]=='.')
            {
                s=2;
                i++;
                break;
            }
            else
            {
                s=0;
                break;
            }
        }
    if(s==2)
        if(isdigit(lex[i]))
        {
            s=3;
            i++;
        }
        else
            s=0;
    if(s==3)
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=3;
            else
            {
                s=0;
                break;
            }
        }
    if(s==3) s=1;
    return s;
}


int par(char lex)
{
    if(lex == '(' || lex == ')')
        return 1;
    return 0;
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
    fp = fopen("output2.c","w");
    char lex[100];
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
            fputc('[',fp);
            if(checkkw(lex) == 1)
            {
                fprintf(fp,"kw %s",lex);
            }
            else if(sep(lex[0]) == 1)
            {
                fprintf(fp,"sep %s",lex);
            }
            else if(id(lex) == 1)
            {
                fprintf(fp,"id %s",lex);
            }
            else if(num(lex) == 1)
            {
                fprintf(fp,"num %s",lex);
            }
            else if(op(lex) == 1)
            {
                fprintf(fp,"op %s",lex);
            }
            else if(par(lex[0]) == 1)
            {
                fprintf(fp,"par %s",lex);
            }
            else
            {
                fprintf(fp,"unkn %s",lex);
                ucheck = 1;
            }
            fprintf(fp,"] ");
            i = 0;
            memset(lex,0,strlen(lex));
        }
    }
    fclose(fp2);
    fclose(fp);

    fp2= fopen("output2.c","r");
    printf("\nOutput 2:\n");
    while((c=getc(fp2))!=EOF)
    {
        printf("%c",c);
    }
    fclose(fp2);

    if(ucheck)
        printf("\n\nUnknown lexeme detected.\n");
    return 0;
}
