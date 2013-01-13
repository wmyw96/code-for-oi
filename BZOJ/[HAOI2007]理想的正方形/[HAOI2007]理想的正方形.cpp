/************************************************************** 
    Problem: 1047 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:2088 ms 
    Memory:20872 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
struct data{ 
       int v,t; 
}; 
  
const int MAX_N=1001; 
  
data Q_MAX[MAX_N*2],Q_MIN[MAX_N*2]; 
int a[MAX_N][MAX_N],B[MAX_N][MAX_N],b[MAX_N][MAX_N],C[MAX_N][MAX_N],c[MAX_N][MAX_N]; 
int n,m,k,l,r,L,R; 
  
int main(){ 
    scanf("%d%d%d",&n,&m,&k); 
    for (int i=1;i<=n;i++) 
        for (int j=1;j<=m;j++) 
            scanf("%d",&a[i][j]); 
      
    for (int i=1;i<=n;i++){ 
        l=1;r=0;L=1;R=0; 
        for (int j=1;j<=m;j++) Q_MAX[j].v=Q_MAX[j].t=Q_MIN[j].v=Q_MIN[j].t=0; 
        for (int j=1;j<=k;j++){ 
            while (l<=r && Q_MAX[r].v<a[i][j]) r--; 
            Q_MAX[++r].v=a[i][j]; 
            Q_MAX[r].t=j; 
  
            while (L<=R && Q_MIN[R].v>a[i][j]) R--; 
            Q_MIN[++R].v=a[i][j]; 
            Q_MIN[R].t=j; 
        } 
        B[i][1]=Q_MAX[l].v; 
        b[i][1]=Q_MIN[L].v; 
        for (int j=k+1;j<=m;j++){ 
            while (l<=r && Q_MAX[l].t<=j-k) l++; 
            while (l<=r && Q_MAX[r].v<a[i][j]) r--; 
            Q_MAX[++r].v=a[i][j]; 
            Q_MAX[r].t=j; 
            B[i][j-k+1]=Q_MAX[l].v; 
  
            while (L<=R && Q_MIN[L].t<=j-k) L++; 
            while (L<=R && Q_MIN[R].v>a[i][j]) R--; 
            Q_MIN[++R].v=a[i][j]; 
            Q_MIN[R].t=j; 
            b[i][j-k+1]=Q_MIN[L].v; 
        } 
    } 
      
    for (int i=1;i<=m-k+1;i++){ 
        l=1;r=0;L=1;R=0; 
        for (int j=1;j<=n;j++) Q_MAX[j].v=Q_MAX[j].t=Q_MIN[j].v=Q_MIN[j].t=0; 
        for (int j=1;j<=k;j++){ 
            while (l<=r && Q_MAX[r].v<B[j][i]) r--; 
            Q_MAX[++r].v=B[j][i]; 
            Q_MAX[r].t=j; 
  
            while (L<=R && Q_MIN[R].v>b[j][i]) R--; 
            Q_MIN[++R].v=b[j][i]; 
            Q_MIN[R].t=j; 
        } 
        C[1][i]=Q_MAX[l].v; 
        c[1][i]=Q_MIN[L].v; 
        for (int j=k+1;j<=n;j++){ 
            while (l<=r && Q_MAX[l].t<=j-k) l++; 
            while (l<=r && Q_MAX[r].v<B[j][i]) r--; 
            Q_MAX[++r].v=B[j][i]; 
            Q_MAX[r].t=j; 
            C[j-k+1][i]=Q_MAX[l].v; 
  
            while (L<=R && Q_MIN[L].t<=j-k) L++; 
            while (L<=R && Q_MIN[R].v>b[j][i]) R--; 
            Q_MIN[++R].v=b[j][i]; 
            Q_MIN[R].t=j; 
            c[j-k+1][i]=Q_MIN[L].v; 
        } 
    }     
    int ans=2147483647; 
    for (int i=1;i<=n-k+1;i++){ 
        for (int j=1;j<=m-k+1;j++) 
            ans=min(ans,C[i][j]-c[i][j]); 
    } 
    printf("%d\n",ans); 
}
