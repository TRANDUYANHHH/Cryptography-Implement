#include <bits/stdc++.h>

using namespace std;

// this is the tiny version of RC4
int N;
vector<int> K;
int S[8], T[8];

string int_to_bin(int x) {
  string s = "";
  for(int i = 2; i >= 0; i--) {
    if(x & (1 << i)) {
      s.push_back('1');
    } else {
      s.push_back('0');
    }
  }
  return s;
}

int bin_to_int(string s) {
  int h = 1;
  int x = 0;
  for(int i = 2; i >= 0; i--) {
    if(s[i] == '1') {
      x += h;
    }
    h *= 2;
  }
  return x;
}

string XOR(string a, string b) {
  string s = "";
  for(int i = 0; i < 3; i++) {
    if(a[i] == b[i]) {
      s.push_back('0');
    } else {
      s.push_back('1');
    }
  }
  return s;
}

int main() {
  cin >> N;
  K.resize(N);
  for(int i = 0; i < N; i++) {
    cin >> K[i];
  }
  string P;
  cin >> P;
  for(int i = 0; i < 8; i++) {
    S[i] = i;
    T[i] = K[i % N];
  }
  for(int i = 0, j = 0; i < 8; i++) {
    j = (j + S[i] + T[i]) % 8;
    swap(S[i], S[j]);
  }
  int i = 0, j = 0;
  for(char c : P) {
    i = (i + 1) % 8;
    j = (j + S[i]) % 8;
    string p = int_to_bin(c - 'a');
    swap(S[i], S[j]);
    int t = (S[i] + S[j]) % 8;
    int k = S[t];
    string np = XOR(int_to_bin(k), p);
    cout << char(bin_to_int(np) + 'A');
  }
}
