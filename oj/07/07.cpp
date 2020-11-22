/*
 * @Author: your name
 * @Date: 2020-11-10 16:29:34
 * @LastEditTime: 2020-11-22 20:52:13
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \07\07.cpp
 */
#include<stdio.h>
#include<stdlib.h>
#include<bitset>
#define _Debug
#ifdef _Debug
#endif
using namespace std;
inline int readNum() // 快速读入
{
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    int v = 0;
    while (ch >= '0' && ch <= '9') {
        v = v * 10 + ch - '0';
        ch = getchar();
    }
    return v;
};
bitset<100000001> gaos(0);
bitset<10001> input(0);
int pivot[10000];
int main()
{
    #ifdef _Debug
    // freopen("7点100组.txt", "r", stdin);
    // freopen("out7.txt", "w", stdout);
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    freopen("test2.txt", "r", stdin);
    freopen("out2.txt", "w", stdout);
    #endif 
    int n, m;//n行m列
    n=readNum();
    m=readNum();
    for(int i=1;i<=n*m;i++)//从1开始
    {
        input[i]=readNum();
    }
    //列方程
    for(int i=1;i<=n*m;i++)
    {
        int j=i-1;
        gaos[j*n*m+i]=1;
        //up
        if(i-2*m > 0)
        {
            gaos[j*n*m+i-2*m]=1;
        }
        if(i-m > 0)
        {
            gaos[j*n*m+i-m]=1;
        }
        //left
        if((i+m-1)%m!=0 && (i+m-2)%m!=0)
        {
            gaos[j*n*m+i-2]=1;
        }
        if((i+m-1)%m!=0)
        {
            gaos[j*n*m+i-1]=1;
        }
        //right
        if((i+1)%m!=1&&(i+2)%m!=1)
        {
            gaos[j*n*m+i+2]=1;
        }
        if((i+1)%m!=1)
        {
            gaos[j*n*m+i+1]=1;
        }
        //down
        if(i+2*m <= n*m)
        {
            gaos[j*n*m+i+2*m]=1;
        }
        if(i+m <= n*m)
        {
            gaos[j*n*m+i+m]=1;
        }
    }
    #ifdef _Debug
    for(int i=0;i<n*m;i++)
    {
        for(int j=0;j<n*m;j++)
        {
            if(gaos.test(i*n*m+j+1))
            {
                printf("1 ");
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
    #endif
    //sovle the equation
    
    //output ans
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(input.test(i*j+j+1))
            {
                printf("1 ");
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
    // if(gaos.test(11))
    //         {
    //             printf("1 ");
    //         }
    //         else
    //         {
    //             printf("0 ");
    //         }
    return 0;
}