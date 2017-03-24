#include <cstdlib> 
#include <cstring> 
#include <iostream> 
#include <algorithm> 
using namespace std; 

const int maxn = 5000 + 5; 
pair<int, int> sc[maxn]; 
int main() 
{ 
	int n; 
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> sc[i].first >> sc[i].second;
	sort(sc, sc + n); 
	int prev = min(sc[0].first, sc[0].second);
	for (int i = 1; i < n; i++) 
	{ 
		int tmp = min(sc[i].first, sc[i].second); 
		prev = (tmp < prev ? max(sc[i].first, sc[i].second) : tmp); 
	} 
	cout << prev;
	return 0; 
}