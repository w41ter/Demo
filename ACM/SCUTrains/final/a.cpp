#include <iostream>
#include <string>
#include <cstring>
#include <stack>

using namespace std;

int idx(char c) {
	return c - '0';
}

int get_p(string &a, string &b) {
	int p = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] - '0' > p)
			p = a[i] - '0';
	}
	for (int i = 0; i < b.size(); ++i)
	{
		if (b[i] - '0' > p)
			p = b[i] - '0';
	}
	//cout << "p + 1 " << p + 1 << endl;
	return p + 1;
}

string cal_sum(string &a, string &b, int p) {
	stack<char> stack_;

	int a_len = a.size() - 1, b_len = b.size() - 1, c = 0;
	for (int i = 0; i <= min(a_len, b_len); ++i) {
		int s = idx(a[a_len - i]) + idx(b[b_len - i]) + c;
		//cout << s << endl;
		if (s / p != 0) c = s / p;
		else c = 0;
		//cout << s % p << " " << s / p << " " << c << endl;
		s %= p;
		stack_.push(s + '0');
	}

	int need = max(a_len, b_len) - min(a_len, b_len);
	if (a_len > b_len) {
		for (int i = 0; i < need; ++i) {
			int s = idx(a[need - i - 1]) + c;
			if (s / p != 0) c = s / p;
			else c = 0;
			s %= p;
			stack_.push(s + '0');
		}
	} else if (a_len < b_len) {
		for (int i = 0; i < need; ++i) {
			int s = idx(b[need - i - 1]) + c;
			if (s / p != 0) c = s / p;
			else c = 0;
			s %= p;
			stack_.push(s + '0');
		}
	} 
	if (c != 0) {
		stack_.push(c + '0');
	}

	string result;
	bool s = false;
	while (!stack_.empty()) {
		char c = stack_.top();
		if (!s && c == '0') {
			stack_.pop();
		} else {
			s = true;
			result += c;
			stack_.pop();
		}
	}
	return result;
}

int main() {
	string a, b;
	cin >> a >> b;
	int p = get_p(a, b);
	string result = cal_sum(a, b, p);
	cout << result.size() << endl;// <<  result << endl;
}