#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
long long int array[4];
long long int last = 3;

void init() {
    array[0] = 1;
    array[1] = 2;
    array[2] = 4;
    last = 3;
}

void change(long long int tmp) {
    if (tmp == 1) {
        array[0] = 0;
        array[1] = 1;
        array[2] = 2;
    } else if (tmp == 2) {
        array[1] = 0;
        array[2] = array[0] + 1;
    } else if (tmp == 3) {
        array[2] = 0;
    }
}

typedef vector<long long int> vec;
typedef vector<vec> mat;

mat mul(mat &A, mat &B) {
    mat C(A.size(), vec(B[0].size()));
    for (int i = 0; i < A.size(); ++i) {
        for (int k = 0; k < B.size(); ++k) {
            for (int j = 0; j < B[0].size(); j++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

mat pow(mat A, long long int n) {
    mat B(A.size(), vec(A.size()));
    for (int i = 0; i < A.size(); ++i) {
        B[i][i] = 1;
    }
    while (n > 0) {
        if (n & 1) B = mul(B, A);
        A = mul(A, A);
        n >>= 1ll;
    }
    return B;
}

void mut(long long int tmp) {
    if (tmp == last) return;
    long long int C[3] = { 0 };
    mat A(3, vec(3));
    A[0][0] = 1; A[0][1] = 1; A[0][2] = 1;
    A[1][0] = 1; A[1][1] = 0; A[1][2] = 0;
    A[2][0] = 0; A[2][1] = 1; A[2][2] = 0;
    
    A = pow(A, tmp - last);
    
    //cout << array[0] << array[1] << array[2] << endl;
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            //cout << A[i][j] << ' ';
            C[i] = (C[i] + A[i][j] * array[2 - j]) % MOD;
        }
        //cout << endl;
        //cout << C[i] << endl;
    }
    array[0] = C[2];
    array[1] = C[1];
    array[2] = C[0];
    last = tmp;
}

void cal(long long int tmp) {
    mut(tmp);
    array[2] = 0;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long int n;
        int m;
        cin >> n >> m;
        init();
        for (int i = 0; i < m; ++i) {
            long long int tmp;
            cin >> tmp;
            if (tmp <= 3) {
                change(tmp);
            } else {
                cal(tmp);
            }
        }
        if (n <= 3) {
            cout << array[n - 1] << endl;
        } else {
            mut(n);
            cout << array[2] << endl;
        }
    }
}