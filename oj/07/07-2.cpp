/*
 * @Author: your name
 * @Date: 2020-11-23 09:24:46
 * @LastEditTime: 2020-11-23 18:40:54
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \07\07-2.cpp
 */
/*
 * @Author: your name
 * @Date: 2020-11-10 16:29:34
 * @LastEditTime: 2020-11-23 09:23:14
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \07\07.cpp
 */
#include<stdio.h>
#include<stdlib.h>
#include<bitset>
#include<cstring>
#include<iostream>
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
bitset<10001> output(0);
int pivot[10001];//记录主元
int pivot2[10001];
#ifdef _Debug
void test(int n,int m);
#endif
inline void Gaos(int n,int x,int size)
//n是主元为多少，x是第几行去消,size是n*m
{
    for(int i=0;i<size;i++)//历遍所有行
    {
        if(i!=x && gaos[i*size+n]!=0)
        {
            for(int j=1;j<=size;j++)//消元
            {
                gaos[i*size+j]=gaos[i*size+j]^gaos[x*size+j];
            }
            input[i+1]=input[i+1]^input[x+1];//扩展矩阵
        }
    }
}
int main()
{
    int count=0;//记录秩为多少
    memset(pivot,-1,sizeof(pivot));
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
        if(i-m > 0)
        {
            gaos[j*n*m+i-m]=1;
            if(i-2*m > 0)
            {
                gaos[j*n*m+i-2*m]=1;
            }
        }
        //left
        
        if((i+m-1)%m!=0)
        {
            gaos[j*n*m+i-1]=1;
            if((i+m-2)%m!=0)
            {
                gaos[j*n*m+i-2]=1;
            }
        }
        //right
        
        if((i+1)%m!=1)
        {
            gaos[j*n*m+i+1]=1;
            if((i+2)%m!=1)
            {
                gaos[j*n*m+i+2]=1;
            }
        }
        //down
        
        if(i+m <= n*m)
        {
            gaos[j*n*m+i+m]=1;
            if(i+2*m <= n*m)
            {
                gaos[j*n*m+i+2*m]=1;
            }
        }
    }
    //sovle the equation
    for(int i=1;i<=n*m;i++)//主元
    {
        for(int j=0;j<n*m;j++)//找那行0~n*m-1
        {
            if(pivot[j]<0&&gaos.test(j*n*m+i))
            {
                pivot[j]=i;//i是主元，j是行数
                pivot2[i]=j;
                //count++;
                //cout<<pivot[j];
                Gaos(i,j,n*m);
                break;
            }
        }
    }
    //count ans
    // for(int i=0;i<n*m;i++)//行
    // {
    //     if(pivot[i]!=-1)
    //     {
    //         output[pivot[i]]=input[i+1];
    //     }        
    // }
    test(n,m);
    //output ans
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(pivot[i*m+j]!=-1)
                output[i*m+j+1]=input[pivot2[i*m+j+1]+1];
            if(output.test(i*m+j+1))
            {
                putchar('1');
                putchar(' ');
            }
            else
            {
                putchar('0');
                putchar(' ');
            }
        }
        printf("\n");
    }
    return 0;
}
#ifdef _Debug
void test(int n,int m)
{
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
        cout<<"  "<<input[i]<<"   "<<pivot2[i];
        printf("\n");
    }
    printf("\n");
}
#endif