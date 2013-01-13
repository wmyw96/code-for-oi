/************************************************************** 
    Problem: 1042 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:128 ms 
    Memory:2052 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cmath> 
#include<cstring> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
  
typedef long long LL; 
  
const int N=4,M=100000; 
LL F[M+1]; 
LL ans; 
int c[N+1],d[N+1]; 
  
void Calc(int dep,int now,int cnt){ 
   if (now<0) return; 
   if (dep>N){ 
        ans += (cnt%2) ? (-F[now]) : (F[now]); 
        return; 
   } 
   Calc(dep+1,now-c[dep]*(d[dep]+1),cnt+1); 
   Calc(dep+1,now,cnt); 
} 
  
int main(){ 
    for (int i=1;i<=N;i++) 
        scanf("%d",&c[i]); 
    F[0]=1; 
    for (int i=1;i<=N;i++) 
        for (int j=1;j<=M;j++) 
            F[j]+=(j-c[i]>=0) ? F[j-c[i]] : 0; 
    int T,s; 
    scanf("%d",&T); 
    while (T--){ 
        for (int i=1;i<=N;i++) scanf("%d",&d[i]); 
        ans=0;scanf("%d",&s); 
        Calc(1,s,0); 
        cout<<ans<<endl; 
    } 
}

