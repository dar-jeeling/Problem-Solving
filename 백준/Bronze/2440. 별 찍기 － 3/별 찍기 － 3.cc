#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N - i; j++) {
      cout << '*';
    }
    cout << '\n';
  }
  return 0;
}
