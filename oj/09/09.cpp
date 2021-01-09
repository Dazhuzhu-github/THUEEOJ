/*
 * @Author: your name
 * @Date: 2020-12-17 14:17:21
 * @LastEditTime: 2020-12-17 14:21:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \09\09.cpp
 */
// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
#define _Debug
typedef long long ll;
const int maxn=50010;
ll n,cnt,maxh,maxx,f1[maxn],f2[maxn];
double sum,g1[maxn],g2[maxn];
struct node{ll t,h,v;}s[maxn];
const bool cmpt(node a,node b){return a.t<b.t;}
const bool cmph(node a,node b){return (a.h==b.h)?(a.t<b.t):a.h>b.h;}
set<ll>st;
map<ll,ll>id;
ll max_[maxn*4];
double cnt_[maxn*4];
void clear(ll o,ll l,ll r)
{
    if(!max_[o])return;
    max_[o]=0;
    if(l==r)return;
    int mid=(l+r)>>1;
    clear(o<<1,l,mid);
    clear(o<<1|1,mid+1,r);
}
void update(ll o,ll l,ll r,ll x,ll v,double v2)
{
    if(l>x||x>r)return;
    if(l==r)
    {
        if(max_[o]<v)max_[o]=v,cnt_[o]=0;
        if(max_[o]==v)cnt_[o]+=v2;
        return;
    }
    ll mid=(l+r)>>1;
    update(o<<1,l,mid,x,v,v2);
    update(o<<1|1,mid+1,r,x,v,v2);
    max_[o]=max(max_[o<<1],max_[o<<1|1]);
    cnt_[o]=0;
    if(max_[o]==max_[o<<1])cnt_[o]+=cnt_[o<<1];
    if(max_[o]==max_[o<<1|1])cnt_[o]+=cnt_[o<<1|1];
}
ll query(ll o,ll l,ll r,ll ql,ll qr,double&cntt)
{
    if(ql>r||l>qr){cntt=0;return 0;}
    if(ql<=l&&r<=qr){cntt=cnt_[o];return max_[o];}
    ll mid=(l+r)>>1;
    double cntl=0,cntr=0;
    ll al=query(o<<1,l,mid,ql,qr,cntl),ar=query(o<<1|1,mid+1,r,ql,qr,cntr);
    cntt=0;
    if(mid>=ql&&max(al,ar)==al)cntt+=cntl;
    if(mid<=qr&&max(al,ar)==ar)cntt+=cntr;
    return max(al,ar);
}
void CDQ1(ll l,ll r)
{
    if(l==r)return;
    ll mid=(l+r)>>1;
    sort(s+l,s+r+1,cmpt);
    CDQ1(l,mid);
    sort(s+l,s+mid+1,cmph);
    sort(s+mid+1,s+r+1,cmph);
    clear(1,1,n);
    for(int i=l,j=mid+1;j<=r;j++)
    {
        while(i<=mid&&s[i].h>=s[j].h)update(1,1,n,s[i].v,f1[s[i].t],g1[s[i].t]),i++;
        double cn=0;
        ll t=query(1,1,n,s[j].v,n,cn);
        if(!t)continue;
        if(f1[s[j].t]<t+1)f1[s[j].t]=t+1,g1[s[j].t]=0;
        if(f1[s[j].t]==t+1)g1[s[j].t]+=cn;
    }
    CDQ1(mid+1,r);
}
void CDQ2(ll l,ll r)
{
    if(l==r)return;
    ll mid=(l+r)>>1;
    sort(s+l,s+r+1,cmpt);
    CDQ2(l,mid);
    sort(s+l,s+mid+1,cmph);
    sort(s+mid+1,s+r+1,cmph);
    clear(1,1,n);
    for(int i=l,j=mid+1;j<=r;j++)
    {
        while(i<=mid&&s[i].h>=s[j].h)update(1,1,n,s[i].v,f2[s[i].t],g2[s[i].t]),i++;
        double cn=0;
        ll t=query(1,1,n,s[j].v,n,cn);
        if(!t)continue;
        if(f2[s[j].t]<t+1)f2[s[j].t]=t+1,g2[s[j].t]=0;
        if(f2[s[j].t]==t+1)g2[s[j].t]+=cn;
    }
    CDQ2(mid+1,r);
}
int main()
{
    #ifdef _Debug
    freopen("test.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld%lld",&s[i].h,&s[i].v),s[i].t=i,st.insert(s[i].v),maxh=max(maxh,s[i].h);
    for(set<ll>::iterator it=st.begin();it!=st.end();it++)id[*it]=++cnt;
    for(int i=1;i<=n;i++)s[i].v=id[s[i].v];
    for(int i=1;i<=n;i++)f1[i]=f2[i]=1,g1[i]=g2[i]=1.0;
    CDQ1(1,n);
    for(int i=1;i<=n;i++)maxx=max(maxx,f1[i]);
    for(int i=1;i<=n;i++)if(f1[i]==maxx)sum+=g1[i];
    printf("%lld\n",maxx);
    for(int i=1;i<=n;i++)s[i].t=n-s[i].t+1,s[i].h=maxh-s[i].h+1,s[i].v=cnt-s[i].v+1;
    sort(s+1,s+n+1,cmpt);
    CDQ2(1,n);
    for(int i=1;i<=n;i++)
    {
        if(f1[i]+f2[n-i+1]-1!=maxx)printf("%.5lf ",0.0);
        else printf("%.5lf ",g1[i]*g2[n-i+1]/sum);
    }
    return 0;
}