#include <cstring>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;

const int DR[4] = {0, 1, 0, -1};
const int DC[4] = {1, 0, -1, 0};

const int NN = 22, MM = 11, KK = 11;
int N, M, K;

struct Cell {
  bool wall;
  int jammer, robot;
} GD[NN][NN];

struct Jammer {
  int r, c;
  int crit, curr, tmp;
  bool active;
} jammer[MM];

struct Robot {
  int r, c;
  int emp;
  bool fin;
} robot[KK];

bool isValid(int r, int c) {
  return 0 <= r && r < N && 0 <= c && c < N;
}

bool vis[NN][NN];
bool step1(int id) {
  vector<pair<int, int>> q;
  memset(vis, 0, sizeof vis);

  int r = robot[id].r, c = robot[id].c, dir = -1;
  vis[N - 1][N - 1] = true;
  q.push_back({N - 1, N - 1});

  while (!q.empty()) {
    int sz = q.size();
    vector<pair<int, int>> tmp;
    for (int d = 0; d < 4; ++d) {
      for (int i = 0; i < sz; ++i) {
        int nr = q[i].first + DR[(d + 2) % 4], nc = q[i].second + DC[(d + 2) % 4];
        if (!isValid(nr, nc) || vis[nr][nc] || GD[nr][nc].wall) {
          continue;
        }
        if (nr == r && nc == c) {
          dir = d;
        }
        vis[nr][nc] = true;
        if (GD[nr][nc].robot) {
          continue;
        }
        tmp.push_back({nr, nc});
      }
    }
    q = tmp;
  }

  if (dir == -1) {
    return false;
  }

  int nr = r + DR[dir], nc = c + DC[dir];
  GD[r][c].robot = 0;
  robot[id].r = nr, robot[id].c = nc;
  if (nr == N - 1 && nc == N - 1) {
    robot[id].fin = true;
    return true;
  }
  GD[nr][nc].robot = id;
  return false;
}

void step2() {
  for (int i = 1; i <= K; ++i) {
    jammer[i].curr += 10;
  }
}

void step3() {
  queue<int> q;
  for (int i = 1; i <= K; ++i) {
    if (jammer[i].crit <= jammer[i].curr) {
      jammer[i].active = true;
      q.push(i);
    }
  }

  while (!q.empty()) {
    int i = q.front();
    q.pop();
    int r = jammer[i].r, c = jammer[i].c;
    if (GD[r][c].robot) {
      int j = GD[r][c].robot;
      robot[j].emp += jammer[i].crit;
      if (robot[j].emp >= 20) {
        robot[j].fin = true;
      }
    }
    for (int d = 0; d < 4; ++d) {
      int nr = r + DR[d], nc = c + DC[d];
      for (int l = 1; isValid(nr, nc) && !GD[nr][nc].wall; ++l, nr += DR[d], nc += DC[d]) {
        if (GD[nr][nc].jammer) {
          int j = GD[nr][nc].jammer;
          jammer[j].tmp += jammer[i].crit >> l;
          if (!jammer[j].active && jammer[j].curr + jammer[j].tmp >= jammer[j].crit) {
            jammer[j].active = true;
            q.push(j);
          }
        }
        if (GD[nr][nc].robot) {
          int j = GD[nr][nc].robot;
          robot[j].emp += jammer[i].crit >> l;
          if (robot[j].emp >= 20) {
            robot[j].fin = true;
          }
        }
      }
    }
  }
}

void step4() {
  for (int i = 1; i <= M; ++i) {
    robot[i].emp = 0;
  }
  for (int i = 1; i <= K; ++i) {
    jammer[i].tmp = 0;
    if (jammer[i].active) {
      jammer[i].active = false;
      jammer[i].curr = 0;
    }
  }
}

int main() {
  cin >> N >> M >> K;
  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < N; ++c) {
      cin >> GD[r][c].wall;
    }
  }
  for (int i = 1; i <= M; ++i) {
    int r, c;
    cin >> r >> c;
    GD[r][c].robot = i;
    robot[i].r = r, robot[i].c = c;
  }
  for (int i = 1; i <= K; ++i) {
    int r, c, p;
    cin >> r >> c >> p;
    GD[r][c].jammer = i;
    jammer[i].r = r, jammer[i].c = c;
    jammer[i].crit = p, jammer[i].curr = 0;
  }

  int ans[MM];
  memset(ans, -1, sizeof ans);
  for (int t = 1; t <= 100; ++t) {
    for (int i = 1; i <= M; ++i) {
      if (!robot[i].fin) {
        if (step1(i)) {
          ans[i] = t;
        }
      }
    }
    step2();
    step3();
    step4();
  }

  for (int i = 1; i <= M; ++i)
    cout << ans[i] << '\n';
}
