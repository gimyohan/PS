#include <bits/stdc++.h>

using namespace std;

extern int excavate(int);

const int WW = 202, INF = 0x7f7f7f7f;

int memo[WW][WW], ans[WW][WW];
int dp(vector<int> &depth, int l, int r) {
  if (l > r)
    return 0;
  if (l == r) {
    ans[l][r] = l;
    return depth[l - 1];
  }
  int &rst = memo[l][r];
  if (rst != -1)
    return rst;
  rst = INF;
  for (int m = l; m <= r; ++m) {
    int ret = max(dp(depth, l, m - 1), dp(depth, m + 1, r)) + depth[m - 1];
    if (rst > ret) {
      rst = ret;
      ans[l][r] = m;
    }
  }
  return rst;
}

int solution(vector<int> depth, int money) {
  memset(memo, -1, sizeof memo);
  int l = 1, r = depth.size();
  for (int i = 1; i <= depth.size(); i++) {
    dp(depth, l, r);
    switch (excavate(ans[l][r])) {
    case -1:
      r = ans[l][r] - 1;
      break;
    case 1:
      l = ans[l][r] + 1;
      break;
    case 0:
      return ans[l][r];
    }
  }
  return 0;
}
