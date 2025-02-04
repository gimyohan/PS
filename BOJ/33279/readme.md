# [33279](https://www.acmicpc.net/problem/33279)

## 접근 방법

- `dp[i]`를 현재 `i`개의 간식이 남았을 경우 추가적으로 간식을 수령할 수 있는 생활관의 기댓값이라고 하자.

### 주요 사실

- 정답은 `dp[N]`을 출력하면 된다.
- `dp[0] = 0` 간식이 남지 않은 경우 더 이상 간식을 수령하는 생활관은 존재하지 않는다.
- `dp[1] = 1` 주어진 조건에 따라 $$1 \leq K_1 \leq 1$$, 즉 $$K_1 = 1$$이므로 하나의 간식을 분배하면 추가적으로 간식을 수령하는 생활관은 없다.

---

## 입력 예시

```
3
1 2 2
```

### `dp[2]` 계산 과정

간식이 두 개가 남은 경우 현재 생활관에게:

- **1개를 분배한 경우** $$\frac{1}{2}$$  
  간식이 1개가 남으므로 추가적으로 `dp[1`만큼의 생활관 기댓값이 생긴다.
- **2개를 분배한 경우** $$\frac{1}{2}$$  
  간식이 0개가 남으므로 추가적으로 `dp[0`만큼의 생활관 기댓값이 생긴다.

이를 통해 일반화하면 다음과 같은 점화식을 얻는다:

$$
\text{dp}[i] = 1 + \frac{1}{K_i} \sum_{j=1}^{K_i} \text{dp}[i-j] \quad (1 \leq i \leq N)
$$

단, $$\sum$$ 부분은 **누적합**을 이용하여 $$O(1)$$에 구한다.

---

## 바텀-업 DP 코드

```cpp
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
