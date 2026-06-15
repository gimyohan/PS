#include <bits/stdc++.h>

using namespace std;

struct monoDQ {
  deque<pair<int, int>> dq;
  void push(pair<int, int> p) {
    while (!dq.empty() && dq.back().second > p.second)
      dq.pop_back();
    dq.push_back(p);
  }
  int min(int idx) {
    while (!dq.empty() && dq.front().first < idx)
      dq.pop_front();
    return dq.front().second;
  }
  void clear() {
    dq.clear();
  }
};

vector<int> solution(int m, int n, int h, int w, vector<vector<int>> drops) {
  vector<vector<int>> gd(m, vector<int>(n, drops.size()));
  for (int i = 0; i < drops.size(); ++i) {
    auto &d = drops[i];
    gd[d[0]][d[1]] = i;
  }

  vector<vector<int>> mn(m - h + 1, vector<int>(n));
  monoDQ dq;
  for (int j = 0; j < n; ++j) {
    dq.clear();
    for (int i = 0; i < m; ++i) {
      dq.push({i, gd[i][j]});
      if (i - h + 1 >= 0) {
        mn[i - h + 1][j] = dq.min(i - h + 1);
      }
    }
  }

  vector<int> ans({-1, -1, -1});
  for (int i = 0; i < mn.size(); ++i) {
    dq.clear();
    for (int j = 0; j < n; ++j) {
      dq.push({j, mn[i][j]});
      if (j - w + 1 >= 0) {
        int ret = dq.min(j - w + 1);
        if (ans[2] < ret) {
          ans = {i, j - w + 1, ret};
        }
      }
    }
  }
  ans.pop_back();
  return ans;
}
