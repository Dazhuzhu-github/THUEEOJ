/*
 * @Author: your name
 * @Date: 2020-11-23 16:35:49
 * @LastEditTime: 2020-11-23 19:11:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \07\07-3.cpp
 */
/*
 * @Author: your name
 * @Date: 2020-11-10 16:29:34
 * @LastEditTime: 2020-11-23 16:33:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \07\07.cpp
 */
#include<stdio.h>
#include<stdlib.h>
#include<bitset>
#include <vector>
#include<cstring>

#define _Debug
#ifdef _Debug
#include<iostream>
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
//bitset<100000001> gaos(0);
vector<bitset<10001> > gaos(10001);
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
    for(int i=x;i<size;i++)//历遍所有以下行
    {
        if(pivot[i]<0 && gaos[i].test(n))
        {
            gaos[i]^=gaos[x];
            input[i]=input[i]^input[x];//扩展矩阵
        }
    }
}
inline int toIndex(int i, int j,int m)
{
	return m*i + j;
}
int main()
{
    //int count=0;//记录秩为多少
    int size;
    memset(pivot,-1,sizeof(pivot));
    memset(pivot2,-1,sizeof(pivot2));
    #ifdef _Debug
    // freopen("7点100组.txt", "r", stdin);
    // freopen("out7.txt", "w", stdout);
    freopen("test.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    // freopen("test2.txt", "r", stdin);
    // freopen("out2.txt", "w", stdout);
    #endif 
    int n, m;//n行m列
    n=readNum();
    m=readNum();
    size=n*m;
    for(int i=0;i<n*m;i++)//从1开始
    {
        //input[i]=readNum();
        if(readNum())
        {
            input.set(i);
        }
    }
    //列方程
    for(int i = 0; i < n; i++)//行
	{
		for(int j = 0; j < m; j++)//列
		{
			int index = toIndex(i, j, m);
			for(int temp = i - 2; temp <= i + 2; temp++)
			{
				if(temp >= 0 && temp < n)
				{
					gaos[index].set(toIndex(temp, j, m));
				}
			}
			for(int temp = j - 2; temp <= j + 2; temp++)
			{
				if(temp >= 0 && temp < m)
				{
					gaos[index].set(toIndex(i, temp, m));
				}
			}
			// if(input[index])
			// 	gaos[index].set(10000);
		}
	}
    //test(n,m);
    //sovle the equation
    for(int i=0;i<size;i++)//主元,0~n*m-1
    {
        for(int j=0;j<size;j++)//找那行0~n*m-1
        {
            if(pivot[j]<0&&gaos[j].test(i))
            {
                pivot[j]=i;//i是主元，j是行数
                pivot2[i]=j;
                Gaos(i,j,size);
                break;
            }
        }
        //test(n,m);
    }
    //test(n,m);
    //count ans
    for(int i = size - 1; i >= 0; i--)//后往前
	{
		int index = pivot2[i];//所在的行
        //cout<<input[index];
		if(pivot2[i]==-1)//那行没东西
        {
            continue;
        }
		// else if(i==size-1)
        // {
        //     output[i]=input[index];
        // }
        else
        {
            // bitset<1> a(0);
            // a[0]=input[pivot2[i]];
            int count=0;
            output[i]=input[index];
            //cout<<i<<" "<<output[i];
            for(int j=size-1;j>i;j--)
            {
                //cout<<i<<gaos[index][j]<<" "<<output[j];
                if(gaos[index][j] && output[j])
                {
                    output.flip(i);
                    count++;
                }
                //cout<<count<<endl;
            }
            //cout<<i<<" "<<output[i]<<" "<<count<<endl;
            //output[i]=a[0];
        }
		
	}
    //test(n,m);
    //output ans
    int count = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			putchar(output[count] + '0');
			if(j == m - 1)
				putchar('\n');
			else
				putchar(' ');
			count++;
		}
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
            cout<<gaos[i][j]<<" ";
        }
        cout<<"  "<<input[i]<<"   "<<pivot2[i]<<" "<<output[i];
        printf("\n");
    }
    printf("\n");
}
#endif