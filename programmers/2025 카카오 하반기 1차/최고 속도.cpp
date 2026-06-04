#include <bits/stdc++.h>

using namespace std;
const int INF = 0x7f7f7f7f;

struct union_find{
    int n;
    vector<int> parent;
    union_find(int n){
        this->n = n;
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x){
        return x==parent[x]?x:parent[x]=find(parent[x]);
    }
    int merge(int a, int b){
        a = find(a), b = find(b);
        if(a>b)swap(a, b);
        parent[b] = a;
        return a;
    }
};

pair<int, int> inter(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    bool is_h1 = (y1 == y2);
    bool is_h2 = (y3 == y4);
    if (is_h1 && is_h2) {
        if (y1 == y3) {
            if (x2 == x3) return {x2, y1};
            if (x1 == x4) return {x1, y1};
        }
    }
    else if (!is_h1 && !is_h2) {
        if (x1 == x3) {
            if (y2 == y3) return {x1, y2};
            if (y1 == y4) return {x1, y1};
        }
    }
    else if (is_h1 && !is_h2) {
        if (x1 <= x3 && x3 <= x2 && y3 <= y1 && y1 <= y4) return {x3, y1};
    }
    else if (x3 <= x1 && x1 <= x4 && y1 <= y3 && y3 <= y2) return {x1, y3};
    return {INF, INF};
}

vector<int> solution(vector<vector<int>> city, vector<vector<int>> road) {
    vector<int> comp;
    vector<pair<int, int>> pos;
    map<pair<int, int>, int> cam;
    vector<pair<pair<int, int>, int>> tmp;
    for(auto &el: city){
        for(int i=0;i<2;++i) comp.push_back(el[i]);
    }
    for(auto &el: road){
        for(int i=0;i<4;++i) comp.push_back(el[i]);
        comp.push_back(el[0]+el[2]>>1);
        comp.push_back(el[1]+el[3]>>1);
    }
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for(auto &el: city){
        for(int i=0;i<2;++i) el[i] = lower_bound(comp.begin(), comp.end(), el[i]) - comp.begin();
        pos.push_back({el[0], el[1]});
    }
    for(auto &el: road){
        int mx = el[0]+el[2]>>1, my = el[1]+el[3]>>1;
        for(int i=0;i<4;++i) el[i] = lower_bound(comp.begin(), comp.end(), el[i]) - comp.begin();
        tmp.push_back({{mx, my}, el[4]});
    }
    for(int i=0;i<road.size();++i){
        auto &a = road[i];
        int x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3], lim = a[4];
        for(int j=i+1;j<road.size();++j){
            auto &b = road[j];
            int x3 = b[0], y3 = b[1], x4 = b[2], y4 = b[3];
            auto p = inter(x1, y1, x2, y2, x3, y3, x4, y4);
            if(p==make_pair(INF, INF)) continue;
            pos.push_back(p);
        }
    }
    for(auto &[f, s]: tmp){
        int mx = f.first, my = f.second, lim = s;
        mx = lower_bound(comp.begin(), comp.end(), mx) - comp.begin();
        my = lower_bound(comp.begin(), comp.end(), my) - comp.begin();
        pos.push_back({mx, my});
        if(cam.find({mx, my})==cam.end())cam[{mx, my}] = INF;
        cam[{mx, my}] = min(cam[{mx, my}], lim);
    }

    vector<vector<pair<int, int>>> ver(comp.size()), hor(comp.size());
    for(int i=0;i<pos.size();++i){
        int x = pos[i].first, y = pos[i].second;
        ver[y].push_back({x, i});
        hor[x].push_back({y, i});
    }
    for(auto &v: ver)sort(v.begin(), v.end());
    for(auto &v: hor)sort(v.begin(), v.end());
    
    
    vector<pair<int, pair<int, int>>> edge;
    for(auto &el: road){
        int x1 = el[0], y1 = el[1], x2 = el[2], y2 = el[3];
        if(y1==y2){
            int idx = lower_bound(ver[y1].begin(), ver[y1].end(), make_pair(x1, -1)) - ver[y1].begin();
            while(idx+1<ver[y1].size()&&ver[y1][idx+1].first<=x2){
                edge.push_back({min(
                    (cam.find({ver[y1][idx].first, y1})==cam.end()?INF:cam[{ver[y1][idx].first, y1}]),
                    (cam.find({ver[y1][idx+1].first, y1})==cam.end()?INF:cam[{ver[y1][idx+1].first, y1}])
                ), {ver[y1][idx].second, ver[y1][idx+1].second}});
                idx++;
            }
        }
        else{
            int idx = lower_bound(hor[x1].begin(), hor[x1].end(), make_pair(y1, -1)) - hor[x1].begin();
            while(idx+1<hor[x1].size()&&hor[x1][idx+1].first<=y2){
                edge.push_back({min(
                    (cam.find({x1, hor[x1][idx].first})==cam.end()?INF:cam[{x1, hor[x1][idx].first}]),
                    (cam.find({x1, hor[x1][idx+1].first})==cam.end()?INF:cam[{x1, hor[x1][idx+1].first}])
                ), {hor[x1][idx].second, hor[x1][idx+1].second}});
                idx++;
            }
        }
    }
    sort(edge.begin(), edge.end());
    reverse(edge.begin(), edge.end());
    
    vector<int> answer(city.size()-1, INF);
    union_find uf(pos.size());
    
    for(int i=0;i<edge.size();++i){
        int u = edge[i].second.first, v = edge[i].second.second, c = edge[i].first;
        uf.merge(u, v);
        if(i!=edge.size()-1&&c==edge[i+1].first) continue;
        for(int i=1;i<city.size();++i){
            if(answer[i-1]!=INF)continue;
            if(uf.find(0)==uf.find(i))answer[i-1] = (c==INF?c-1:c);
        }
    }
    
    for(auto &a:answer)if(a==INF-1)a=0;
    return answer;
}
