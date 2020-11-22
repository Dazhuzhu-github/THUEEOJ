/*
 * @Author: your name
 * @Date: 2020-11-10 16:29:34
 * @LastEditTime: 2020-11-16 22:05:10
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \07\07.cpp
 */
#include<stdio.h>
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
int mat[100][100];
int main()
{
    int n, m;
    
    return 0;
}