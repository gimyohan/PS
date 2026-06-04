#include <bits/stdc++.h>

using namespace std;

const int DR[4] = {0, 0, 1, -1};
const int DC[4] = {1, -1, 0, 0};
const int INF = 0x3e3e3e3e;
const int KK = 15;

int H;
int N, M;
int K;

vector<string> G;
vector<vector<int>> P, S;

vector<vector<int>> D;

bool is_valid(int r, int c){return 0<=r&&r<N&&0<=c&&c<M;}
vector<vector<int>> dist_from(int r, int c){
    vector<vector<int>> dst(N, vector<int>(M, INF)); dst[r][c] = 0;
    queue<pair<int, int>> q; q.push({r, c});
    
    while(!q.empty()){
        auto f = q.front(); q.pop();
        int cr = f.first, cc = f.second;
        for(int d=0;d<4;++d){
            int nr = cr+DR[d], nc = cc+DC[d];
            if(!is_valid(nr, nc)||dst[nr][nc]!=INF||G[nr][nc]=='#')continue;
            q.push({nr, nc});
            dst[nr][nc] = dst[cr][cc] + 1;
        }
    }
    
    return dst;
}

int dist_btwn(int a, int b, int c, int d){
    queue<pair<int, int>> q; q.push({a, b});
    vector<vector<bool>> v(N, vector<bool>(M)); v[a][b] = true;
    int rst = 0;
    while(!q.empty()){
        ++rst;
        for(int i=q.size();i;--i){
            auto f = q.front(); q.pop();
            int cr = f.first, cc = f.second;
            for(int dir=0;dir<4;++dir){
                int nr = cr+DR[dir], nc = cc+DC[dir];
                if(!is_valid(nr, nc)||v[nr][nc]||G[nr][nc]=='#')continue;
                if(nr==c&&nc==d)return rst;
                q.push({nr, nc});
                v[nr][nc] = true;
            }
        }
    }
    return INF;
}

int memo[KK][1<<KK];
int tsp(int cur, int bit){
    if(bit==(1<<K)-1) return 0;
    int &rst = memo[cur][bit];
    if(rst!=-1)return rst;
    rst = INF;
    for(int nxt=0;nxt<K;++nxt){
        if(bit&(1<<nxt))continue;
        int cond = 0;
        for(auto el:S[nxt]){
            cond|=(1<<el);
        }
        if((bit&cond)==cond){
            rst = min(rst, tsp(nxt, bit|(1<<nxt)) + D[cur][nxt]);
        }
    }
    return rst;
}

int solution(int h, vector<string> grid, vector<vector<int>> panels, vector<vector<int>> seqs) {
    memset(memo, -1, sizeof memo);
    H = h, N = grid.size(), M = grid[0].size(), K = panels.size();
    G = grid, P = panels;
    
    S.resize(K);
    for(auto seq:seqs){
        S[seq[1]-1].push_back(seq[0]-1);
    }
    
    
    vector<vector<int>> elv;
    for(int r=0;r<N;++r){
        for(int c=0;c<M;++c){
            if(grid[r][c]=='@')elv = dist_from(r, c);
        }
    }
    
    D.assign(K, vector<int>(K, INF));
    for(int i=0;i<K;++i){
        for(int j=i;j<K;++j){
            if(i==j){
                D[i][j] = 0; continue;
            }
            int &d = D[i][j];
            if(panels[i][0]==panels[j][0]){
                d = dist_btwn(panels[i][1]-1, panels[i][2]-1, panels[j][1]-1, panels[j][2]-1);
            }
            else{
                d = abs(panels[i][0]-panels[j][0]) + elv[panels[i][1]-1][panels[i][2]-1] + elv[panels[j][1]-1][panels[j][2]-1];
            }
            D[j][i] = d;
        }
    }
    int answer = tsp(0, 0);
    return answer;
}
