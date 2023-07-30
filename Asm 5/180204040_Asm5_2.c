/* CSE 4130 (Fall 2021)                  Assignment - 5                   ID:180204040                      */
#include<stdio.h>
#include<string.h>

char inp[10000];
int index = 0,len = 0;



int ID()
{
    if(inp[index] >= 'a' && inp[index] <='z')
    {
        index++;
        return 1;
    }
    return 0;
}

int NUM()
{
    if(inp[index] >= '0' && inp[index] <='9')
    {
        index++;
        return 1;
    }
    return 0;
}

int factor()
{
    if(inp[index] == '(')
    {
        index++;
        expn();
        index--;
        if(inp[index] == ')')
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
            if(inp[index]=='*' || inp[index]=='/')
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

int expn()
{
    if(term())
    {
        if(index<len)
        {
            if(inp[index] == '+' || inp[index] == '-')
            {
                index++;
                if(term())
                    return 1;
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int main()
{
    printf("Enter arithmetic expression: ");
    gets(inp);
    len = strlen(inp);
    int f = 0;
    while(index<len)
    {
        if(expn())
            f = 1;
        else
        {
            f=0;
            break;
        }
    }
    if(f)
        printf("The arithmetic expression is accepted.");
    else
        printf("The arithmetic expression is not accepted");

    return 0;
}
