/************************************************************** 
    Problem: 1053 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:52 ms 
    Memory:1272 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
typedef long long LL; 
  
int P[101],tot,n,ansn,ans,limit; 
int p[101]; 
  
void dfs(int dep,int now,int num){ 
     if (num>ansn) ansn=num,ans=2147483647; 
     if (num==ansn && now<ans) ans=now; 
     if (dep>tot) return; 
     LL nn=now; 
     for (int i=0;nn<=limit;i++,nn*=P[dep]){ 
         dfs(dep+1,nn,num*(i+1)); 
     } 
} 
  
int main(){ 
    scanf("%d",&limit); 
    for (int i=2;i<=30;i++){ 
        if (!p[i]) P[++tot]=i; 
        for (int j=1;j<=tot;j++) 
            p[P[j]*i]=1; 
    } 
    dfs(1,1,1); 
    printf("%d\n",ans); 
}

