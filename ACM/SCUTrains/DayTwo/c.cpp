#include <iostream>

using namespace std;

int n, food[100000 + 5];
char visit[100000 + 5];

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> food[i];
	
	int left = 1, left_size = food[0], right_size = food[n-1], right = 1, l = 1, r = n-2;
	for (int i = 0; i < n; i++)
	{
		if (left_size <= right_size && visit[l] != 1)
		{  
            left_size += food[l];  
            visit[l] = 1;  
			left++;
			l++;
		}  
        else if (left_size > right_size && visit[r] != 1)  
        {  
            right_size += food[r];
			visit[r] = 1;
			r--;
            right++; 
        }  
	}
	if (n == 1)  
		cout << "1 0\n";  
    else if(n==2)  
		cout << "1 1\n";
    else  
		cout << left << " " << right;  
    return 0;  
}