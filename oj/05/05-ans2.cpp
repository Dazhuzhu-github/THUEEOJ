#include<cstdio>
#include<queue>
#include<cstring>
#define R register
#define N 20008
using namespace std;
#define _Debug
inline void in(int &x)
{
	int f=1;x=0;char s=getchar();
	while(s>'9' || s<'0'){if(s=='-')f=-1;s=getchar();}
	while(s>='0' && s<='9'){x=x*10+s-'0';s=getchar();}
	x*=f;
}
int head[N],tot,n,m,s,t,k;
int dis[N][15],ans=2147483647;
bool vis[N][15];
struct cod{int u,v,w;}edge[N*6+8];
inline void add(int x,int y,int z)
{
	edge[++tot].u=head[x];
	edge[tot].v=y;
	edge[tot].w=z;
	head[x]=tot;
}
struct coc{
	int u,d,used;
	bool operator <(const coc&a) const 
	{
		return d>a.d;
	}
};
inline void dijkstra()
{
	memset(dis,127,sizeof dis);
	dis[s][0]=0;
	priority_queue<coc>q;
	q.push((coc){s,0,0});
	while(!q.empty())
	{
		int u=q.top().u,now=q.top().used;
		q.pop();
		if(vis[u][now])continue;
		vis[u][now]=true;
		for(R int i=head[u];i;i=edge[i].u)
		{
			if(now<k && !vis[edge[i].v][now+1] && dis[edge[i].v][now+1]>dis[u][now])//当前路径,使用一次免费机会.注意判断 now<k
			{
				dis[edge[i].v][now+1]=dis[u][now];
				q.push((coc){edge[i].v,dis[edge[i].v][now+1],now+1});
			}
			if(!vis[edge[i].v][now] && dis[edge[i].v][now]>dis[u][now]+edge[i].w)//当前路径,不使用免费机会
			{
				dis[edge[i].v][now]=dis[u][now]+edge[i].w;
				q.push((coc){edge[i].v,dis[edge[i].v][now],now});
			}
		}
	}
}
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
	in(n),in(m),in(k);
	in(s),in(t);
	s++;t++;//这里个人习惯不同.我选择记录编号为1~n
	for(R int i=1,x,y,z;i<=m;i++)
	{
		in(x),in(y),in(z);
		x++;y++;
		add(x,y,z);
		add(y,x,z);
	}
	dijkstra();//直接跑dijkstra
	for(R int i=0;i<=k;i++)
		ans=min(ans,dis[t][i]);//到达t我们需要对使用免费机会的情况枚举.取min
	printf("%d 1",ans);
}