#include<stdio.h>
#include<cstring>
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
#define _Debug
#ifdef _Debug
#endif
int id_sc[200000];
int sc_num[1001001];
int sc_buc_num[1001];
void Insert()
{
    int id=readNum();
    int score=readNum();
    id_sc[id]=score;
    sc_num[score] += 1;
    sc_buc_num[score/1000] += 1;
    //printf("   %d",score/1000);
    return;
}
void Out()
{
    int id=readNum();
    sc_num[id_sc[id]] -= 1;
    sc_buc_num[id_sc[id]/1000] -= 1;
    id_sc[id]=0;
    //printf("%d",rank);
    return;
}
void Srank()
{
    int id=readNum();
    int rank=0;
    //printf("    %d\n",sc_buc_num[932]);
    for(int i=1000;i>id_sc[id]/1000;i--)//bucket 区间
    {
        rank += sc_buc_num[i];
        
        //printf("   %d\n",rank);
    }
    for(int i=999+(id_sc[id]/1000)*1000;i>id_sc[id];i--)//该区间细算
    {
        rank += sc_num[i];
    }
    printf("%d\n",rank+1);
    return;
}
void Pscore()
{
    int id=readNum();
    int score=id_sc[id]+1;
    while(sc_num[score]==0)
    {
        score++;
    }
    printf("%d\n",score);
    return;
}
void Nscore()
{
    int id=readNum();
    int score=id_sc[id]-1;
    while(sc_num[score]==0)
    {
        score--;
    }
    printf("%d\n",score);
    return;
}
int main()
{
    #ifdef _Debug
    // freopen("7点100组.txt", "r", stdin);
    // freopen("out7.txt", "w", stdout);
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    freopen("test2.txt", "r", stdin);
    freopen("out2.txt", "w", stdout);
    #endif 
    memset(sc_num,0,sizeof(sc_num));
    memset(sc_buc_num,0,sizeof(sc_buc_num));
    int N, M;
    int id, score;
    char ch;
    int bucket;
    //
    N=readNum();
    M=readNum();
    for(int i=0;i<N;i++)
    {
        id=readNum();
        score=readNum();
        id_sc[id]=score;
        sc_num[score] += 1;
        sc_buc_num[score/1000] += 1;
    }
    for(int i=0;i<M;i++)
    {
        ch=readChar();
        switch(ch)
        {
            case 'I' :
                Insert();
                break;
            case 'O' :
                Out();
                break;
            case 'S' :
                Srank();
                break;
            case 'P' :
                Pscore();
                break;
            case 'N' :
                Nscore();
                break;
            default:
                break;
        }
    }
    // for(int i=1000000;i>0;i--){
    //     if(sc_num[i]!=0){
    //         printf("%d\n",sc_num[i]);
    //     }
        
    // }
    
    return 0;
}