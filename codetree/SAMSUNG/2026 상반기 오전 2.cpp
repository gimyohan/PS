#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int NN = 1111, KK = 3e3 + 3;

int Q;
int N;
int S[NN];

void init() {
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    int s;
    cin >> s;
    S[i] = s;
  }
}

void add() {
  int s;
  cin >> s;
  S[++N] = s;
}

void remove() {
  int idx;
  cin >> idx;
  if (S[idx] == 0) {
    cout << -1 << '\n';
  } else {
    cout << S[idx] << '\n';
    S[idx] = 0;
  }
}

vector<int> getList() {
  vector<int> rst;
  rst.reserve(N);
  for (int i = 1; i <= N; ++i) {
    if (S[i]) {
      rst.push_back(S[i]);
    }
  }
  return rst;
}

void query1() {
  int k;
  cin >> k;
  vector<int> lst = getList();
  vector<bool> vis(KK);
  queue<int> q;

  vis[0] = true;
  q.push(0);
  int ans = 0;
  while (!q.empty()) {
    ++ans;
    for (int i = q.size(); i; --i) {
      int cur = q.front();
      q.pop();
      for (auto el : lst) {
        int nxt = cur + el;
        if (nxt >= KK || vis[nxt]) {
          continue;
        }
        if (nxt == k) {
          cout << ans << '\n';
          return;
        }
        vis[nxt] = true;
        q.push(nxt);
      }
    }
  }
  cout << -1 << '\n';
}

void query2() {
  int k;
  cin >> k;
  vector<int> lst = getList(), couple;
  for (auto a : lst) {
    for (auto b : lst) {
      couple.push_back(a + b);
    }
  }
  sort(lst.begin(), lst.end());

  int ans = 0;
  for (auto ab : couple) {
    ans += lst.end() - lower_bound(lst.begin(), lst.end(), k - ab);
  }
  cout << ans << '\n';
}

int main() {
  cin >> Q;
  while (Q--) {
    int q;
    cin >> q;
    switch (q) {
    case 1:
      init();
      break;
    case 2:
      add();
      break;
    case 3:
      remove();
      break;
    case 4:
      query1();
      break;
    case 5:
      query2();
      break;
    }
  }
}
