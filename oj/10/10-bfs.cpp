/*
 * @Author: your name
 * @Date: 2020-12-25 18:50:08
 * @LastEditTime: 2020-12-26 19:13:05
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \10\10-bfs.cpp
 */
/*
 * @Author: your name
 * @Date: 2020-12-23 18:21:56
 * @LastEditTime: 2020-12-23 18:45:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \10\10-gaos1.cpp
 */
#include<stdio.h>
#include<stdlib.h>
#include<bitset>
#include <vector>
#include<map>
#include<queue>
//Int nSize = mapStudent.size();
/*
map<int, string> mapStudent;  
mapStudent.insert(pair<int, string>(1, "student_one"));  
*/
#define _Debug
#ifdef _Debug
#include<iostream>
#endif
using namespace std;
vector<bitset<30> > tow(30);

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
    scanf("%d",&k);
    for(int i=0;i<k;i++)
    {
        // input the data
        int N,M,S;//标志，塔，配色（0-火，1-冰）
        scanf("%d%d%d",&N,&M,&S);
        int mark[30];// the state of the mark
        
        for(int j=0;j<M;j++)//存那个塔连到了哪个标志
        {
            int flag = 0;
            while (flag != -1)
            {
                scanf("%d",&flag);
                tow[flag-1].set(M);
            }
        }
        for(int j=0;j<M;j++)
        {
            scanf("%d",&mark[j]);
        }
        
        //mark 预处理 0：不变，1：变

        //bfs
        int conditon[30];

        for(int j=0;j<M;j++)//踩几个点
        {

        }

        

        
    }
    return 0;
}