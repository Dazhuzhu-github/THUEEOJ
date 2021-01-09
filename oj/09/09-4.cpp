/*
 * @Author: your name
 * @Date: 2020-12-17 16:48:15
 * @LastEditTime: 2020-12-17 16:49:31
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \09\09-4.cpp
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include<string.h>
#define _Debug
using namespace std;
int N;
int main()
{
    #ifdef _Debug
    freopen("test1.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif
    int M;
    cin>>M;
    int Num[10] ={0};
    for(int i=0;i<M;i++)
    {
        cin>>Num[i];
    }
    for(int i=0;i<M;i++)
    {
        //cin >> N;
        N = Num[i];
    }
}