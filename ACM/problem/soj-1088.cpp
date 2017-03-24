#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
	int n;
	while (cin >> n && n) {
		char c[32], tmp[32]; 
		int p = 1, e = 0, olen = sprintf(tmp, "%d", n);
		for (int i = 0; i <= 30; ++i) {
			e = i;
			int length = sprintf(c, "%d", p); 
			//cout <<"i=" << i << " p= " << p << " str is " << c << " length is" << length << endl;
			if (strncmp(c, tmp, olen) == 0 && length > 2 * olen) break;
			p <<= 1;
		}
		cout << e << endl;
	}
	return 0;
}