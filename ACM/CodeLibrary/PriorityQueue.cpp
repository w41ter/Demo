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
	//cout << "Swap : " << a[max] << " and " << a[i] << endl;
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

int HeapMaxmum()
{
	return a[1];
}

int HeapExtractMax()
{
	if (heap_size < 1)
		return -1;
	
	int max = a[1];
	a[1] = a[heap_size];
	heap_size--;
	MaxHeapify(1);
	return max;
}

bool HeapIncreaseKey(int i, int value)
{
	if (value <= a[i])
		return false;
	
	a[i] = value;
	while (i > 1 && a[Parent(i)] < a[i])
	{
		Swap(i, Parent(i));
		i = Parent(i);
	}
	return true;
}

bool HeapDecreaseKey(int i, int value)
{
	if (value >= a[i])
		return false;
	
	a[i] = value;
	MaxHeapify(i);
	return true;
}

void MaxHeapInsert(int value)
{
	heap_size++;
	a[heap_size] = -1;
	if (!HeapIncreaseKey(heap_size, value))
		cout << "Inser false" << endl;
}

int main()
{
	heap_size = 0;
	a[0] = 0;
	
	MaxHeapInsert(32);
	MaxHeapInsert(23);
	MaxHeapInsert(55);
	MaxHeapInsert(1);
	MaxHeapInsert(133);
	HeapIncreaseKey(3, 3223);
	for (int i = heap_size; i > 0; i--)
		cout << HeapExtractMax() << " ";
		
	return 0;
}