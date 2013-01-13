/************************************************************** 
    Problem: 1076 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:3608 ms 
    Memory:105720 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
  
using namespace std; 
  
const int MAX_N=21,MAX_K=102; 
int n,K,S; 
int v[MAX_N],s[MAX_N]; 
double F[MAX_K][1<<17]; 
  
int main(){ 
    scanf("%d%d",&K,&n); 
    for (int i=1;i<=n;i++){ 
        scanf("%d",&v[i]); 
        int tot,j=1; 
        for (;j;){ 
            scanf("%d",&j); 
            if (!j) break;  
            s[i]+=1<<(j-1); 
        } 
    } 
    S=(1<<n); 
    double N=n; 
    for (int i=K;i>=1;i--) 
        for (int j=0;j<S;j++){ 
            for (int k=1;k<=n;k++) 
                if ((j & s[k]) == s[k]) 
                    F[i][j]+=max((double)(v[k]+F[i+1][j | 1<<(k-1)])/N,(double)F[i+1][j]/N); 
                else F[i][j]+=F[i+1][j]/N; 
        } 
    printf("%.6f\n",F[1][0]); 
}

