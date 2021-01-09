/*
 * @Author: your name
 * @Date: 2020-12-19 16:22:17
 * @LastEditTime: 2020-12-20 20:06:19
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \09\09-One-ans0.cpp
 */
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#pragma warning(disable:4996)
int M, num[10], l[50001], r[50001], dp[50001], pos[50001];
int main()
{
	scanf("%d", &M);
	for(int i=0;i<M;i++)
	{
		scanf("%d", &num[i]);
	}
	
	for (int k = 0; k < M; k++)
	{
		int len = 1;
		for (int i = 1; i <= num[k]; i++)
		{
		//dp[i] = 0; pos[i] = 0;
			scanf("%d%d", &l[i], &r[i]);
		}
		memset(dp,0,sizeof(dp));
		memset(pos,0,sizeof(pos));
		for (int i = 1; i <= num[k]; i++)
		{
			if (i == 1)
			{
				dp[1] = l[1];
				pos[1] = 1;
			}
			else
			{
				if (l[i] >= dp[len])
				{
					dp[++len] = l[i];
					pos[i] = len;///用来记录从l[i]中1到n每个位置的在dp中的位置
				}
				else
				{
					int m = lower_bound(dp + 1, dp + len + 1, l[i]) - dp;
					if (l[i] == dp[m]) m++;
					dp[m] = l[i];
					pos[i] = m;
				}
			}
		}
		printf("%d\n", len);
	}
	return 0;
}