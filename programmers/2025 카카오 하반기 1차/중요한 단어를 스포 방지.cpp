#include <bits/stdc++.h>

using namespace std;

int solution(string message, vector<vector<int>> spoiler_ranges) {
    set<string> pub, prv;
    vector<bool> is_blur(message.size());
    for(auto el:spoiler_ranges){
        for(int i=el[0];i<=el[1];++i)is_blur[i] = true;
    }
    
    for(int i=0;i<message.size();++i){
        if(message[i] == ' ')continue;
        bool blur = false;
        for(int j=i;;++j){
            if(j == message.size() || message[j] == ' '){
                (blur?prv:pub).insert(message.substr(i, j-i));
                i = j;
                break;
            }
            if(is_blur[j])blur = true;
        }
    }
    
    int answer = 0;
    for(auto &s:prv){
        if(pub.find(s)==pub.end())answer++;
    }
    return answer;
}
