#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void doit(int magic[], string &str) 
{
    for (size_t i = 0; i < str.size(); ++i) {
        int a, b, c, d;
        switch (str[i]) {
            case 'C': {
                a = 2; b = 5; c = 3; d = 4;
                break;
            }
            case 'A': {
                a = 4; b = 3; c = 5; a = 2;
                break;
            }
            case 'L': {
                a = 0; b = 1; c = 2; d = 3;
                break;
            }
            case 'R': {
                a = 3; b = 2; c = 1; d = 0;
                break;
            }
            case 'B': {
                a = 4; b = 0; c = 5; d = 1;
                break;
            }
            case 'F': {
                a = 1; b = 5; c = 0; d = 4;
                break;
            }
        }
        
        int t = magic[a];
        magic[a] = magic[b];
        magic[b] = magic[c];
        magic[c] = magic[d];
        magic[d] = t;
    }
}

int main() 
{
    string op;
    while (getline(cin, op)) {
        int magic[] = {1,2,3,4,5,6};
        doit(magic, op);
        for (size_t i = 0; i < 6; ++i) {
            std::cout << magic[i];
        }
        std::cout << endl;
    }
    return 0;
}