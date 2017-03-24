#include <iostream>
#include <bitset>
#include <cstring>

using namespace std;

int pos1, pos2;
long long int l, r;
long long int num1[100], num2[100];

void print()
{
	cout << "Now is:" ;
	
	for (int i = pos2 - 1; i >= 0; --i)
	{
		cout << num1[i];
	}
	cout << ' ';
	for (int i = pos2 - 1; i >= 0; --i)
	{
		cout << num2[i];
	}
	cout << endl;
}

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		cin >> l >> r;
		pos1 = 0;
		memset(num1, 0, sizeof(num1));
		memset(num2, 0, sizeof(num2));
		while (l)
		{
			num1[pos1++] = l % 2;
			l >>= 1;
		}
		pos2 = 0;
		while (r)
		{
			num2[pos2++] = r % 2;
			r >>= 1;
		}
		//print();
		bool flag = false;
		int i = pos2 - 1;
		while (i >= 0)
		{
			if (num1[i] != num2[i])
			{
				flag = true;
				break;
			}
			--i;
		}
		if (flag)
		{
			flag = false;
			for (int j = i - 1; j >= 0; --j)
			{
				num1[j] = 1;
				if (num2[j] == 0)
					flag = true;
			}
		}
		
		//print();
		if (flag)
		{
			for (int k = pos2 - 1; k >= 0; k--)
			{
				l <<= 1;
				l += num1[k];
			}
			cout << l << endl;
		}
		else
		{
			for (int k = pos2 - 1; k >= 0; k--)
			{
				r <<= 1;
				r += num2[k];
			}
			cout << r << endl;
		}
	}
	return 0;
}
