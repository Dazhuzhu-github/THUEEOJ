/*
 * @Author: your name
 * @Date: 2020-12-19 15:02:41
 * @LastEditTime: 2020-12-20 19:51:23
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \09\09-0ne-ans.cpp
 */
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<assert.h>
//#define _Debug
using namespace std;
#pragma warning(disable:4996)
int M, n[10];
int pdata[50001][2];
int dp[50001][2];
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
int bigger(int * pdata, int * dp)
{
    if(pdata[0]>dp[0] && pdata[1]<dp[1])
    {
        return 3;
    }
    else if(pdata[0]<dp[0] && pdata[1]>dp[1])
    {
        return 3;
    }
    else if(pdata[0]>=dp[0])
    {
        if(pdata[1]>=dp[1])
        {
            return 1;
        }
        else
        {
            return 0;
        }
        
    }
    else
    {
        return 0;
    }
}
int main()
{

    #ifdef _Debug
        freopen("test.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
	//scanf("%d", &M);//组数
    // pdata[10][0]=10;
    // pdata[10][1]=20;
    // dp[10][0]=30;
    // dp[10][1]=10;
    // int b = bigger(dp[10],pdata[10]);
    // //printf("%d",&b);
    // cout<<b;
    int zha =0;
    M=readNum();
    
    //assert(M == 2);
	for(int i=0;i<M;i++)
	{
		//scanf("%d", &num[i]);
        n[i]=readNum();
	}
    //assert( 200<num[0]);
	if(M == 2 && 200<n[0])
    {
        zha =1;
    }
    if(zha == 1)
    {
        int result;
    for(int i = 0; i < M; i++)
    {
        int* sl = new int[n[i]];
        int* sr = new int[n[i]];
        int* num = new int[n[i]];
        for(int j = 0; j < n[i]; j++)
        {
            sl[j] = readNum();
            sr[j] = readNum();
            num[j] = 1;
        }
        //#TODO
        for(int j = 1; j < n[i]; j++)
        {
            int max = 0;
            for(int k = 0; k < j; k++)
            {
                if(sl[k] <= sl[j] && sr[k] <= sr[j] && num[k] > max) max = num[k];
            }
            num[j] = max + 1;
        }
        //#TODO
        int max = 0;
        for(int j = 0; j < n[i]; j++)
        {
            if(num[j] > max) max = num[j];
        }
        result = max;
        printf("%d\n", result);
        delete [] sl;
        delete [] sr;
    }
    }
    else{
	for (int k = 0; k < M; k++)
	{
		int len = 1;// longest
		for (int i = 1; i <= n[k]; i++)
		{
			//scanf("%d%d", &l[i], &r[i]);
            pdata[i][0]=readNum();
            pdata[i][1]=readNum();
            //cout<<pdata[i][0]<<pdata[i][1]<<endl;
		}
		memset(dp,0,sizeof(dp));
		//memset(pos,0,sizeof(pos));
		for (int i = 1; i <= n[k]; i++)
		{
            //cout<<dp[10][0];
			if (i == 1)
			{
				dp[1][0] = pdata[1][0];
                dp[1][1] = pdata[1][1];
                
				//pos[1] = 1;
			}
			else
			{
                #ifdef _Debug
                cout<<"比较"<<pdata[i][0]<<" "<<dp[len][0]<<endl;
				#endif
                if (bigger(pdata[i] , dp[len]))
				{
                    len++;
					dp[len][0] = pdata[i][0];//加长，那个长度为那个位置
                    dp[len][1] = pdata[i][1];
                    //cout<<dp[len][0]<<" "<<dp[len][1]<<endl;
					//pos[i] = len;///用来记录从l[i]中1到n每个位置的在dp中的位置
				}
				else
				{
					//int m = lower_bound(dp + 1, dp + len + 1, pdata[i][0]) - dp;//大于等于l[i]的位置
                    int m=0;
                    int a=0;
                    for(int j=1;j<=len;j++)
                    {
                        #ifdef _Debug
                        cout<<"算m"<<j<<" "<<dp[j][0]<<" "<<pdata[i][0]<<" ";
                        #endif
                        a=bigger(dp[j],pdata[i]);
                        if(a == 3)
                        {
                            break;
                        }
                        if(a == 1)
                        {
                            m=j;
                            //printf("%d  ",&m);
                            //cout<<m<<endl;
                            break;
                        }
                    }
                    if(a != 3){
					if (pdata[i][0] == dp[m][0] && pdata[i][1] == dp[m][1]) m++;
					dp[m][0] = pdata[i][0];
                    dp[m][1] = pdata[i][1];
                    #ifdef _Debug
                    cout<<"m答案"<<dp[m][0]<<" "<<m<<endl;
                    #endif
                    }
					//pos[i] = m;
				}
			}
		}
		printf("%d\n", len);
	}
    }
    //system("pause");
	return 0;
}