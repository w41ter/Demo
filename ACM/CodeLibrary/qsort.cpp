#include <stdio.h>

void Print(int *a, int length)
{
	printf("try to sort: ");
	for (int i = 0; i < length; i++)
	{
		printf(" %d ", a[i]);
	}
	putchar('\n');
	//fflush(stdin);
}

void Swap(int *left,  int *right)
{
	int tmp = *left;
	*left = *right;
	*right = tmp;
}

void Qsort(int *a, int l, int r)
{
	if (l >= r) return ;
	
	Print(&a[l], r - l + 1);

	int middle = a[l], left = l, right = r + 1;
	while (true)
	{
		while (++left <= r && a[left] < middle);	//	等于号效果不知道怎么样
		while (a[--right] > middle);
		if (left >= right) 
			break;
		Swap(&a[left], &a[right]);
	}
	a[l] = a[right];
	a[right] = middle;
	
	Qsort(a, l, right - 1);
	Qsort(a, right + 1, r);
}

int main()
{
	int b[] = {6, 6, 7, 6, 9, 55, 35, 20, 4, 0, 88, 45};
	int c[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int a[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	Qsort(a, 0, 9);

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", a[i]);
	}
	putchar('\n');
	return 0;
}