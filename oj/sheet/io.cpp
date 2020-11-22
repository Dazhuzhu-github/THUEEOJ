/*
 * @Author: dazhuzhu
 * @Date: 2020-11-16 22:03:34
 * @LastEditTime: 2020-11-16 22:04:36
 * @LastEditors: Please set LastEditors
 * @Description: oj常用IO
 * @FilePath: \oj\sheet\io.cpp
 */

//快读
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
inline char readChar()//快速读入
{
    char ch = getchar();
    while(ch<'A' || ch>'Z')
    {
        ch = getchar();
    }
    return ch;
};