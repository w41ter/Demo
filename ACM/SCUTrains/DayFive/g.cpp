#include <iostream>
#include <vector>

using namespace std;

struct Tree
{
	int l;
	int r;
	int var;
};

const int N = 110000;
struct Tree tree[N * 10];
struct Tree in[N];
vector<int> table;
void build(int o, int l, int r)
{
	tree[o].l = l;
	tree[o].r = r;
	tree[o].var = 0;
	if (l == r)
		return ;
	
	int mid = l + (r - l) / 2;  
    build(o + o, l, mid);  
    build(o + o + 1, mid + 1, r);  
}

void Update(int o  , int l, int r, int val)
{
	if (tree[o].l == l && tree[o].r == r)
	{
		tree[o].var |= val;
		return ;
	}
	
	int mid = tree[o].l + (tree[o].r - tree[o].l) / 2;
	if (mid < l)
		Update(o + o + 1, l, r, val);
	else if (mid >= r)
		Update(o + o, l, r, val);
	else
	{
		Update(o + o, l, mid, val);  
        Update(o + o + 1, mid + 1, r, val);  
	}
}

int query(int o, int l, int r)
{
	if (tree[o].l == l && tree[o].r == r)
		return tree[o].var;
	int mid = tree[o].l + (tree[o].r - tree[o].l) / 2;
	if (mid < l)
		return query(o + o + 1, l, r);
	else if (mid >= r)
		return query(o + o, l, r);
	else
	{
		return query(o + o, l, mid) & query(o + o + 1, mid + 1, r);
	}
}

void Solve(int o)
{
	if (o != 1)
		tree[o].var |= tree[o / 2].var;
	if (tree[o].l != tree[o].r)
	{
		Solve(o + o);
		Solve(o + o + 1);
		return ;
	}
	table.push_back(tree[o].var);
}

int main()
{
	int n, k, flag = 1;
	cin >> n >> k;
	build(1, 1, n);
	for (int i = 0; i < k; ++i)
	{
		cin >> in[i].l >> in[i].r >> in[i].var;
		Update(1, in[i].l, in[i].r, in[i].var);
	}
	
    for(int i = 0; i < k; i++)  
    {  
        if(query(1, in[i].l, in[i].r) != in[i].var)  
        {  
            flag = 0; 
            break;  
        }  
    }  

    Solve(1);  
    if(flag)
	{  
        cout << "YES" << endl;  
        for(int i = 0; i < table.size(); i++)  
            cout << table[i] << ' ';  
    }  
    else  
        cout << "NO" << endl;  
    return 0;  
}
