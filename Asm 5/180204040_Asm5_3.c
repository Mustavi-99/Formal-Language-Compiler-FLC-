/* CSE 4130 (Fall 2021)                  Assignment - 5                   ID:180204040                      */
#include<stdio.h>
#include<string.h>

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

int main()
{
    printf("Enter string: ");
    gets(checkinp);
    len = strlen(checkinp);
    if(stat())
        printf("The string is accepted.");
    else
        printf("The string is not accepted");

    return 0;
}
