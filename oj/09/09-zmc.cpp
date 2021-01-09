/*
 * @Author: your name
 * @Date: 2020-12-20 17:39:37
 * @LastEditTime: 2020-12-20 18:51:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \09\09-zmc.cpp
 */
#include<stdio.h>
#include<string.h>
//#include<algorithm>
#include<iostream>
#define _Debug
using namespace std;
#pragma warning(disable:4996)
int M, num[10];//M 有几组，num每组几个
int pdata[50001][2];
int cnt[50001][5];//分支的尾巴，这个要清,点+len
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
    //M=readNum();
    cin>>M;
    //cout<<M;
	for(int i=0;i<M;i++)
	{
		scanf("%d", &num[i]);
        //num[i]=readNum();
	}
	
	for (int k = 0; k < M; k++)
	{
        int cntLen=1;
        //int lenMax=1;
		//int len = 1;// longest
		for (int i = 1; i <= num[k]; i++)
		{
			//scanf("%d%d", &l[i], &r[i]);
            pdata[i][0]=readNum();
            pdata[i][1]=readNum();
            //cout<<pdata[i][0]<<pdata[i][1]<<endl;
		}
        memset(cnt,0,sizeof(cnt));//这里还可以优化
        for(int i=1;i<=num[k];i++)
        {
            if(i == 1)
            {
                cnt[1][0]=pdata[1][0];
                cnt[1][1]=pdata[1][1];
                cnt[1][2]=1;
            }
            else
            {
                int flag=1;
                int len=1;
                for(int j=1;j<=cntLen;j++)
                {
                    //cout<<cnt[j][0]<<" "<<cnt[j][1]<<" "<<cnt[j][2]<<" "<<cnt[j][3]<<" "<<cnt[j][4]<<endl;
                    int a = bigger(pdata[i],cnt[j]);
                    if(a == 1)
                    {
                        cnt[j][3]=cnt[i][0];
                        cnt[j][4]=cnt[i][1];
                        cnt[j][0]=pdata[i][0];
                        cnt[j][1]=pdata[i][1];
                        cnt[j][2]++;
                        flag = 0;
                    }
                    else if(a == 0)
                    {
                        if(pdata[i][0]>=cnt[j][3])
                        {
                            if(pdata[i][1]>=cnt[j][4])
                            {
                                cnt[j][3]=pdata[i][0];
                                cnt[j][4]=pdata[i][1];
                                //cnt[j][2]++; 
                                flag = 0;
                            }
                            else
                            {
                                len=cnt[j][2];
                            }
                            
                        }
                        else
                        {
                            len=cnt[j][2];
                        }
                    }
                }
                if(flag)
                {
                    cntLen++;
                    cnt[cntLen][0]=pdata[i][0];
                    cnt[cntLen][1]=pdata[i][1];
                    cnt[cntLen][2] = len;
                }
            }
            //cout<<endl;
        }
        int ans=cnt[1][2];
        for(int i=2;i<=cntLen;i++)
        {
            if(ans<cnt[i][2])
            {
                ans = cnt[i][2];
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}