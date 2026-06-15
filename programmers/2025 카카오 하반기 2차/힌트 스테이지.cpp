#include <bits/stdc++.h>

using namespace std;

int N;

int bt(vector<vector<int>> &cost, vector<vector<int>> &hint, vector<int> &item, int stage, int sum) {
  if (stage == N - 1) {
    for (int i = 0; i < N; ++i) {
      sum += cost[i][min(N - 1, item[i])];
    }
    return sum;
  }
  int rst = bt(cost, hint, item, stage + 1, sum);
  for (int i = 1; i < hint[stage].size(); ++i) {
    ++item[hint[stage][i] - 1];
  }
  rst = min(rst, bt(cost, hint, item, stage + 1, sum + hint[stage][0]));
  for (int i = 1; i < hint[stage].size(); ++i) {
    --item[hint[stage][i] - 1];
  }
  return rst;
}

int solution(vector<vector<int>> cost, vector<vector<int>> hint) {
  N = cost.size();
  vector<int> item(N);
  return bt(cost, hint, item, 0, 0);
}
