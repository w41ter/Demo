#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
	freopen("test.txt", "w", stdout);
	int t = 10;
	cout << 10 << endl;
	while (t--) {
		int l = (rand() % 10) + 1, r = (rand() % 10) + 1;
		cout << l << ' ' << r << endl;
		for (int i = 0; i < l; ++i) {
			for (int j = 0; j < r; ++j) {
				if (rand() % 2 == 1) cout << '#';
				else cout << '.';
			}
			cout << endl;
		}
	}
	return 0;
}