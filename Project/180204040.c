/* CSE 4130 (Fall 2021)      Assignment - 1    ID:180204040 */
#include<stdio.h>
#include<string.h>
int eF = 0;
char checkinp[10000];
int index = 0,len = 0;

int expn();
int stat();

int ID()
{
    if(checkinp[index] >= 'a' && checkinp[index] <='z')
    {
        index++;
        return 1;
    }
    return 0;
}

int NUM()
{
    if(checkinp[index] >= '0' && checkinp[index] <='9')
    {
        index++;
        return 1;
    }
    return 0;
}

int factor()
{
    if(checkinp[index] == '(')
    {
        index++;
        expn();
        index--;
        if(checkinp[index] == ')')
        {
            index++;
            return 1;
        }
        return 0;
    }
    if(ID() || NUM())
        return 1;
    return 0;
}

int term()
{
    if(factor())
    {
        if(index<len)
        {
            if(checkinp[index]=='*' || checkinp[index]=='/')
            {
                index++;
                if(factor())
                    return 1;
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int smpl_expn()
{
    if(term())
    {
        if(index<len)
        {
            if(checkinp[index] == '+' || checkinp[index] == '-')
            {
                index++;
                if(term())
                {
                    return 1;
                }
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
int relop()
{
    if((checkinp[index] == '=' || checkinp[index] == '!' || checkinp[index] == '<' || checkinp[index] == '>')&&checkinp[index+1]=='=')
    {
        index+=2;
        return 1;
    }
    if(checkinp[index]=='>'||checkinp[index]=='<')
    {
        index++;
        return 1;
    }
    return 0;
}

int extn()
{
    if(relop())
        return smpl_expn();
    return 1;
}
int expn()
{
    if(smpl_expn())
        return extn();
    return 0;
}

int asgn_stat()
{
    if(ID())
    {
        if(checkinp[index]=='=')
        {
          index++;
          return expn();
        }
    }
    return 0;
}
int extnl()
{
    if(checkinp[index]=='e' && checkinp[index+1]=='l' && checkinp[index+2]=='s' && checkinp[index+3]=='e')
    {
        index+=4;
        return stat();
    }

    return 1;
}

int dscn_stat()
{
    if(checkinp[index] == 'i' && checkinp[index+1] == 'f' && checkinp[index+2] == '(')
    {
        index += 3;

        if(expn())
        {
            if(checkinp[index]==')')
            {
                index++;
                if(checkinp[index]=='\n')
                    index++;
                if(stat())
                    return extnl();
            }
        }
    }
    return 0;
}

int loop_stat()
{
    if(checkinp[index] == 'w' && checkinp[index+1] == 'h' && checkinp[index+2] == 'i' && checkinp[index+3] == 'l' && checkinp[index+4] == 'e' && checkinp[index+5] == '(')
    {
        index +=6;
        if(expn())
        {
            if(checkinp[index]==')')
            {
                index++;
                if(checkinp[index]=='\n')
                                    index++;
                return stat();
            }
        }

    }
    if(checkinp[index] == 'f' && checkinp[index+1] == 'o' && checkinp[index+2] == 'r' && checkinp[index+3] == '(')
    {
        index += 4;

        if(asgn_stat())
        {


            if(checkinp[index] == ';')
            {

                index++;
                if(expn())
                {

                    if(checkinp[index]==';')
                    {

                        index++;
                        if(asgn_stat())
                        {
                            ///printf("check");
                            if(checkinp[index]==')')
                            {
                                index++;
                                if(checkinp[index]=='\n')
                                    index++;
                                return stat();
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
int stat()
{
    if(loop_stat() || dscn_stat() || asgn_stat())
        return 1;
    return 0;
}

int taI2 = 0;
struct symbolTable2
{
    char name[20][20];
    char idType[20][20];
    char dataType[20][20];
    char scope[20][20];
} symTable2;

void insert2(char n[], char iT[], char dT[], char scp[])
{
    strcpy(symTable2.name[taI2],n);
    strcpy(symTable2.idType[taI2],iT);
    strcpy(symTable2.dataType[taI2],dT);
    strcpy(symTable2.scope[taI2],scp);
    taI2++;
}

int lookUp2(char n[],char scp[])
{
    for(int i = 0; i<taI2; i++)
        if(!strcmp(symTable2.name[i],n))
        {

            if(!strcmp(symTable2.idType[i],"func"))
                return (i+1);
            else if(!strcmp(symTable2.scope[i],scp) || !strcmp(scp,"global") || !strcmp(symTable2.scope[i],"global"))
            {
                return (i+1);
            }
        }
    return 0;
}
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

int curB(char lex)
{
    if(lex == '{' || lex == '}')
        return 1;
    return 0;
}

int taI = 0;
struct symbolTable
{
    char name[20][20];
    char idType[20][20];
    char dataType[20][20];
    char scope[20][20];
    char value[20][20];
}symTable;

void insert(char n[], char iT[], char dT[], char scp[], char v[])
{
    strcpy(symTable.name[taI],n);
    strcpy(symTable.idType[taI],iT);
    strcpy(symTable.dataType[taI],dT);
    strcpy(symTable.scope[taI],scp);
    strcpy(symTable.value[taI],v);
    taI++;
}

void set_attribute(char n[], char scp[], char v[])
{
    for(int i= 0;i<taI;i++)
    {
        if(strcmp(symTable.name[i],n)==0 && strcmp(symTable.scope[i],scp)==0)
        {
            strcpy(symTable.value[i],v);
            break;
        }
    }
}

void frees()
{
    for(int i = 0 ; i<taI ; i++)
        free(symTable.name[i]);
}

int lookUp(char n[],char scp[])
{
    for(int i = 0; i<taI;i++)
        if(strcmp(symTable.name[i],n)==0)
        {
            if(strcmp(symTable.idType[i],"func")==0)
                return (i+1);
            else if(strcmp(symTable.scope[i],scp)==0)
                return (i+1);
        }

}

void display()
{
    printf("\nSl\tName\tId TYPE\tData Type\tScope\tValue\n-------------------------------------------------------\n");
    for(int i = 0; i<taI ; i++)
        printf("%d\t|%s\t|%s\t|%s\t\t|%s\t|%s\n",(i+1),symTable.name[i],symTable.idType[i],symTable.dataType[i],symTable.scope[i],symTable.value[i]);
}

void kwIdChecker(char inp[],int inpi)
{
    FILE *fp;
    char c,word[20],kword[20],keyW[20]=" ",idW[20]=" ",linec[20];
    int j=0,kwf,idf,wf;
    char scope[20]="global";
    fp = fopen("addspace.txt","w");
    for(int i=0; i<inpi; i++)
    {
        if(inp[i]=='(' || inp[i]==';' || inp[i]==',' || inp[i]==')' || inp[i]=='=' || inp[i]=='<')
            fprintf(fp," %c ",inp[i]);
        else
            fputc(inp[i],fp);
    }
    fclose(fp);
    inpi=0;
    fp = fopen("addspace.txt","r");
    while((c=fgetc(fp))!=EOF)
    {
        inp[inpi] = c;
        inpi++;
    }
    fclose(fp);
    linec[0]=inp[0];
    for(int i=0; i<inpi; i++)
    {
        if(inp[i]=='\n')
        {
            strcpy(keyW," ");
            strcpy(idW," ");
            idf=0;
            kwf=0;
            i++;
            j=0;
            while(inp[i] != ' ')
            {
                linec[j] = inp[i];
                i++;
                j++;
            }
            linec[j] = '\0';
            continue;
        }
        if(inp[i]=='}')
        {
            strcpy(scope,"global");
        }
        j=0;
        while(inp[i] != ' ')
        {
            word[j] = inp[i];
            i++;
            j++;
        }
        word[j] = '\0';
        wf = 1;
        //printf("\nword: %s",word);
        fp = fopen("kw.txt","r");
        while(fscanf(fp,"%s ",kword)==1)
        {
            if(!strcmp(kword,word))
            {
                if(kwf && !strcmp(word,keyW) && strcmp(word,"else"))
                {
                    printf("\nDuplicate keyword detected at line %s",linec);
                    eF = 1;
                }
                strcpy(keyW,word);
                kwf = 1;
                wf=0;
            }
        }
        fclose(fp);
        if(id(word) && wf)
        {
            strcpy(idW,word);
            idf=1;
        }
        if(idf && kwf && strcmp(idW," ") && strcmp(keyW," ") && keyW[0]!='e' && keyW[0]!='r' )
        {
            i++;
            j=0;
            while(inp[i] != ' ')
            {
                word[j] = inp[i];
                i++;
                j++;
            }
            word[j] = '\0';
            if(lookUp2(idW,scope))
            {
                ///printf("\nDuplicate identifier detected at line %s",linec);
            }
            else if(!strcmp(word,"("))
            {
                //printf("\nid: %s,kw: %s,par:%s---- line: %s",idW,keyW,word,linec);
                insert2(idW,"func",keyW,scope);
                strcpy(scope,idW);
            }
            else
            {
                //printf("\nid: %s,kw: %s;+++line: %s,%s",idW,keyW,linec,word);
                insert2(idW,"var",keyW,scope);
            }
            idf = 0;
            kwf = 0;
        }
        else if(idf && strcmp(idW," "))
        {
            if(!lookUp2(idW,scope))
            {
                printf("\nUnknown identifier detected at line %s",linec);
                eF = 1;
                ///printf(",%s,%s",idW,scope);
            }
            idf = 0;
        }


    }
}

void commentRemove(FILE *fp)
{
    FILE *f;
    f= fopen("comment_remove.txt","w");
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
        if(pf)
            fputc(c,f);
        pf=1;
        cb = c;
    }
    fclose(f);
    /*     f= fopen("comment_remove.txt","r");
     *     while((c=getc(f))!=EOF)
     *     {
     *         printf("%c",c);
     *     }
     *     fclose(f);
     */
}
int forCheck(char inp[],int k)
{
    k--;
    while(inp[k]==' ' && inp[k]!='(')
    {
        k--;
    }

    if(inp[k]=='(')
    {
        if(inp[k-3]=='f' && inp[k-2]=='o' && inp[k-1]=='r')
            return 1;
        else
            return 0;
    }
    else
        return 0;
}
void duplicateErrors(char inp[],int inpi)
{
    char linec[20],linecB[20],lineP[20],lineD[20],lineD2[20];
    int i=0, ifflag=0;
    int j=0, countB=0,countP=0,k;
    while(inp[i] != ' ')
    {
        linec[j] = inp[i];
        i++;
        j++;
    }
    linec[j] = '\0';
    for(i = 0; i<inpi; i++)
    {
        if(inp[i] == '\n')
        {
            if(countP>0)
            {
                printf("\nUnbalanced '(' at line %s",lineP);
                eF = 1;
                countP = 0;
            }
            i++;
            j=0;
            while(inp[i] != ' ')
            {
                linec[j] = inp[i];
                i++;
                j++;
            }
            linec[j] = '\0';
        }
        else if(inp[i] == '{')
        {
            countB++;
            strcpy(linecB,linec);
        }
        else if(inp[i] == '}')
            countB--;
        else if(inp[i] == '(')
        {
            countP++;
            ///printf("\n+++%s",linec);
            strcpy(lineP,linec);
        }
        else if(inp[i]==';')
        {
            k=i;
            k++;
            while(inp[k]!=';' && inp[k]==' ')
                k++;
            if(inp[k]==';')
                if(!forCheck(inp,i))
                {
                    if(strcmp(lineD2,linec))
                    {
                        printf("\nDuplicate token at line %s",linec);
                        eF = 1;
                        strcpy(lineD2,linec);
                    }
                }
        }
        else if(inp[i] == ')')
            countP--;
        else if(inp[i] == 'i' && inp[i+1] == 'f' && inp[i+2] == '(')
            ifflag++;
        else if(inp[i] == ' ' && inp[i+1] == 'e' && inp[i+2] == 'l' && inp[i+3] == 's' && inp[i+4] == 'e' && inp[i+5] == ' ')
            ifflag--;

        if(countB<0 && strcmp(lineD,linec))
        {
            printf("\nUnbalanced '}' at line %s",linec);
            eF = 1;
            strcpy(lineD,linec);
            countB=0;
        }
        else if(countB < 0)
            countB = 0;

        if(countP<0 && strcmp(lineP,linec))
        {
            printf("\nUnbalanced ')' at line %s",linec);
            eF = 1;
            strcpy(lineP,linec);
            countP=0;
        }
        else if(countP < 0)
            countP = 0;
        if(ifflag<0)
        {
            eF = 1;
            printf("\nUnmatched 'else' at line %s",linec);
            ifflag=0;
        }
    }
    if(countB)
    {
        printf("\nUnbalanced '{' at line %s",linecB);
        eF = 1;
    }

}

void addLineNum(FILE *fp, char inp[],int inpi)
{
    int linen=1;
    fprintf(fp,"%d ",linen);
    for(int i = 0; i<inpi; i++)
    {
        while(inp[i]!='\n')
        {
            fputc(inp[i],fp);
            i++;
        }
        fputc(inp[i],fp);
        linen++;
        fprintf(fp,"%d ",linen);
    }
}
void userInput()
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
    ///printf("%s",userip);
    for(int i = 0;i<ui;i++)
        fputc(userip[i],fp);
    fclose(fp);
}
int main()
{
    printf("Enter code:\n");
    userInput();
    FILE *fp,*fp2;
    fp = fopen("input.c","r");
    fp2= fopen("output1.c","w");
    int pf=1,parf=0,prif=1;
    char c,cb;
    /// Assignment 1
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
    fp2= fopen("output1.c","r");
    while((c=getc(fp2))!=EOF)
    {
        ///printf("%c",c);
    }
    fclose(fp2);
    /// Assignment 2
    fp = fopen("output1.c","r");
    fp2= fopen("output2.c","w");
    int i=1;
    ///printf("\Output of 1:\n");
    while((c=getc(fp))!=EOF)
    {
       /// printf("%c",c);
        if(c == '<' || c == '>' || c == '!' || c == '=')
        {
            cb = c;
            c=getc(fp);
          ///  printf("%c",c);
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
        else if(c == ',' || c == ';' || c == '+' || c == '-' || c == '/' || c == '*' || c == '(' || c == '"' || c == ')' || c == '\''|| c == '{'|| c == '}')
        {
            fprintf(fp2," %c ",c);
        }
        else
            fputc(c,fp2);
    }
    fclose(fp);
    fclose(fp2);
    /**fp2= fopen("output2.c","r");
    printf("\nOutput 2:\n");
    while((c=getc(fp2))!=EOF)
    {
        printf("%c",c);
    }
    fclose(fp2);*/

    fp2= fopen("output2.c","r");
    fp = fopen("output3.c","w");
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
            else if(curB(lex[0]) == 1)
            {
                fprintf(fp,"cur %s",lex);
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
/**
    fp2= fopen("output3.c","r");
    printf("\n------------------------------------");
    printf("\nLexemes:\n");
    while((c=getc(fp2))!=EOF)
    {
        printf("%c",c);
    }
    fclose(fp2);
*/
    if(ucheck)
    {
        printf("\n\nUnknown lexeme detected.\n");
        eF=1;
    }

    ///Assignment 3
    int inpi=0;
    char inp[1000];
    char scp[20] = "global";
    int j;
    fp = fopen("output3.c","r");
    while((c=getc(fp))!=EOF)
    {
        inp[inpi]=c;
        inpi++;
    }
    fclose(fp);
    fp2 = fopen("output4.c","w");
    ///printf("\nStep - 1:\n");
    for(int i = 0;i<inpi;i++)
    {
        if(inp[i] == '[' && inp[i+1]== 'i' && inp[i+2]=='d' && inp[i+3]==' ')
        {
            i+=4;
            j = 0;
            char id[20];
            while(inp[i] != ']')
            {
                id[j] = inp[i];
                i++;
                j++;
            }
            id[j] = '\0';
            ///printf("[id %s",id);
            fprintf(fp2,"[id %s",id);

        }
        if(inp[i]=='[')
        {
            ///printf("[");
            fputc('[',fp2);
            while(inp[i]!=' ')
                i++;
            i++;
        }

        ///printf("%c",inp[i]);
        fputc(inp[i],fp2);
    }
    fclose(fp2);
    for(int i = 0;i<inpi;i++)
    {
        if(inp[i] == 'k' && inp[i+1] == 'w' && inp[i+3]!='r')
        {
            char dT[20],n[20],v[20];
            j=0;
            i+=3;
            while(inp[i]!=']')
            {
                dT[j] = inp[i];
                j++;
                i++;
            }
            dT[j] = '\0';
            i+=3;
            if(inp[i]=='i' && inp[i+1] == 'd' && inp[i+2] == ' ')
            {
                i+=3;
                j=0;
                while(inp[i] !=']')
                {
                    n[j] = inp[i];
                    i++;
                    j++;
                }
                n[j] = '\0';

                i+=3;

                if(inp[i] == 's' || inp[i] == 'o')
                {
                    if(inp[i] == 's')
                        insert(n,"var",dT,scp," ");
                    else
                    {
                        i+=10;
                        j = 0;
                        while(inp[i] != ']')
                        {
                            v[j] = inp[i];
                            j++;
                            i++;
                        }
                        v[j] = '\0';
                        insert(n,"var",dT,scp,v);
                    }
                }
                else
                {
                    i+=4;
                    if(inp[i]==')')
                        insert(n,"var",dT,scp," ");
                    else
                    {
                        insert(n,"func",dT,"global"," ");
                        strcpy(scp,n);
                    }
                }
            }
        }
        else if(inp[i]=='[' && inp[i+1]=='i' && inp[i+2] == 'd' && inp[i+3]== ' ')
        {
            char n[20],v[20];
            i+=4;
            j = 0;
            while(inp[i] != ']')
            {
                n[j] = inp[i];
                j++;
                i++;
            }
            n[j]='\0';
            i+=3;
            if(inp[i]=='o' && inp[i+7] == 'n')
            {
                i+=10;
                j=0;
                while(inp[i] != ']')
                {
                    v[j] = inp[i];
                    j++;
                    i++;
                }
                v[j] = '\0';
                set_attribute(n,scp,v);
            }
        }
        else if(inp[i]=='}')
        {
            strcpy(scp,"global");
        }
    }
    ///printf("\n-----------------------------------\nSymbol Table:");
    ///display();
    strcpy(scp,"global");
    ///printf("\nStep - 4:\n");
    fp2 = fopen("output5.c","w");
    for(int i = 0;i<inpi;i++)
    {
        if(inp[i] == '[' && inp[i+1]== 'i' && inp[i+2]=='d' && inp[i+3]==' ')
        {
            i+=4;
            j = 0;
            char id[20];
            while(inp[i] != ']')
            {
                id[j] = inp[i];
                i++;
                j++;
            }
            id[j] = '\0';
            ///printf("[id %d",lookUp(id,scp));
            fprintf(fp2,"[id %d",lookUp(id,scp));
            if(inp[i+3]=='p' && inp[i+7]=='(' && strcmp(scp,"global") == 0)
                strcpy(scp,id);
        }
        if(inp[i]=='[')
        {
            ///printf("[");
            fputc('[',fp2);
            while(inp[i]!=' ')
                i++;
            i++;
        }
        if(inp[i] == '}')
            strcpy(scp,"global");
        ///printf("%c",inp[i]);
        fputc(inp[i],fp2);
    }
    fclose(fp2);
    /// Assignment 4
    inpi=0;
    int countB=0;

    ///printf("\n-----------------------------------------------\n");
    fp = fopen("input.c","r");
    commentRemove(fp);
    fclose(fp);
    fp = fopen("comment_remove.txt","r");
    while((c=getc(fp))!=EOF)
    {
        inp[inpi]=c;
        inpi++;
    }
    fclose(fp);
    fp = fopen("codewithline.txt","w");
    addLineNum(fp,inp,inpi);
    fclose(fp);
    fp = fopen("codewithline.txt","r");
    inpi=0;
    ///printf("With Line Numbers:\n");
    while((c=getc(fp))!=EOF)
    {
        ///printf("%c",c);
        inp[inpi]=c;
        inpi++;
    }
    fclose(fp);
    printf("\n------------------------------\nErrors:");
    duplicateErrors(inp,inpi);
    kwIdChecker(inp,inpi);
    ///printf("\n------------------------------\n");
    ///printf("--\n%s",checkinp);
    if(!eF)
        printf("\nNo error.\n");
    else
        printf("\nThere is at least one error.\n");

    fp = fopen("comment_remove.txt","r");
    inpi=0;
    while((c=getc(fp))!=EOF)
    {
        inp[inpi]=c;
        inpi++;
    }
    inp[inpi]='\0';
    fclose(fp);
    len = 0;
    for(int i = 0; i<inpi; i++)
    {
        if((inp[i]=='f'&& inp[i+1]=='o'&&inp[i+2]=='r' ) || (inp[i]=='i'&& inp[i+1]=='f' ))
        {
            while(1)
            {
                checkinp[len] = inp[i];
                len++;
                i++;
                if(inp[i]==';' && inp[i+1]=='\n')
                {
                    i+=2;
                    break;
                }
            }
            len = strlen(checkinp);
            if(stat())
            {
                printf("\nCompilation successful\n");
                //break;
            }
            else
            {
                printf("\nCompilation error. %s l\n",checkinp);
            }

            memset(checkinp,0,strlen(checkinp));
            len=0;
        }
    }

    /*if(stat())
    {
        printf("\nCompilation successful\n");
    }
    else
        printf("\nCompilation error.\n");*/
    //display();
    return 0;

}


