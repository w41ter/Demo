#include <cstdio> 
#include <map> 
#include <iostream> 
using namespace std; 
map<long long int , long long int > s1, s2;

int main()
{
	int n, k;
	long long int result = 0;
	long long int x;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		scanf("%I64d", &x);
		if (x % (k * k) == 0)
			result += s2[x / k];
		if (x % k == 0)
			s2[x] += s1[x / k];
		s1[x]++;
	}
	printf("%I64d\n", result);
	return 0;
}
