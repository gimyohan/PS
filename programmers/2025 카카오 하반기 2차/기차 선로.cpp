#include <bits/stdc++.h>

using namespace std;

const int DR[4] = {-1, 0, 1, 0};
const int DC[4] = {0, 1, 0, -1};
const int MAP[8] = {0, 10, 5, 15, 9, 3, 6, 12};
int N, M;

bool isValid(int r, int c) {
  if (0 <= r && r < N && 0 <= c && c < M)
    return true;
  else
    return false;
}

bool vis[9][9];
bool check(vector<vector<int>> &gd) {
  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < M; ++c) {
      if (gd[r][c] == 15) {
        for (int d = 0; d < 4; ++d) {
          int nr = r + DR[d], nc = c + DC[d];
          if (!isValid(nr, nc) || gd[nr][nc] <= 0)
            return false;
        }
      }
    }
  }

  int r = 0, c = 0, d = 1;
  memset(vis, 0, sizeof vis);
  while ((r != N - 1 || c != M - 1)) {
    if (!isValid(r, c) || gd[r][c] <= 0)
      return false;
    vis[r][c] = true;
    if (gd[r][c] % 5 == 0) {
      r += DR[d], c += DC[d];
    } else {
      d = (d + 2) % 4;
      for (int i = 0; i < 4; ++i) {
        if (gd[r][c] & (1 << i))
          d -= i;
      }
      d *= -1;
      r += DR[d], c += DC[d];
    }
  }
  vis[r][c] = 1;

  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < M; ++c) {
      if (gd[r][c] > 0 && !vis[r][c])
        return false;
    }
  }

  return true;
}
int bt(vector<vector<int>> &gd, int idx) {
  int r = idx / M, c = idx % M;
  if (r == N - 1 && c == M - 1) {
    return check(gd);
  }
  if (gd[r][c])
    return bt(gd, idx + 1);
  int rst = 0;
  for (int t : MAP) {
    bool good = true;
    for (int d = 0; d < 4 && good; ++d) {
      int nr = r + DR[d], nc = c + DC[d];
      if (t & (1 << d)) {
        if (!isValid(nr, nc) || gd[nr][nc] == -1) {
          good = false;
          continue;
        }
        if ((d == 0 || d == 3) && gd[nr][nc] == 0) {
          good = false;
          continue;
        }
        if (gd[nr][nc] && ~gd[nr][nc] & (1 << ((d + 2) % 4))) {
          good = false;
          continue;
        }
      } else {
        if (isValid(nr, nc) && gd[nr][nc] > 0 && gd[nr][nc] & (1 << ((d + 2) % 4)))
          good = false;
      }
    }
    if (good) {
      gd[r][c] = t;
      rst += bt(gd, idx + 1);
      gd[r][c] = 0;
    }
  }

  return rst;
}

int solution(vector<vector<int>> grid) {
  N = grid.size(), M = grid[0].size();

  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < M; ++c) {
      if (grid[r][c] >= 0) {
        grid[r][c] = MAP[grid[r][c]];
      }
    }
  }
  return bt(grid, 0);
}
