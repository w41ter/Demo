#include <iostream>
#include <functional>
#include <algorithm>
#include <queue>
#include <stdio.h>

using namespace std;

struct edge
{
	int des;
	int len;
	int money;

	bool operator < (const edge &a)const
	{
		if(len == a.len ) return money > a.money;
		else return len > a.len;
	}
};

struct Vector {
	edge e[10000 + 10];
	int total;
	void clear() { total = -1; }
	void push_back(edge& value) { e[++total] = value;}
	int size() { return total + 1; };
	edge& operator [] (int n) { return e[n]; }
};

Vector vec[100+10];

int bfs(int s, int total, int dest)
{
	priority_queue<edge>que;
	edge temp ;
	temp.des = s;
	temp.len = 0;
	temp.money = 0;

	que.push(temp);

	while(!que.empty())
	{
		temp = que.top(); que.pop();

		if(temp.des == dest) return temp.len;

		int i;
		edge now;

		for(i = 0; i < vec[temp.des].size(); ++i)
		{
			now = vec[temp.des][i];
			now.money += temp.money;

			if(now.money <= total)
			{
				now.len += temp.len;
				que.push(now);
			}
		}
	}

	return -1;
}



int main()
{
	int N,K,R;
	while(scanf("%d %d %d",&K,&N,&R)==3)
	{
		int i;
		int s,d,l,t;

		for(i = 0; i < N; ++i) vec[i].clear();

		for(i = 0; i < R; ++i)
		{
			scanf("%d %d %d %d",&s,&d,&l,&t);
			edge temp;
			temp.des = d;
			temp.len = l;
			temp.money = t;
            
			vec[s].push_back(temp);
		}

		int res = bfs(1,K,N);
		printf("%d\n",res);
	}
	return 0;
}