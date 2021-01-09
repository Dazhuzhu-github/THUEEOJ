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
	scanf("%d", &K);
	for (int j = 0; j < K; j++) //K轮
	{	
		first.state.reset();
		first.tower_done.reset();
		last.state.reset();
		last.tower_done.reset();
		ansnum = 0;
		anstower.reset();
		flag = 0;
		scanf("%d%d%d", &Nk, &Mk, &Sk);
		for (int i = 0; i < Mk; i++) A[i].reset(),tower[i].reset();
		for (int i = 0; i < Mk; i++)
		{
			scanf("%d", &temp);
			while (temp != -1)
			{
				tower[i][temp - 1] = 1;
				A[temp - 1][i] = 1;
				scanf("%d", &temp);
			}
		}
		for (int i = 0; i < Nk; i++)
		{
			scanf("%d", &temp);
			first.state[i] = temp;
		}
		if (Sk == 1) 
		{
			for (int i = 0; i < Nk; i++)
				last.state[i] = 1;
		};
		//每轮循环的初始化与输入
		if (abs(Nk - Mk) >= 5) {
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
						if (Forward.front().tower_done[i] == 0)
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
			clear(Forward);
			clear(Backward);
			storage.clear();
		}
		//BFS,双向广度优先搜索
		else if (abs(Nk - Mk) < 5) {
			b = last.state ^ first.state;
			int row, col, pivot, free[30], times, count;//Nk行，Mk列
			pivot = 0, count = 0, times = 0;
			for (int i = 0; i < 30; i++) free[i] = 0;
			for (col = 0; col < Mk; col++)
			{
				row = pivot;
				while (A[row][col] != 1 && row < Nk) row++;
				if (row != Nk)
				{
					tp = A[row];
					A[row] = A[pivot];
					A[pivot] = tp;
					temp = b[row];
					b[row] = b[pivot];
					b[pivot] = temp;
					for (int i = pivot + 1; i < Nk; i++)
					{
						if (A[i][col] == 1)
						{
							A[i] = A[pivot] ^ A[i];
							b[i] = b[pivot] ^ b[i];
						}
					}
					pivot++;
				}
				else if (row == Nk)
				{
					free[count] = col;
					count++;
				}
			}
			times = 1 << count;
			ansnum = 31;
			for (int m = 0; m < times; m++) {
				tp.reset();
				int tep = m;
				for (int n = 0; n < count; n++)
				{
					tp[free[n]] = tep % 2;
					tep = tep / 2;
				}
				for (int row = Nk - 1; row >= 0; row--)
				{
					int k = 0;
					if (A[row].count() != 0)
					{
						while (A[row][k] != 1) k++;
						int q = k + 1;
						tp[k] = b[row];
						for (q; q < Mk; q++)
							if (A[row][q]) tp[k] = tp[q] ^ tp[k];
					}
				}
				if (tp.count() < ansnum) ansnum = tp.count(), anstower = tp;
			}
		}
		//高斯消元法
		printf("%d\n", ansnum);
		for (int i = 0; i < Mk; i++) 
		{
			if (anstower[i] == 1) printf("%d ", i + 1);
		}
		printf("%d\n", -1);
	}
// #ifdef _WIN32
// 	fclose(stdin);
// 	fclose(stdout);
// #endif
	return 0;
}