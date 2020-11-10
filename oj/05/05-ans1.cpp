#include<cstdio>
#include<cctype>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility> 
#include<functional>
#define _Debug

#ifdef _Debug
#endif
int Read()
{
    int x=0;char c=getchar();
    while(!isdigit(c))
    {
        c=getchar();
    }
    while(isdigit(c))
    {
        x=x*10+(c^48);
        c=getchar();
    }
    return x;
}

using std::priority_queue;
using std::pair;
using std::vector;
using std::make_pair;
using std::greater;

struct Edge
{
    int to,next,cost;//a到b，费用
}edge[3500001];
int cnt=0,head[800005]={0};

void add_edge(int u,int v,int c=0)
{
    //edge[++cnt]= (Edge) {v,head[u],c};
    edge [++cnt].to=v;
    edge[cnt].next=head[u];
    edge[cnt].cost=c;
    head[u]=cnt;
}
int count[800005]={0};//计算有几条路
int dis[800005];//代表到达i的最小花费
bool vis[800005];//代表这个点是否走过
void Dijkstra(int s)
{
    memset(dis,0x4e,sizeof(dis));
    dis[s]=0;
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > points;
    points.push(make_pair(0,s));
    count[s]=1;
    while(!points.empty())
    {
        int u=points.top().second;//点
        points.pop();
        if(!vis[u])//如果没有走过u
        {
            vis[u]=1;
            for(int i=head[u];i;i=edge[i].next)//指向不同条边
            {
                int to=edge[i].to;
                if(dis[to]>dis[u]+edge[i].cost) 
                {
                    dis[to]=dis[u]+edge[i].cost;
                    points.push(make_pair(dis[to],to));
                    count[to] = count[u];
                }
                else if(dis[to] == dis[u]+edge[i].cost)
                {
                    count[to]+=count[u];
                }
                //printf("%d %d %d %d\n",u,to,count[u], count[to]);
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
    int n=Read(),m=Read(),k=Read();
    int u,v,c;
    for(int i=0;i<m;++i)
    {
        u=Read(),v=Read(),c=Read();//建第一层
        add_edge(u,v,c);
        add_edge(v,u,c);
        for(int j=1;j<=k;++j)//建n层的图
        {
            add_edge(u+(j-1)*n,v+j*n);//为0的路
            add_edge(v+(j-1)*n,u+j*n);
            add_edge(u+j*n,v+j*n,c);
            add_edge(v+j*n,u+j*n,c);
        }
        
    }
    // for(int i=0;i<k*n;i++)
    // {
    //     printf("%d %d %d %d\n",edge[i].to,edge[i].next,edge[i].cost,head[i]);
    // }
    int s=Read(),t=Read();
    for(int i=1;i<=k;++i)
	{
		add_edge(t+(i-1)*n,t+i*n);
	}//预防奇葩数据
    Dijkstra(s);
    for(int i=0;i<n;i++);
    printf("%d %d",dis[t+k*n],count[t+k*n]);
    return 0;
}