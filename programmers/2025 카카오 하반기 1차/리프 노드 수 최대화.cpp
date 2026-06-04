#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll log3(ll x){
    ll rst = 0;
    while(x/=3)rst++;
    return rst;
}

ll pow(ll b, ll e){
    ll rst = 1;
    while(e--)rst*=b;
    return rst;
}

ll g_sum(ll a, ll r, ll n){
    ll rst = 0;
    for(int i=0;i<n;++i){
        rst+=a;
        a*=r;
    }
    return rst;
}

int solution(int dist_limit, int split_limit) {
    ll d = dist_limit, s = split_limit;
    ll h2 = 0, h3 = log3(s);
    ll answer = min(d, g_sum(1, 3, h3))<<1|1;
    while(h3>=0){
        while(pow(2, h2)*pow(3, h3)*2<=s){
            h2++;
            ll d2 = min(d, (1ll<<h2)-1);
            ll d3 = min(d-d2, g_sum(1<<h2, 3, h3));
            answer = max(answer, 1+d2+d3*2);
        }
        h3--;
        h2++;
    }
    return answer;
}
