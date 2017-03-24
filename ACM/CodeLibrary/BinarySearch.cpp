#include <iostream>
using namespace std;

int BinarySearch(int *a, int length, int key)
{
	int left = 0, right = length - 1, mid = (right - left) / 2 + left;
	while (left <= right)
	{
		if (a[mid] < key) left = mid + 1;
		else if (a[mid] > key) right = mid - 1;
		else return mid;
		
		mid = (right - left) / 2 + left;
	}
	return -1;
}

int main() 
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 10};
	cout << "Result is :" << BinarySearch(a, sizeof(a) / sizeof(int), 1) << endl;
	return 0;
}