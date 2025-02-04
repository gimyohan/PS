#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int NN = 1e5+5;
int N;
double memo[NN], psum[NN];

signed main(){
    fastio;

    cin>>N;
    for(int i=1;i<=N;i++){
        int k;cin>>k;
        memo[i] = 1 + (psum[i-1] - psum[i-1-k])/k;
        psum[i] = psum[i-1] + memo[i];
    }

    cout<<fixed<<setprecision(6)<<memo[N];
    
    return 0;
}
