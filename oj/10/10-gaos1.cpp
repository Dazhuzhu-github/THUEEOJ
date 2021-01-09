/*
 * @Author: your name
 * @Date: 2020-12-23 18:21:56
 * @LastEditTime: 2020-12-26 19:03:43
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \10\10-gaos1.cpp
 */
#include<stdio.h>
#include<stdlib.h>
#include<bitset>
#include <vector>
#include<queue>
#define _Debug
#ifdef _Debug
#include<iostream>
#endif
using namespace std;
vector<bitset<10001> > gaos(10001);
int main()
{
    #ifdef _Debug
    // freopen("7点100组.txt", "r", stdin);
    // freopen("out7.txt", "w", stdout);
    freopen("test.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    // freopen("test2.txt", "r", stdin);
    // freopen("out2.txt", "w", stdout);
    #endif 
    int k;
    int test[10]={0};
    //scanf("%d",&k);
    for(int i=0;i<k;i++)
    {
        int n,m,s;
        //scanf("%d%d%d",&n,&m,&s);
        
    }
    queue<int*> s;
    for(int i=0;i<10;i++)
    {
        int* ne = new int[10];
        ne[i] = i;
        s.push(ne);
    }
    int * b;
    for(int i=0;i<10;i++)
    {
        b=s.front();
        s.pop();
        for(int j=0;j<10;j++)
            cout<<b[j]<<"   ";
        cout<<endl;
        delete [] b;
    }
    return 0;
}