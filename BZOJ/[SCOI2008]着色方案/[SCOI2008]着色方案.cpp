/************************************************************** 
    Problem: 1079 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:44 ms 
    Memory:25848 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
using namespace std; 
typedef long long LL; 
const int MOD=1000000007; 
int F[16][16][16][16][16][6]; 
int nt[191]; 
int n; 
int c; 
  
int  dfs(int a,int b,int c,int d,int e,int f){ 
     if (a+b+c+d+e==0) return 1; 
     LL ret=0; 
     if (F[a][b][c][d][e][f]) return F[a][b][c][d][e][f]; 
     if (a) ret+=(LL)(a-(f==2))*dfs(a-1,b,c,d,e,1); 
     if (b) ret+=(LL)(b-(f==3))*dfs(a+1,b-1,c,d,e,2); 
     if (c) ret+=(LL)(c-(f==4))*dfs(a,b+1,c-1,d,e,3); 
     if (d) ret+=(LL)(d-(f==5))*dfs(a,b,c+1,d-1,e,4); 
     if (e) ret+=(LL)(e)*dfs(a,b,c,d+1,e-1,5); 
     ret%=MOD; 
     return F[a][b][c][d][e][f]=ret; 
} 
  
int main(){ 
    //memset(F,-1,sizeof F); 
    scanf("%d",&n); 
    for (int i=1;i<=n;i++){ 
        scanf("%d",&c); 
        nt[c]++; 
    } 
    printf("%d\n",dfs(nt[1],nt[2],nt[3],nt[4],nt[5],0)); 
}

