#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;

  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < i; j++) {
      cout << ' ';
    }

    for (int j = 0; j < 2 * (N - i) - 1; j++) {
      cout << '*';
    }

    cout << '\n';
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 0; j < N - i; j++) {
      cout << ' ';
    }

    for (int j = 0; j < 2 * i - 1; j++) {
      cout << '*';
    }

    cout << '\n';
  }

  return 0;
}
