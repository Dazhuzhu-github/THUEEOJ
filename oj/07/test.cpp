/*
 * @Author: your name
 * @Date: 2020-11-22 19:26:49
 * @LastEditTime: 2020-11-22 21:43:34
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