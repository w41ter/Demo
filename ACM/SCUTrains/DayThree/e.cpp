#include <iostream>

using namespace std;

long int n, m, x, y, z, p;
int px, py;

int swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
	return t;
}

void Output()
{
	int a = px, b = py, tn = n, tm = m;
	
	if (x == 1)
		a = py, b = n + 1 - px, swap(n, m);
	else if (x == 2)
		a = n + 1 - px, b = m + 1 - py;
	else if (x == 3)
		a = m + 1 - py, b = px, swap(n, m);

	px = a, py = b;
	
	if (y == 1)
		a = px, b = m + 1 - py;
	
	px = a, py = b;
	
	if (z == 1)
		a = m + 1 - py, b = px, swap(n, m);
	else if (z == 2)
		a = n + 1 - px, b = m + 1 - py;
	else if (z == 3)
		a = py, b = n + 1 - px, swap(n, m);
	
	px = a, py = b;
	cout << a << " " << b << endl;
	n = tn, m = tm;
}


int main()
{
	cin >> n >> m >> x >> y >> z >> p;
	x %= 4;
	y %= 2;
	z %= 4;
	
	cout << x << " " << y << " " << z << endl;
	
	for (int i = 0; i < p; i++)
	{
		cin >> px >> py;
		Output();
	}
	return 0;
}