#define LOACLFILE

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

const int N = 1000;

class ACMachine
{
public:
	ACMachine() { sz = 1; memset(ch[0], 0, sizeof(ch[0]));}
	int idx(char c)
	{
		if (c < 'a') return c - 'A';
		else return c - 'a';
	}
	
	int ch[N][26];
	int val[N], sz;
	int fail[N];
	
	void insert(const char *s, int v)
	{
		cout << s << endl;
		int u = 0, n = strlen(s);
		for (int i = 0; i < n; ++i)
		{
			int c = idx(s[i]);
			if (!ch[u][c])
			{
				memset(ch[sz], 0, sizeof(ch[sz]));
				val[sz] = 0;
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
		val[u] = v;
	}

	int find(char *t)
	{
		int n = strlen(t);
		int j = 0;
		for (int i = 0; i < n; ++i)
		{
			int c = idx(t[i]);
			while (j && !ch[j][c]) j = fail[c];
			j = ch[j][c];
		}
		return val[j];
	}
	
	int Search(const char *t)
	{
		int len = strlen(t);
		int u = 0;
		for (int i = 0; i < len; ++i)
		{
			int c = idx(t[i]);
			if (!ch[u][c]) return 0;
			else u = ch[u][c];
		}
		return val[u];
	}
};

bool check(int year)
{
	if (year % 400 == 0) return true;
	if (year % 4 == 0 && year % 100 != 0) return true;
	return false;
}

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif
	
	ACMachine tree;
	string mon[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November" , "December"};
	for (int i = 0; i < 12; ++i)
		tree.insert(mon[i].c_str(), i + 1);
	
	int T, case_ = 0, ans = 0;
	cin >> T;
	while (T--)
	{
		case_++;
		ans = 0;
		
		string in1, in2;
		int day1, month1, year1; 
		int day2, month2, year2; 
		char c;
		cin >> in1 >> day1 >> c >> year1;
		cin >> in2 >> day2 >> c >> year2;
		
		month1 = tree.Search(in1.c_str());
		month2 = tree.Search(in2.c_str());
		
		if(year2==year1)  
        {  
            if((year2%400==0)||(year2%4==0&&year2%100!=0))  
              if((month1==1||(month1==2&&day1<=29))&&(month2>2||(month2==2&&day2==29)))  
                ans++;  
        }  
		else
		{
			if((year1%400==0)||(year1%4==0&&year1%100!=0))  
              if((month1==1)||(month1==2&&day1<=29)) ans++;  
			ans+=(year2-1)/4-(year2-1)/100+(year2-1)/400-(year1/4-year1/100+year1/400); 
			 if((year2%400==0)||(year2%4==0&&year2%100!=0))  
              if(month2>2||(month2==2&&day2==29)) ans++;  
		}
		
		cout << "Case #" << case_ << ':' << ans << endl;
	}
	return 0;
}