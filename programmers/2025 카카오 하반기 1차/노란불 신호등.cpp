#include <bits/stdc++.h>

using namespace std;

int solution(vector<vector<int>> signals) {
    int n = signals.size(), t = 1;
    vector<vector<int>> lin(n);
    for(int i=0;i<n;++i){
        t = lcm(t, accumulate(signals[i].begin(), signals[i].end(), 0));
        for(int j=0;j<signals[i][0];++j)lin[i].push_back(0);
        for(int j=0;j<signals[i][1];++j)lin[i].push_back(1);
        for(int j=0;j<signals[i][2];++j)lin[i].push_back(0);
    }
    int answer = -1;
    for(int i=0;i<t;++i){
        int sum = 0;
        for(int j=0;j<n;++j){
            sum+=lin[j][i%lin[j].size()];
        }
        if(sum==n){
            answer = i+1;
            break;
        }
    }
    return answer;
}
