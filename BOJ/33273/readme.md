# [33273](https://www.acmicpc.net/problem/33273)

#dp #그리디

만약 수열에 $$k$$를 사용하기로 했다면 $$k$$를 모두 다 사용하지 않고
$$k$$의 약수를 사용하는 것은 손해임을 증명할 수 있다.

$$M$$가지 종류의 정수를 오름차순으로 정렬한 수열을 $$B$$라 하고,
수열 $$A$$를 뒤에서부터 구성해보자.
구성하려는 수 역시 가장 큰 수($$B$$의 뒤쪽)부터 고려해보자.

$$B_i$$를 사용한다고 가정하면 다음의 일이 발생한다.
- $$B_i$$를 모두 사용해야 한다.
  - 다음에 채워야 하는 $$A$$의 위치는 현재 위치에서 $$B_i$$의 개수 뺀 값과 관련 있다.
- 다음에 고려할 수는 $$B_i$$의 약수들이다.

메모이제이션을 사용해 중복된 계산을 줄이자.

시간복잡도는 다음과 같을 것으로 추정한다.
- $$O(NM \log M)$$
  - $$N \times M$$ 개의 dp 테이블을 채우고
  - 자신의 약수를 모두 확인하는 것은 평균적으로 $$\log M$$만큼 걸릴 것이다.

만약 $$M$$개의 정수에 범위에 제한이 없다면 다음의 경우에는 평균적으로 $$M$$개를 확인해야 한다.
- $$2^0, 2^1, 2^2, \dots, 2^{M-1}$$

그러나 $$M$$개의 분포가 고르다면 평균적인 약수의 수는 최악의 경우 조화수열의 합과 유사한 분포를 보일 것이다.

```cpp
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
