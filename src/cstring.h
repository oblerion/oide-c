#pragma once
#include <string.h>
int sfind(const char* str,char c)
{
    int ir = -1;
    const int length = strlen(str);
    for(int i=0;i<length;i++)
    {
        if(str[i]==c)
        {
            ir=i;
            break;
        }
    }
    return ir;
}
int sfinds(const char* str,const char* sc)
{
    int ir = -1;
    const int length = strlen(str);
    const int l2 = strlen(sc);
    for(int i=0;i<length;i++)
    {
        for(int j=0;j<l2;j++)
        {
            if(str[i+j]!=sc[j]) break;
            else if(j==l2-1)
            {
                return i;
            }
        }
    }
    return ir;
}
