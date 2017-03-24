#include <cstdio>
#include <iostream>

using namespace std;

long int l, r, k;

void print(long int value)
{
	long int tmp = 1 << (sizeof(value) * 8 - 2);
	cout << value << " binary is : ";
	while (tmp)
	{
		cout << ((value & tmp) == 0 ? 0 : 1);
		tmp >>= 1;
		//cout << tmp << endl;
	}
	cout << endl;
	return ;
}

int main()
{
	// long int a = 123l;
	// long int b = 124l;
	// long int c = a ^ b;
	// print(a);
	// print(b);
	// print(c);
	// print(a ^ c);
	// print(b ^ c);
	// print(a ^ b ^ c);
	
	long long int l = 45;
	long long int r = 100;
	long long int x = 1;
	while (x <= l) x <<= 1;

	print(x);
	if ((x | (x>>1)) <= r) 
	{
		print(l);
		print(x | (x>>1));
		print((x | (x>>1)) ^ l);
	}
	return 0;
}
