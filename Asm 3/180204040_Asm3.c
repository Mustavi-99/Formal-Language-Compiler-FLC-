/* CSE 4130 (Fall 2021)     Assignment - 3     ID:180204040 */
#include<stdio.h>
#include<string.h>

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

int main()
{
    FILE *fp,*fp2;
    int inpi=0;
    char inp[1000],c;
    char scp[20] = "global";
    int j;
    fp = fopen("input.txt","r");
    printf("Input file:\n");
    while((c=getc(fp))!=EOF)
    {
        printf("%c",c);
        inp[inpi]=c;
        inpi++;
    }
    fclose(fp);
    fp2 = fopen("step1.txt","w");
    printf("\nStep - 1:\n");
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
            printf("[id %s",id);
            fprintf(fp2,"[id %s",id);

        }
        if(inp[i]=='[')
        {
            printf("[");
            fputc('[',fp2);
            while(inp[i]!=' ')
                i++;
            i++;
        }

        printf("%c",inp[i]);
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
    printf("\n\nStep - 2:");
    display();
    strcpy(scp,"global");
    printf("\nStep - 4:\n");
    fp2 = fopen("step4.txt","w");
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
            printf("[id %d",lookUp(id,scp));
            fprintf(fp2,"[id %d",lookUp(id,scp));
            if(inp[i+3]=='p' && inp[i+7]=='(' && strcmp(scp,"global") == 0)
                strcpy(scp,id);
        }
        if(inp[i]=='[')
        {
            printf("[");
            fputc('[',fp2);
            while(inp[i]!=' ')
                i++;
            i++;
        }
        if(inp[i] == '}')
            strcpy(scp,"global");
        printf("%c",inp[i]);
        fputc(inp[i],fp2);
    }
    fclose(fp2);
    return 0;
}
