/* CSE 4130 (Fall 2021)                  Assignment - 5                   ID:180204040                      */
#include<stdio.h>

char str[2000];
int i=0,f,l;

int X()
{
    while(i<l-1)
    {
        if(str[i]=='b' && ( str[i+1] == 'b' || str[i+1] == 'c'))
            i = i+2;
        else return 0;
    }
    return 1;
}

void A()
{
    if(str[i]=='a')
    {
        i++;
        if(l==2 && str[l-1]=='d')
            f=1;
        else
        {
            if(X() && str[l-1]=='d')
                f=1;
            else
                f=0;
        }
    }
    else
        f=0;
}
int main()
{
    printf("Enter string: ");
    gets(str);
    l= strlen(str);
    A();
    if(f)
        printf("The string is accepted");
    else
        printf("The string is not accepted");
    return 0;
}
