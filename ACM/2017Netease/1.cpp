#include <iostream>
#include <string>

using namespace std;

int main() {
    string str;
    while (std::getline(cin, str)) {
        if (str.empty()) {
            cout << 0 << endl;
            continue;
        }

        int left = str[0] - '0';
        int idx = 1, length = str.size();
        while (idx < length) {
            switch (str[idx++]) {
                case '+': {
                    int right = str[idx++] - '0';
                    left += right;
                    break;
                }
                case '-': {
                    int right = str[idx++] - '0';
                    left -= right;
                    break;
                }
                case '*': {
                    int right = str[idx++] - '0';
                    left *= right;
                    break;
                }
            }
        }
        cout << left << endl;
    }
    return 0;
}