/*
 * @Author: your name
 * @Date: 2020-12-26 21:48:22
 * @LastEditTime: 2020-12-26 21:49:10
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \10\bfs.cpp
 */
/*
 * @Author: your name
 * @Date: 2020-12-26 20:29:35
 * @LastEditTime: 2020-12-26 21:41:23
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \10\10-doublebfs.cpp
 */
#include<stdio.h>
#include<queue>
#include<vector>
#include<bitset>
#define _WiN32
#pragma warning (disable:4996)
using namespace std;
//bitset<30> tower[30];
vector<bitset<30> > tower(30);
//bitset<30> A[30];
vector<bitset<30> > A(30);
bitset<30> tp;
bitset<30> b;
bitset<30> anstower;
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
struct node
{
	bitset<30> state;
	bitset<30> tower_done;
}first, last;
inline void clear(queue<node>& q) {
	queue<node> empty;
	swap(empty, q);
}
int main() {
#ifdef _WIN32
	freopen("test.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	queue<node> Forward;
	vector<node> storage;
	queue<node> Backward;
	int ansnum;
	int K, Nk, Mk, Sk, flag, temp;
	//scanf("%d", &K);
    K = readNum();
	for (int j = 0; j < K; j++) //K轮
	{	
		first.state.reset();
		first.tower_done.reset();
		last.state.reset();
		last.tower_done.reset();
		ansnum = 0;
		anstower.reset();
		flag = 0;
		//scanf("%d%d%d", &Nk, &Mk, &Sk);
        Nk = readNum();
        Mk = readNum();
        Sk = readNum();
        //每轮循环的初始化与输入
		for (int i = 0; i < Mk; i++) 
        {
            A[i].reset();
            tower[i].reset();
        }
		for (int i = 0; i < Mk; i++)
		{
			scanf("%d", &temp);
			while (temp != -1)
			{
				//tower[i][temp - 1] = 1;
                tower[i].set(temp-1);
				//A[temp - 1][i] = 1;
                A[temp-1].set(i);
				scanf("%d", &temp);
			}
		}
		for (int i = 0; i < Nk; i++)
		{
			//scanf("%d", &temp);
            int a = readNum();
			first.state[i] = a;
		}
		if (Sk == 1) 
		{
			for (int i = 0; i < Nk; i++)
				last.state[i] = 1;
		};
		
        //BFS,双向广度优先搜索
		if (1) {
            clear(Forward);
			clear(Backward);
			storage.clear();
			Forward.push(first);
			Backward.push(last);
			storage.push_back(last);
			while (!flag)
			{
				temp = Forward.size();
				for (int s = 0; s < temp; s++)
				{
					for (int i = 0; i < Mk; i++)
					{
						node x;
						if (!Forward.front().tower_done.test(i))
						{
							x.tower_done = Forward.front().tower_done;
							x.state = Forward.front().state ^ tower[i];
							x.tower_done[i] = 1;
							Forward.push(x);
							storage.push_back(x);
							for (int k = 0; k < Backward.size(); k++)
							{
								if (x.state == storage[k].state)
								{
									flag = 1;
									anstower = x.tower_done ^ storage[k].tower_done;
									ansnum = anstower.count();
									break;
								}
							}
						}
					}
					Forward.pop();
					if (flag == 1) break;
				}
				if (flag == 1) break;
				storage.erase(storage.begin(), storage.begin() + Backward.size());
				temp = Backward.size();
				for (int s = 0; s < temp; s++)
				{
					for (int i = 0; i < Mk; i++)
					{
						node x;
						if (Backward.front().tower_done[i] == 0)
						{
							x.tower_done = Backward.front().tower_done;
							x.state = Backward.front().state ^ tower[i];
							x.tower_done[i] = 1;
							Backward.push(x);
							storage.push_back(x);
							for (int k = 0; k < Forward.size(); k++)
							{
								if (x.state == storage[k].state)
								{
									flag = 1;
									anstower = x.tower_done ^ storage[k].tower_done;
									ansnum = anstower.count();
									break;
								}
							}
						}
					}
					Backward.pop();
					if (flag == 1) break;
				}
				if (flag == 1) break;
				storage.erase(storage.begin(), storage.begin() + Forward.size());
			}
			
		}
		
		
		printf("%d\n", ansnum);
		for (int i = 0; i < Mk; i++) 
		{
			if (anstower.test(i)) 
            {
                printf("%d ", i + 1);
            }
		}
		printf("%d\n", -1);
	}
// #ifdef _WIN32
// 	fclose(stdin);
// 	fclose(stdout);
// #endif
	return 0;
}