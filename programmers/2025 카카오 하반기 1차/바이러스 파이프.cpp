#include <bits/stdc++.h>

using namespace std;

int simulate(int n, vector<vector<pair<int, int>>> &e, int s, vector<int> &seq){
    vector<bool> vis(n+1);
    queue<int> q;
    vector<int> b(n+1), tmp;
    
    int rst = 1;
    q.push(s);
    vis[s] = true;
    for(auto t:seq){
        tmp.clear();
        while(!q.empty()){
            auto f = q.front(); q.pop();
            for(auto [nxt, typ]: e[f]){
                if(vis[nxt]||t!=typ) continue;
                vis[nxt] = true;
                q.push(nxt);
                rst++;
            }
            b[f]|=(1<<t);
            if(b[f]!=14)tmp.push_back(f);
        }
        for(auto v:tmp)q.push(v);
    }
    return rst;
}

int bt(int n, int k, vector<vector<pair<int, int>>> &e, int s, vector<int> &seq){
    if(k==seq.size()){
        return simulate(n, e, s, seq);
    }
    int rst = 0;
    for(int i=1;i<=3;++i){
        if(seq.empty()||seq.back()!=i){
            seq.push_back(i);
            rst = max(rst, bt(n, k, e, s, seq));
            seq.pop_back();
        }
    }
    return rst;
}

int solution(int n, int infection, vector<vector<int>> edges, int k) {
    vector<vector<pair<int, int>>> e(n+1);
    for(auto &eg:edges){
        e[eg[0]].push_back({eg[1], eg[2]});
        e[eg[1]].push_back({eg[0], eg[2]});
    }
    vector<int> seq;
    return bt(n, k, e, infection, seq);
}
