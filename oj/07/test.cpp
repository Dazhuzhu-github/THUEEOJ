/*
 * @Author: your name
 * @Date: 2020-11-22 19:26:49
 * @LastEditTime: 2020-11-23 17:05:26
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \07\test.cpp
 */
#include<stdio.h>
#include<stdlib.h>
#include<bitset>
#include<iostream>
using namespace std;
int main()
{
    bitset<2> test(1);
    test[1]=1;
    test[0]=test[0]^test[1];
    cout<<test[0];
    system("pause");
    return 0;
}
// for(int i = 0; i < n; i++)//行
// 	{
// 		for(int j = 1; j <= m; j++)//列
// 		{
// 			int index = toIndex(i, j, m);
// 			for(int temp = i - 2; temp <= i + 2; temp++)
// 			{
// 				if(temp > 0 && temp <= n)
// 				{
// 					gaos[index].set(toIndex(temp, j, m));
// 				}
// 			}
// 			for(int temp = j - 2; temp <= j + 2; temp++)
// 			{
// 				if(temp > 0 && temp <= m)
// 				{
// 					gaos[index].set(toIndex(i, temp, m));
// 				}
// 			}
// 			if(input[index])
// 				gaos[index].set(i);
// 		}
// 	}