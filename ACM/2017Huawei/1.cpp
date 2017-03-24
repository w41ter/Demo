#include <stdio.h>
#include <iostream>

using namespace std;

int reverse(int a) 
{
    int b = 0;
    while (a > 0) {
        b *= 10;
        b += a % 10;
        a /= 10;
    }
    return b;
}

int main() 
{
    int a, b;
    while (scanf("%d,%d", &a, &b) == 2) {
        a = reverse(a);
        b = reverse(b);
        a = a + b;
        if (a < 1 || a > 70000) 
            cout << -1 << endl;
        else 
            cout << a << endl;
    }
    return 0;
}