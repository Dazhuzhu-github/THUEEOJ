#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
#define _Debug
//#define delta 0.4//偷鸡系数
#ifdef _Debug
#endif
int readNum() // 快速读入
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
class Node
{
public:
    int id;//序号 从1开始
    int x;
    int y;
    int xpy;//x+y
    int xmy;//x-y
    int max;//最远
    int min=100000;//最近
    int hamit=0;//hamiton distance
    // Node* Left;
    // Node* Right;
};
int Village()
{
    int delta=0.4;//偷鸡系数
    Node* ans=NULL;
    Node* maxmin=NULL;
    Node* Xpmax = NULL;//x+y max
    Node* Xpmin = NULL;//x+y min
    Node* X_max = NULL;//x-y max
    Node* X_min = NULL;//x-y min
    vector <Node*> data;
    int n=readNum();
    //data input
    //find the max and min
    for(int i=0;i<n;i++)
    {
        Node* p = new Node;
        p->x=readNum();
        p->y=readNum();
        p->id= i+1;
        p->xpy= p->x+p->y;
        p->xmy= p->x-p->y;
        data.push_back(p);
        if(Xpmax == NULL)
        {
            Xpmax = p;
        }
        else
        {
           if(p->xpy>Xpmax->xpy)
           {
               Xpmax=p;
           }
        }
        if(Xpmin == NULL)
        {
            Xpmin = p;
        }
        else
        {
           if(p->xpy<Xpmin->xpy)
           {
               Xpmin=p;
           }
        }
        if(X_max == NULL)
        {
            X_max = p;
        }
        else
        {
           if(p->xmy>X_max->xmy)
           {
               X_max=p;
           }
        }
        if(X_min == NULL)
        {
            X_min = p;
        }
        else
        {
           if(p->xmy<X_min->xmy)
           {
               X_min=p;
           }
        }
    }
    // #ifdef _Debug
    // printf("%d %d\n", Xpmax->x, Xpmax->y);
    // #endif
    //find the farthest distance
    //renew the answer
    ans=data[0];
    maxmin=data[0];
    for(int i=0;i<n;i++)
    {
        int a[4];
        a[0]=abs(Xpmax->x-data[i]->x)+abs(Xpmax->y-data[i]->y);
        a[1]=abs(Xpmin->x-data[i]->x)+abs(Xpmin->y-data[i]->y);
        a[2]=abs(X_max->x-data[i]->x)+abs(X_max->y-data[i]->y);
        a[3]=abs(X_min->x-data[i]->x)+abs(X_min->y-data[i]->y);
        data[i]->max=a[0];
        for(int j=1;j<4;j++)
        {
            if(data[i]->max < a[j])
            {
                data[i]->max=a[j];
            }
        }
        //renew the ans
        if(data[i]->max<ans->max)
        {
            ans=data[i];
        }
        // #ifdef _Debug
        // printf("%d\n",data[i]->max);
        // #endif
        data[i]->min=data[i]->max;
    }
    // #ifdef _Debug
    // printf("%d %d %d %d\n",Xpmax->id,Xpmin->id,X_max->id,X_min->id);
    // #endif
    //选出约束点
    // if(n<5000)
    // {
    //     delta=0;
    // }
    // int xpymax=Xpmax->xpy-(Xpmax->xpy-Xpmin->xpy)*delta;
    // int xpymin=Xpmin->xmy+(Xpmax->xpy-Xpmin->xpy)*delta;
    // int xmymax=X_max->xmy-(X_max->xmy-X_min->xmy)*delta;
    // int xmymin=X_min->xmy+(X_max->xmy-X_min->xmy)*delta;

    //find the closest distance
    ans->hamit=ans->max;
    for(int i=0;i<n;i++)
    {
        // if(data[i]->xpy<xpymax && data[i]->xpy>xpymin &&
        //    data[i]->xmy<xmymax && data[i]->xmy>xmymin);
        {
            for(int j=0;j<n;j++)
            {
                if(i!=j)
                {
                    int min=abs(data[j]->x-data[i]->x)+abs(data[j]->y-data[i]->y);
                    if(min<data[i]->min)
                    {
                        data[i]->min=min;
                        data[i]->hamit=data[i]->max-data[i]->min;
                        if(data[i]->hamit>ans->hamit)
                        {
                            break;
                        }
                    }    
                }
                
            }
            if(data[i]->hamit<ans->hamit)
            {
                ans=data[i];
            }
        }
        
        //printf("%d %d %d\n",data[i]->hamit,data[i]->max, data[i]->min);
    }
    // ans=maxmin;
    // ans->hamit=ans->max-ans->min;
    // for(int i=0;i<n;i++)
    // {
    //     data[i]->hamit=data[i]->max-data[i]->min;
    //     if(data[i]->hamit<ans->hamit)
    //     {
    //         ans=data[i];
    //     }
    //     printf("%d %d\n",data[i]->hamit, data[i]->min);
    // }
    int mmm=ans->id;
    for(int i=0;i<n;i++)
    {
        delete data[i];
    }
    return mmm;
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

    int ans;
    int T;
    T = readNum();
    for(int i=0;i<T;i++)
    {
        ans=Village();
        printf("%d\n",ans);
    }
    #ifdef _Debug
    fclose(stdin);//关闭文件 
    fclose(stdout);//关闭文件
    #endif 
    return 0;
}