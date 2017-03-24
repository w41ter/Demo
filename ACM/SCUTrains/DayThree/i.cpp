#include <iostream>

using namespace std;

const int N = 1001;
int tree[N], tmp[N];
int max_height, cur_heaght, num, max_num;
int n, k;

int main()
{
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> tree[i];
	
	for (cur_heaght = max_height = 1; cur_heaght < N; cur_heaght++)
	{
		num = 0;
		tmp[0] = cur_heaght;
		if (tree[0] == tmp[0])
			num++;
		
		for (int i = 1; i < n; i++)
		{
			tmp[i] = tmp[i - 1] + k;
			if (tree[i] == tmp[i])
				num++;
			//cout << " " << tmp[i];
		}
		//cout << endl;
		if (num > max_num)
		{
			max_height = cur_heaght;
			max_num = num;
			//cout << "Now max is :" << max_height << " Just Need Change : " << num << endl;
		} 
	}
	
	cout << n - max_num << endl;
	if (n - max_num == 0)
		return 0;
	
	tmp[0] = max_height;
	if (tmp[0] - tree[0] > 0)
		cout << "+ " << 1 << ' ' << tmp[0] - tree[0] << endl;
	else if (tmp[0] - tree[0] < 0)
		cout << "- " << 1 << ' ' << tree[0] - tmp[0] << endl;
	
	for (int i = 1; i < n; ++i)
	{
		tmp[i] = tmp[i - 1] + k;
		if (tmp[i] - tree[i] > 0)
			cout << "+ " << i + 1 << ' ' << tmp[i] - tree[i] << endl;
		else if (tmp[i] - tree[i] < 0)
			cout << "- " << i + 1 << ' ' << tree[i] - tmp[i] << endl;
	}
	
	return 0;
}