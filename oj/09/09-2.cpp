/*
 * @Author: your name
 * @Date: 2020-12-17 14:23:44
 * @LastEditTime: 2020-12-17 17:19:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \09\09-2.cpp
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include<string.h>
#define _Debug
using namespace std;

using ld = long double;
const size_t    MaxN = 50005;

const size_t    _M_size = 1 << 28;
char            _M_pool[_M_size], *_M_cur;

inline void* operator new(size_t size)
{ return _M_cur -= size; }
inline void operator delete(void* ptr)
{ }

int N, H[MaxN], V[MaxN];
int H0[MaxN], HN, V0[MaxN], VN;
int F[MaxN], rF[MaxN];
ld  G[MaxN], rG[MaxN];
int Ans;
ld  Cnt;

class segtreenode {
    struct node {
        int    max;
        ld    cnt;
        node    *lc, *rc;

        node(): max(0), cnt(0), lc(nullptr), rc(nullptr){ }
    } *root;
    void modify(node *&o, int l, int r, int pos, int w, ld d)
    {
        if(!o)
            o = new node();
        if(w > o->max)
            o->max = w, o->cnt = d;
        else if(w == o->max)
            o->cnt += d;
        if(l == r)
            return;
        int    m = l + r >> 1;
        if(pos <= m)
            modify(o->lc, l, m, pos, w, d);
        else
            modify(o->rc, m + 1, r, pos, w, d);
    }
    void query(node *o, int l, int r, int tl, int tr, int& w, ld& d)
    {
        if(!o)
            return;
        if(l >= tl && r <= tr) {
            if(w < o->max)
                w = o->max, d = o->cnt;
            else if(w == o->max)
                d += o->cnt;
            return;
        }
        int    m = l + r >> 1;
        if(tl <= m)
            query(o->lc, l, m, tl, tr, w, d);
        if(tr > m)
            query(o->rc, m + 1, r, tl, tr, w, d);
    }
public:
    segtreenode(): root(nullptr) {}
    inline void modify(int pos, int w, ld d)
    { modify(root, 1, VN, pos, w, d); }
    inline void query(int tl, int tr, int& w, ld& d)
    { query(root, 1, VN, tl, tr, w, d); }
} ;
class segtree {
    struct node {
        segtreenode    x;
        node        *lc, *rc;

        node(): x(), lc(nullptr), rc(nullptr){ }
    } *root;
    void modify(node *&o, int l, int r, int posx, int posy, int w, ld d)
    {
        if(!o)
            o = new node();
        (o->x).modify(posy, w, d);
        if(l == r)
            return;
        int    m = l + r >> 1;
        if(posx <= m)
            modify(o->lc, l, m, posx, posy, w, d);
        else
            modify(o->rc, m + 1, r, posx, posy, w, d);
    }
    void query(node *o, int l, int r, int tlx, int trx, int tly, int _try, int& w, ld& d)
    {
        if(!o)
            return;
        if(l >= tlx && r <= trx) {
            (o->x).query(tly, _try, w, d);
            return;
        }
        int    m = l + r >> 1;
        if(tlx <= m)
            query(o->lc, l, m, tlx, trx, tly, _try, w, d);
        if(trx > m)
            query(o->rc, m + 1, r, tlx, trx, tly, _try, w, d);
    }
public:
    segtree(): root(nullptr) { _M_cur = _M_pool + _M_size; }
    inline void modify(int posx, int posy, int w, ld d)
    { modify(root, 1, HN, posx, posy, w, d); }
    inline void query(int tlx, int trx, int tly, int _try, int& w, ld& d)
    { query(root, 1, HN, tlx, trx, tly, _try, w, d); }
} SegTree;

int main()
{
    #ifdef _Debug
    freopen("test1.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif
    int M;
    cin>>M;
    int Num[10] ={0};
    for(int i=0;i<M;i++)
    {
        cin>>Num[i];
    }
    for(int i=0;i<M;i++)
    {
        //cin >> N;
        N = Num[i];
        //cout<<N;
        for(int i = N; i >= 1; --i)
            scanf("%d%d", H + i, V + i), H0[i] = H[i], V0[i] = V[i];
        sort(H0 + 1, H0 + 1 + N), sort(V0 + 1, V0 + 1 + N);
        HN = unique(H0 + 1, H0 + 1 + N) - H0 - 1, VN = unique(V0 + 1, V0 + 1 + N) - V0 - 1;

        for(int i = 1; i <= N; ++i) {
            H[i] = lower_bound(H0 + 1, H0 + 1 + HN, H[i]) - H0, V[i] = lower_bound(V0 + 1, V0 + 1 + VN, V[i]) - V0;
            int w = 0;
            ld  cnt = 1;
            SegTree.query(H[i], HN, V[i], VN, w, cnt);
            F[i] = ++w, G[i] = cnt;
            SegTree.modify(H[i], V[i], w, cnt);
        }
        SegTree = segtree();
        for(int i = N; i; --i) {
            int w = 0;
            ld  cnt = 1;
            SegTree.query(1, H[i], 1, V[i], w, cnt);
            rF[i] = ++w, rG[i] = cnt;
            SegTree.modify(H[i], V[i], w, cnt);
            if(F[i] > Ans)
                Ans = F[i], Cnt = G[i];
            else if(F[i] == Ans)
                Cnt += G[i];
        }

        cout << Ans << endl;
        // memset(H, 0, sizeof(int)*N);
        // memset(V, 0, sizeof(int)*N);
        // memset(H0, 0, sizeof(int)*N);
        // memset(V0, 0, sizeof(int)*N);
        VN = 0;
         memset(F, 0, sizeof(int)*N);
        // memset(rF, 0, sizeof(int)*N);
         memset(G, 0, sizeof(long double)*N);
        // memset(rG, 0, sizeof(long double)*N);
        memset(_M_pool, 0, sizeof(char)*_M_size);
        Cnt = 0;
    }
    
    // for(int i = 1; i <= N; ++i)
    //     if(F[i] + rF[i] - 1 != Ans)
    //         printf("0.00000 ");
    //     else
    //         printf("%.5Lf ", G[i] * rG[i] / Cnt);

    return 0;
}