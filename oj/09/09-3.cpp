/*
 * @Author: your name
 * @Date: 2020-12-17 16:33:52
 * @LastEditTime: 2020-12-17 17:57:39
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \09\09-3.cpp
 */
//#include<bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<vector>
#include<algorithm>
#include<iostream>
#define _Debug
using namespace std;
#define lowbit(x) (x&-x)
#define pid pair<int,double>
#define mkp make_pair
#define fir first
#define sec second
const int maxn=5e4+10;
int n,num;
int a[maxn];
pid ans;
pid f[maxn],g[maxn];
struct Flies{int h,v,id;}fly_pre[maxn],fly[maxn];
inline bool cmp1(Flies x,Flies y){return x.h>y.h;}
inline bool cmp2(Flies x,Flies y){return x.h<y.h;}
inline pid operator+(pid a,pid b){return mkp(a.fir+b.fir,a.sec+b.sec);}
inline pid max(pid a,pid b)
{
	if(a.fir!=b.fir)return a.fir>b.fir?a:b;
	else return mkp(a.fir,a.sec+b.sec);
}
struct Tree_arry1
{
	pid a[maxn];
	inline void clear(int x){for(int i=x;i;i-=lowbit(i))a[i]=mkp(0,0);}
	inline void add(int x,pid k){for(int i=x;i;i-=lowbit(i))a[i]=max(a[i],k);}
	inline pid query(int x){pid res=mkp(0,0);for(int i=x;i<=num;i+=lowbit(i))res=max(res,a[i]);return res;}
}tr1;
void cdq1(int l,int r)
{
	if(l==r)return;
	int mid=(l+r)>>1;
	cdq1(l,mid);
	for(int i=l;i<=r;i++)fly[i]=fly_pre[i];
	sort(fly+l,fly+mid+1,cmp1);sort(fly+mid+1,fly+r+1,cmp1);
	for(int i=l,j=mid+1;j<=r;j++)
	{
		while(i<=mid&&fly[i].h>=fly[j].h)tr1.add(fly[i].v,f[fly[i].id]),i++;
		f[fly[j].id]=max(f[fly[j].id],tr1.query(fly[j].v)+mkp(1,0));
	}
	for(int i=l;i<=mid;i++)tr1.clear(fly[i].v);
	cdq1(mid+1,r);
}
struct Tree_arry2
{
	pid a[maxn];
	inline void clear(int x){for(int i=x;i<=num;i+=lowbit(i))a[i]=mkp(0,0);}
	inline void add(int x,pid k){for(int i=x;i<=num;i+=lowbit(i))a[i]=max(a[i],k);}
	inline pid query(int x){pid res=mkp(0,0);for(int i=x;i;i-=lowbit(i))res=max(res,a[i]);return res;}
}tr2;
void cdq2(int l,int r)
{
	if(l==r)return;
	int mid=(l+r)>>1;
	cdq2(l,mid);
	for(int i=l;i<=r;i++)fly[i]=fly_pre[i];
	sort(fly+l,fly+mid+1,cmp2);sort(fly+mid+1,fly+r+1,cmp2);
	for(int i=l,j=mid+1;j<=r;j++)
	{
		while(i<=mid&&fly[i].h<=fly[j].h)tr2.add(fly[i].v,g[fly[i].id]),i++;
		g[fly[j].id]=max(g[fly[j].id],tr2.query(fly[j].v)+mkp(1,0));
	}
	for(int i=l;i<=mid;i++)tr2.clear(fly[i].v);
	cdq2(mid+1,r);
}
int main()
{
    int M=0;
    cin>>M;
    int Num[10] ={0};
    for(int i=0;i<M;i++)
    {
        cin>>Num[i];
    }
    for(int i=0;i<M;i++)
    {
        //cin >> N;
        n = Num[i];
        for(int i=n;i>=1;i--)scanf("%d%d",&fly_pre[i].h,&fly_pre[i].v),fly_pre[i].id=i,a[++num]=fly_pre[i].v;
        sort(a+1,a+num+1);num=unique(a+1,a+num+1)-(a+1);
        for(int i=1;i<=n;i++)fly_pre[i].v=lower_bound(a+1,a+num+1,fly_pre[i].v)-a;
        for(int i=1;i<=n;i++)f[i]=g[i]=mkp(1,1);
        cdq1(1,n);
        reverse(fly_pre+1,fly_pre+n+1);cdq2(1,n);
        for(int i=1;i<=n;i++)ans=max(ans,f[i]);
        printf("%d\n",ans.fir);
        memset(a, 0, sizeof(int)*n);
        num=0;
    }
    return 0;
}
