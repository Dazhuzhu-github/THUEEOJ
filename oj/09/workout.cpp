#include<stdio.h>
#pragma warning(disable:4996)



int readNum() 
{
    char ch = getchar();
    while (ch < '0' or ch > '9') ch = getchar();
    int v = 0;
    while (ch >= '0' and ch <= '9') {
        v = v * 10 + ch - '0';
        ch = getchar();
    }
    return v;
}



int main()
{
    int M = readNum();
    int * n = new int[M];
    for(int i = 0; i < M; i++)
    {
        n[i] = readNum();
    }
    int result;
    for(int i = 0; i < M; i++)
    {
        int* sl = new int[n[i]];
        int* sr = new int[n[i]];
        int* num = new int[n[i]];
        for(int j = 0; j < n[i]; j++)
        {
            sl[j] = readNum();
            sr[j] = readNum();
            num[j] = 1;
        }
        //#TODO
        for(int j = 1; j < n[i]; j++)
        {
            int max = 0;
            for(int k = 0; k < j; k++)
            {
                if(sl[k] <= sl[j] && sr[k] <= sr[j] && num[k] > max) max = num[k];
            }
            num[j] = max + 1;
        }
        //#TODO
        int max = 0;
        for(int j = 0; j < n[i]; j++)
        {
            if(num[j] > max) max = num[j];
        }
        result = max;
        printf("%d\n", result);
        delete [] sl;
        delete [] sr;
    }
    delete [] n;
    return 0;
}