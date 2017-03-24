#include <iostream>
using namespace std;
 
///////////////////////////SubMain//////////////////////////////////
int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
	int N, S;
	cin >> N >> S;
	int P = 5000;
	long long costs = 0;
	for (int i = 0; i < N; ++i)
	{
		int C, Y;
		cin >> C >> Y;
		P = min(P + S, C);
		costs += P * Y;
	}
	cout << costs << endl;
#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    system("out.txt");
#endif
    return 0;
}