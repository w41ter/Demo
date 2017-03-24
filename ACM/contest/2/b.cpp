#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

struct state {
	char table[10];
	int x, y, g, h, hash;
};

const int dir[4][2] = { {1, 0}, {0, -1}, {0, 1}, {-1, 0}};
const int factor[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };
const int MAX_N = 400000;

int vis[MAX_N], pre[MAX_N], deep[MAX_N], reservse;
char map[10][3];
state beg, en;

bool operator < (const state &l, const state &s) {
	if (l.g + l.h == s.g + s.h) return vis[l.hash] > vis[s.hash];
	else return l.g + l.h > s.g + s.h;
	//return s.h == l.h ? l.g > s.g : l.h > s.h;
}	

int get_hash(state &s) {
	int ans = 0; 
	for (int i = 0; i < 9; ++i) {
		int t = 0;
		for (int j = i + 1; j < 9; ++j) 
			if (s.table[i] > s.table[j]) ++t;
		ans += factor[8 - i] * t;
	}
	return ans;
}

int reservse_order(state &s) {
	int ans = 0;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < i; ++j) 
			if (s.table[i] < s.table[j]) ++ans; 
	}
	return ans % 2;
}

int get_h(state &s) {   //获得估价函数H  
    int ans = 0;  
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
        	int pos = i * 3 + j;
        	if (s.table[pos]) {
        		int c = s.table[pos];
        		ans += abs(map[c][0] - i);
        		ans += abs(map[c][1] - j);
        	}
        }
    }
	return ans;  
}  

inline bool can(state &u) {
	if (0 <= u.x && u.x < 3 && 0 <= u.y && u.y < 3) return true;
	return false;
}

void debug(state tmp){  
    for(int i=0;i<3;i++){  
        for(int j=0;j<3;j++)  
            printf("%d ",tmp.table[i * 3 + j]);  
        printf("\n");  
    }  
    printf("%d %d\n%d %d\n",tmp.x,tmp.y,tmp.g,tmp.h);  
    printf("hash=%d\n",tmp.hash);  
    cout << tmp.h + tmp.g << endl;
}  

int astar() {
	priority_queue<state> que;
	que.push(beg);
	vis[beg.hash] = -2;
	pre[beg.hash] = -1;

	while (!que.empty()) {
		const state u = que.top(); que.pop();
		//debug(u);
		if (u.hash == en.hash) return u.g;
		for (int i = 0; i < 4; ++i) {
			state v = u;
			v.x += dir[i][0];
			v.y += dir[i][1];
			if (can(v)) {
				swap(v.table[v.x * 3 + v.y], v.table[u.x * 3 + u.y]);
				v.hash = get_hash(v);
				v.g++;
				if (vis[v.hash] == -1) {// && reservse_order(v) == reservse) {
					vis[v.hash] = i;
					pre[v.hash] = u.hash;
					v.h = get_h(v);
					que.push(v);
					//debug(v);
				}
			}
		}
	}
	return -1;
}

void output() {
	string ans;
	int n = en.hash;
	while (n != -1) {
		switch (vis[n]) {
			case 0: ans += 'd'; break;
			case 1: ans += 'l'; break;
			case 2: ans += 'r'; break;
			case 3: ans += 'u'; break;
		}
		n = pre[n];
	}
	for (int i = ans.size() - 1; i >= 0; --i) {
		putchar(ans[i]);
	}
	putchar('\n');
}

int main() {
	freopen("test.txt","r",stdin);
	freopen("a.txt","w",stdout);
	int t;
	cin >> t;
	for (int i = 1; i <= t; ++i) {
		memset(vis, -1, sizeof(vis));  
        memset(pre, -1, sizeof(pre)); 
        memset(deep, -1, sizeof(deep)); 

		cin >> beg.table >> en.table;
		for (int i = 0; i < 9; ++i) {
			if (beg.table[i] == 'X') {
				beg.table[i] = 0;
				beg.x = i / 3;
				beg.y = i % 3;
			} else {
				beg.table[i] -= '0';
			}
		}
		for (int i = 0; i < 9; ++i) {
			if (en.table[i] == 'X') {
				en.table[i] = 0;
				en.x = i / 3;
				en.y = i % 3;
			} else {
				en.table[i] -= '0';
			}
			map[en.table[i]][0] = i / 3;
			map[en.table[i]][1] = i % 3;
		}

		beg.g = 0, en.g = 0;
		beg.h = get_h(beg);
		en.h = get_h(en);
		beg.hash = get_hash(beg);
		en.hash = get_hash(en);

		reservse = reservse_order(en);

		cout << "Case " << i << ": ";
		//cout << "except hash is " << en.hash << endl;
		//cout << "now hash is " << beg.hash << endl;
  		cout << astar() << endl;
  		output();
	}

	return 0;
}