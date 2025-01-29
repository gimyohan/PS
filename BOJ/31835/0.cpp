#include<bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define rep(a) for(int __i = (a); __i > 0; --__i)
#define all(x) x.begin(), x.end()
#define len(x) (int)(x).size()
typedef long long ll;

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
