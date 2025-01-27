#include<bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define rep(a) for(int __i = (a); __i > 0; --__i)
#define all(x) x.begin(), x.end()
#define len(x) (int)(x).size()
typedef long long ll;

const int NN = 5e2+2;
int N, M;
pair<ll, ll> A[NN];

vector<int> eg[NN];
ll memo[NN][NN];
ll dp(ll i, ll j){
    if(i<0) return 0;
    ll &rst = memo[i][j];
    if(rst!=-1)return rst;
    rst = -2;
    if(A[j].second>i)return rst = min(i+1, A[j].second)*A[j].first;
    if(eg[j].empty())return rst;
    for(auto nj:eg[j]){
        ll ret = dp(i-A[j].second, nj);
        if(ret!=-2)rst = max(rst, ret+A[j].first*min(i+1, A[j].second));
    }
    return rst;
}

signed main(){
    fastio;

    cin>>N>>M;
    for(int i=0;i<M;i++){
        cin>>A[i].first>>A[i].second;
    }

    sort(A, A+M);
    for(int i=0;i<M;i++){
        for(int j=i+1;j<M;j++){
            if(A[j].first%A[i].first==0) eg[j].push_back(i);
        }
    }
    memset(memo, -1, sizeof(memo));
    ll ans = -1;
    for(int i=0;i<M;i++)ans = max(ans, dp(N-1, i));
    cout<<ans;
    
    return 0;
}
