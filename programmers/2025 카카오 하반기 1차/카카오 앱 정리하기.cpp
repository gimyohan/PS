#include <bits/stdc++.h>

using namespace std;

const int DR[4] = {0, 1, 0, -1};
const int DC[4] = {1, 0, -1, 0};

int N, M;
struct App{
    int r, c;
    int l = 0;
}app[101];

vector<vector<int>> solution(vector<vector<int>> board, vector<vector<int>> commands) {
    N = board.size(), M = board[0].size();
    for(int r=0;r<N;++r){
        for(int c=0;c<M;++c){
            int id = board[r][c];
            if(app[id].l==0){
                app[id].r = r, app[id].c = c;
                for(int i=c;i<M&&board[r][i]==id;++i)app[id].l++;
            }
        }
    }
    
    queue<int> q;
    vector<bool> inq(101);
    auto push = [&](int id, int dir){
        auto wrapper = [n=N, m=M](int &r, int &c){
            r = (r+n)%n;
            c = (c+m)%m;
        };
        q.push(id);
        inq[id] = true;
        while(!q.empty()){
            auto i = q.front(); q.pop();
            inq[i] = false;
            int br = app[i].r + (app[i].l-1)*(dir==3);
            int bc = app[i].c + (app[i].l-1)*(dir==2);
            for(int j=0;j<app[i].l;++j){
                int r = br+j*(~dir&1);
                int c = bc+j*(dir&1);
                wrapper(r, c);
                if(board[r][c]==i) board[r][c] = 0;
            }
            if(dir&1) br+=app[i].l*(dir==1?1:-1);
            else bc+=app[i].l*(dir==0?1:-1);
            for(int j=0;j<app[i].l;++j){
                int r = br+j*(~dir&1);
                int c = bc+j*(dir&1);
                wrapper(r, c);
                int jd = board[r][c];
                if(jd&&!inq[jd]){
                    q.push(jd);
                    inq[jd] = true;
                }
                board[r][c] = i;
            }
            app[i].r += DR[dir];
            app[i].c += DC[dir];
            wrapper(app[i].r, app[i].c);
            if(app[i].r + app[i].l > N || app[i].c + app[i].l > M)inq[i] = true, q.push(i);
        }
    };
    
    for(auto command: commands){
        push(command[0], command[1]-1);
    }
    
    return board;
}
