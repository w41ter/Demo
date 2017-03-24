#include <iostream>
#include <cstring>
#include <stack>
#include <string>

using namespace std;

stack<char> s;

int main()
{
	string str;
	cin >> str;
	for (auto i : str)
	{
		if (s.empty()) s.push(i);
		else if (s.top() == i) s.pop();
		else s.push(i);
	}
	
	cout << (s.empty() ? "Yes" : "No");
	return 0;
}
