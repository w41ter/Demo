#include <iostream>
#include <cstring>

using namespace std;

int heap_size;
int a[100];

int Parent(int i)
{
	return i / 2;
}

int Right(int i)
{
	return i * 2 + 1;
}

int Left(int i)
{
	return i * 2;
}

void Swap(int i, int max)
{
	int tmp = a[i];
	a[i] = a[max];
	a[max] = tmp;
}

void MaxHeapify(int i)
{
	int l = Left(i);
	int r = Right(i);
	int max = i;
	if (l <= heap_size && a[l] > a[i])
		max = l;
	if (r <= heap_size && a[r] > a[max])
		max = r;
	if (max != i)
	{
		Swap(i, max);
		MaxHeapify(max);
	}
}

void BuildMaxHeapify()
{
	for (int i = Parent(heap_size); i > 0; --i)
		MaxHeapify(i);
}

void HeapSort()
{
	BuildMaxHeapify();
	for (int i = heap_size; i > 1; --i)
	{
		Swap(i, 1);
		heap_size--;
		MaxHeapify(1);
	}
}

int main()
{
	int a1[] = { 0, 0, 1, 0, 0, 0, 0 ,0 , 1 , 23 , 32 };
	memcpy(a, a1, sizeof(a1));
	heap_size = sizeof(a1) / sizeof(int) - 1;
	
	HeapSort();
	
	for (int i = 1; i < sizeof(a1) / sizeof(int); i++)
		cout << a[i] << " ";
	return 0;
}