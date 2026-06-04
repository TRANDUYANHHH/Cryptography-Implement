#include <bits/stdc++.h>

using namespace std;

char XOR(char x, char y) {
  return (x == y ? '0' : '1');
}

string fx(string x) {
  return string(1, XOR(x[2], XOR(x[4], x[5]))) + x.substr(0, x.size() - 1);
}

string fy(string y) {
  return string(1, XOR(y[6], y[7])) + y.substr(0, y.size() - 1);
}

string fz(string z) {
  return string(1, XOR(z[2], XOR(z[7], z[8]))) + z.substr(0, z.size() - 1);
}

char maj(vector<char> a) {
  if(count(a.begin(), a.end(), '1') >= 2) {
    return '1';
  }
  return '0';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string p;
  cin >> p;
  string k;
  cin >> k;
  string x = k.substr(0, 6);
  string y = k.substr(6, 8);
  string z = k.substr(14, 9);
  for(char c : p) {
    char m = maj({x[1], y[2], z[3]});
    if(m == x[1]) {
      x = fx(x);
    }
    if(m == y[2]) {
      y = fy(y);
    }
    if(m == z[3]) {
      z = fz(z);
    }
    char s = XOR(x[5], XOR(y[7], z[8]));
    cout << XOR(c, s);
  }
  return 0;
}
