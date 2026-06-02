#include <bits/stdc++.h>

using namespace std;

// Initial Permutation Table

int IP[] = {
  58, 50, 42, 34, 26, 18, 10, 2,
  60, 52, 44, 36, 28, 20, 12, 4,
  62, 54, 46, 38, 30, 22, 14, 6,
  64, 56, 48, 40, 32, 24, 16, 8,
  57, 49, 41, 33, 25, 17,  9, 1,
  59, 51, 43, 35, 27, 19, 11, 3,
  61, 53, 45, 37, 29, 21, 13, 5,
  63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation Table

int FP[] = {
  40,  8, 48, 16, 56, 24, 64, 32,
  39,  7, 47, 15, 55, 23, 63, 31,
  38,  6, 46, 14, 54, 22, 62, 30,
  37,  5, 45, 13, 53, 21, 61, 29,
  36,  4, 44, 12, 52, 20, 60, 28,
  35,  3, 43, 11, 51, 19, 59, 27,
  34,  2, 42, 10, 50, 18, 58, 26,
  33,  1, 41,  9, 49, 17, 57, 25
};

// Expansion Table

int E[] = {
  32,  1,  2,  3,  4,  5,
   4,  5,  6,  7,  8,  9,
   8,  9, 10, 11, 12, 13,
  12, 13, 14, 15, 16, 17,
  16, 17, 18, 19, 20, 21,
  20, 21, 22, 23, 24, 25,
  24, 25, 26, 27, 28, 29,
  28, 29, 30, 31, 32,  1
};

// P-Box

int P[] = {
  16,  7, 20, 21,
  29, 12, 28, 17,
   1, 15, 23, 26,
   5, 18, 31, 10,
   2,  8, 24, 14,
  32, 27,  3,  9,
  19, 13, 30,  6,
  22, 11,  4, 25
};

// S-Boxes

int SBOX[][4][16] = {
  // S-box 1
  {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 9},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
  },
  // S-box 2
  {
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
    {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
    {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
    {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
  },
  // S-box 3
  {
    {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
    {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
    {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
    {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
  },
  // S-box 4
  {
    {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
    {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
    {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
    {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
  },
  // S-box 5
  {
    {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
    {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
    {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
    {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
  },
  // S-box 6
  {
    {13, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
    {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
    {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
    {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
  },
  // S-box 7
  {
    {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
    {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
    {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
    {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
  },
  // S-box 8
  {
    {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
    {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
    {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
    {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
  }
};

// Permuted Choice 1 64 bits -> 56 bits

int PC1[] = {
  57, 49, 41, 33, 25, 17,  9,
   1, 58, 50, 42, 34, 26, 18,
  10,  2, 59, 51, 43, 35, 27,
  19, 11,  3, 60, 52, 44, 36,
  63, 55, 47, 39, 31, 23, 15,
   7, 62, 54, 46, 38, 30, 22,
  14,  6, 61, 53, 45, 37, 29,
  21, 13,  5, 28, 20, 12,  4
};

int PC2[] = {
  14, 17, 11, 24,  1,  5,
   3, 28, 15,  6, 21, 10,
  23, 19, 12,  4, 26,  8,
  16,  7, 27, 20, 13,  2,
  41, 52, 31, 37, 47, 55,
  30, 40, 51, 45, 33, 48,
  44, 49, 39, 56, 34, 53,
  46, 42, 50, 36, 29, 32
};

int SHIFT[] = {
  1, 1, 2, 2, 2, 2, 2, 2,
  1, 2, 2, 2, 2, 2, 2, 1
};

string hex_to_bin(string s) {
  string ans = "";
  for(char c : s) {
    int x;
    if(c >= 'A' && c <= 'Z') {
      x = 10 + (c - 'A');
    } else {
      x = c - '0';
    }
    string t = "";
    for(int i = 3; i >= 0; i--) {
      if(x & (1 << i)) {
        t.push_back('1');
      } else {
        t.push_back('0');
      }
    }
    ans += t;
  }
  return ans;
}

string bin_to_hex(string s) {
  string ans = "";
  for(int i = 0; i < (int) s.size(); i += 4) {
    string t = s.substr(i, 4);
    int x = 0;
    int h = 1;
    for(int j = 3; j >= 0; j--) {
      if(t[j] == '1') {
        x += h;
      }
      h *= 2;
    }
    if(x < 10) {
      ans += to_string(x);
    } else {
      ans += char('A' + (x - 10));
    }
  }
  return ans;
}

int bin_to_int(string s) {
  int h = 1;
  int x = 0;
  for(int i = (int) s.size() - 1; i >= 0; i--) {
    if(s[i] == '1') {
      x += h;
    }
    h *= 2;
  }
  return x;
}

string int_to_bin(int x) {
  string ans = "";
  while(x) {
    ans += to_string(x % 2);
    x /= 2;
  }
  while((int) ans.size() < 4) {
    ans += "0";
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

string make_ip(string s) {
  string ans = "";
  for(int x : IP) {
    ans.push_back(s[x - 1]);
  }
  return ans;
}

string pc1(string k) {
  string ans = "";
  for(int x : PC1) {
    ans.push_back(k[x - 1]);
  }
  return ans;
}

string pc2(string k) {
  string ans = "";
  for(int x : PC2) {
    ans.push_back(k[x - 1]);
  }
  return ans;
}

string left_shift(string s, int x) {
  return s.substr(x) + s.substr(0, x);
}

string gen_key(string s, int round) {
  string l = s.substr(0, 28);
  string r = s.substr(28);
  l = left_shift(l, SHIFT[round - 1]);
  r = left_shift(r, SHIFT[round - 1]);
  return l + r;
}

string expand(string s) {
  string ans = "";
  for(int x : E) {
    ans.push_back(s[x - 1]);
  }
  return ans;
}

string XOR(string a, string b) {
  assert(a.size() == b.size());
  string ans = "";
  for(int i = 0; i < (int) a.size(); i++) {
    if(a[i] == b[i]) {
      ans.push_back('0');
    } else {
      ans.push_back('1');
    }
  }
  return ans;
}

string sbox(string s) {
  string ans = "";
  for(int i = 0; i < 48; i += 6) {
    string t = s.substr(i, 6);
    string cc = t.substr(1, 4);
    string rr = string(1, t[0]) + string(1, t[5]);
    int row = bin_to_int(rr);
    int col = bin_to_int(cc);
    ans += int_to_bin(SBOX[i / 6][row][col]);
  }
  return ans;
}

string pbox(string s) {
  string ans = "";
  for(int x : P) {
    ans.push_back(s[x - 1]);
  }
  return ans;
}

string fp(string s) {
  string ans = "";
  for(int x : FP) {
    ans.push_back(s[x - 1]);
  }
  return ans;
}

int main() {
  string p, k;
  cin >> p >> k;
  cout << "Plaintext(hex) p: " << p << '\n';
  cout << "Key(hex) k: " << k << '\n';
  p = hex_to_bin(p);
  k = hex_to_bin(k);
  p = make_ip(p);
  k = pc1(k);
  for(int i = 1; i <= 16; i++) {
    k = gen_key(k, i);
    string key = pc2(k);
    string l = p.substr(0, 32);
    string r = p.substr(32);
    string nl = r;
    string nr;
    r = expand(r);
    r = XOR(r, key);
    r = sbox(r);
    r = pbox(r);
    nr = XOR(r, l);
    p = nl + nr;
  }
  string tp = p.substr(32) + p.substr(0, 32);
  p = fp(tp);
  cout << "ciphertext(hex): " << bin_to_hex(p) << '\n';
}
