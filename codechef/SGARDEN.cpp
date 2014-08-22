#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>

using namespace std;

#define gc getchar_unlocked
#define MOD 1000000007

int read_int() {
  char c = gc();
  while(c<'0' || c>'9') c = gc();
  int ret = 0;
  while(c>='0' && c<='9') {
    ret = 10 * ret + c - 48;
    c = gc();
  }
  return ret;
}

int main()
{

    return 0;
}