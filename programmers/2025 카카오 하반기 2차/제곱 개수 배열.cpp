#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll range_sum(vector<int> &arr, ll l, ll r) {
  ll sum = 0, rst = 0;
  for (int i = 0; i < arr.size(); ++i) {
    if (sum + arr[i] >= l) {
      rst += (min(sum + arr[i], r) - max(l, sum + 1) + 1) * arr[i];
      if (r <= sum + arr[i])
        return rst;
    }
    sum += arr[i];
  }
  return rst;
}

vector<ll> solution(vector<int> arr, ll l, ll r) {
  ll d = r - l + 1;
  vector<ll> answer({range_sum(arr, l, r), 0});

  queue<pair<int, int>> p, q;
  for (auto el : arr)
    p.push({el, el}), q.push({el, el});

  while (d) {
    int mn = min(d, (ll)q.front().first);
    d -= mn;
    q.front().first -= mn;
    if (q.front().first == 0)
      q.pop();
  }

  vector<pair<ll, ll>> v;
  while (!p.empty() && !q.empty()) {
    int mn = min(p.front().first, q.front().first);
    v.push_back({mn, -p.front().second + q.front().second});
    p.front().first -= mn;
    q.front().first -= mn;
    if (p.front().first == 0)
      p.pop();
    if (q.front().first == 0)
      q.pop();
  }

  d = r - l + 1;
  ll cur = range_sum(arr, 1, d);
  if (cur == answer[0])
    answer[1]++;

  for (auto [f, s] : v) {
    if (s == 0) {
      answer[1] += (answer[0] == cur) * f;
    } else {
      ll mn = min(cur, cur + f * s), mx = max(cur, cur + f * s);
      if (cur != answer[0] && mn <= answer[0] && answer[0] <= mx && abs(cur - answer[0]) % s == 0)
        answer[1]++;
    }
    cur += f * s;
  }

  return answer;
}
