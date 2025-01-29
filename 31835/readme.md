# [31835](https://www.acmicpc.net/problem/31835)

#브루투포스 #애드혹

최대 2개를 수정하면 원하는 값으로 바꿀 수 있다.

- `F`를 얻으려는 경우 `& F`를,
- `T`를 얻으려는 경우 `| T`를 접미사로 가지게 만들면 된다.

따라서 답이 0개인 경우와 1개인 경우를 $$O(N^2)$$에 모두 확인하고,
둘 다 아니라면 2번의 수정이면 충분하다.

```cpp
const int NN = 2e3+3;
int N;
char A[NN], C;

char sim(){
    char cur = A[0];
    for(int i=1;i<N;i+=2){
        if(A[i]=='|')cur = (cur||A[i+1])?'T':0;
        else cur = (cur&&A[i+1])?'T':0;
    }
    return cur?cur:'F';
}

signed main(){
    fastio;
    
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>A[i];
        if(A[i]=='F')A[i] = 0;
    }
    cin>>C;

    if(sim()==C){
        cout<<0;
        return 0;
    }
    
    for(int i=0;i<N;i++){
        char tmp = A[i];
        if(A[i]=='T')A[i] = 0;
        else if(A[i]=='&')A[i] = '|';
        else if(A[i]=='|')A[i] = '&';
        else A[i] = 'T';
        if(sim()==C){
            cout<<1;
            return 0;
        }
        A[i] = tmp;
    }


    cout<<2;
    
    return 0;
}
