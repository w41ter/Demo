#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>

using namespace std;

const int MAX_N = 50000 + 50;

int n, k;
int rank[MAX_N], tmp[MAX_N];

bool compare_sa(int x, int y) {
  if (rank[x] != rank[y]) 
    return rank[x] < rank[y];
  else {
    int rx = x + k <= n ? rank[x + k] : -1;
    int ry = y + k <= n ? rank[y + k] : -1;
    return rx < ry;
  }
}

void construct_sa(string str, int *sa) {
  memset(tmp, 0, sizeof(tmp));
  memset(rank, 0, sizeof(rank));
  n = str.length();
  for (int i = 0; i <= n; ++i) {
    sa[i] = i;
    rank[i] = i < n ? str[i] : -1;
  }
  for (k = 1; k <= n; k *= 2) {
    sort(sa, sa + n + 1, compare_sa);
    tmp[sa[0]] = 0;
    for (int i = 1; i <= n; ++i) {
      tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
    }
    for (int i = 0; i <= n; ++i) 
      rank[i] = tmp[i];
  }
}

void construct_lcp(string s, int *sa, int *lcp) {
  memset(rank, 0, sizeof(rank));
  int n = s.length();
  for (int i = 0; i <= n; ++i) 
    rank[sa[i]] = i;
  int h = 0;
  lcp[0] = 0;
  for (int i = 0; i < n; ++i) {
    int j = sa[rank[i] - 1];
    if (h > 0) 
      h--;
    for (; j + h < n && i + h < n; ++h) {
      if (s[j + h] != s[i + h])
        break;
    }
    lcp[rank[i] - 1] = h;
  }
}

int sa[MAX_N], lcp[MAX_N];

int main() {
  int T;
  cin >> T;
  while (T--) {
    string str;
    cin >> str;
    
    memset(sa, 0, sizeof(sa));
    memset(lcp, 0, sizeof(lcp));
    
    construct_sa(str, sa);
    construct_lcp(str, sa, lcp);
    
    int n = str.length(), sum = 0;
    for (int i = 1; i <= n; ++i) {
      sum += n - sa[i] - lcp[i];
    }
    cout << sum << endl;
    sum = 0;
  }
  return 0;
}