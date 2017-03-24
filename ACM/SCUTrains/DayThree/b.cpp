#include <iostream>

using namespace std;

long long int stack[51];
long long int sum;
int n;

void cal()
{
	stack[0] = 1;
	for (int i = 1; i < n; i++)
	{
		sum += stack[i - 1];
		stack[i] = sum + 1;
	}
}

int main()
{
	cin >> n;
	cal();
	sum = 0;
	for (int i = 0; i < n; ++i)
	{
		char c;
		cin >> c;
		if (c == 'B')
			sum += stack[i];
	}
	cout << sum;
	return 0;
}