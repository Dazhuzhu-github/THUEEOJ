/*
 * @Author: your name
 * @Date: 2020-12-26 20:29:35
 * @LastEditTime: 2020-12-26 23:40:38
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
int ansnum;
int K, Nk, Mk, Sk, flag, temp;

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
queue<node> Forward;
vector<node> storage;
queue<node> Backward;
inline void clear(queue<node>& q) {
	queue<node> empty;
	swap(empty, q);
}
void reset()
{
	first.state.reset();
		first.tower_done.reset();
		last.state.reset();
		last.tower_done.reset();
		ansnum = 0;
		anstower.reset();
		flag = 0;
}
void input()
{
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
}
void swapping(int row, int pivot)
{
	//换到主元那行
					tp = A[row];
					A[row] = A[pivot];
					A[pivot] = tp;

					temp = b[row];
					b[row] = b[pivot];
					b[pivot] = temp;
}
void gaos(int a)
{
	b = last.state ^ first.state;//1是要动，0是不动
			int row;// col;
            int pivot = 0;
            int free[30] ={0};
            int times = 0;
            int count = 0;
            //Nk行，Mk列
			//pivot = 0, count = 0, times = 0;
			// for (int i = 0; i < 30; i++) 
            // {
            //     free[i] = 0;
            // }
			for (int col = 0; col < Mk; col++)
			{
				row = pivot;
				while ( !A[row].test(col) && row < Nk) row++;//找主元的列
				if (row != Nk)//Nk是标志数
				{
					swapping(row, pivot);
                    
					for (int i = pivot + 1; i < Nk; i++)//消元
					{
						if (A[i].test(col))
						{
							A[i] = A[pivot] ^ A[i];
							b[i] = b[pivot] ^ b[i];
						}
					}
					pivot++;
				}
				else if (row == Nk)//整列都是0，没主元，count=有多少列是全0
				{
					free[count] = col;
					count++;
				}
			}
			times = 1 << count;//2的count次方，遍历
			ansnum = 31;
			for (int m = 0; m < times; m++) {
                //tp 要遍历数组
				tp.reset();
				int tep = m;
				for (int n = 0; n < count; n++)//十进制转成2进制遍历 0-1-01-001-101....
				{
					tp[free[n]] = tep % 2;
					tep = tep / 2;
				}
				for (int row = Nk - 1; row >= 0; row--)//递推
				{
					int k = 0;
					if (A[row].count() != 0)//当行不等于全0
					{
						while ( !A[row].test(k)) k++;
						int q = k + 1;
						tp[k] = b[row];
						for (q; q < Mk; q++)
                        {
                            if ( A[row].test(q) && tp.test(q)) 
                            {
                                //tp[k] = tp[q] ^ tp[k];
                                tp[k].flip();
                            }
                            
                        }
							
					}
				}
				if (tp.count() < ansnum) 
                {
                    ansnum = tp.count();
                    anstower = tp;
                }
			}
}
int bfs()
{
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
			return ansnum;
}
int main() {
#ifdef _WIN32
	freopen("test.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	
	//scanf("%d", &K);
    K = readNum();
	for (int j = 0; j < K; j++) //K轮
	{	
		reset();
		//scanf("%d%d%d", &Nk, &Mk, &Sk);
        input();
		//高斯消元法
		if (abs(Nk - Mk) < 5)
		{
			gaos(1);	
		}
        //BFS,双向广度优先搜索
		else if (abs(Nk - Mk) >= 5) 
		{
			int b =bfs();
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