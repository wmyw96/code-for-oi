/************************************************************** 
    Problem: 1087 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:24 ms 
    Memory:7312 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
typedef long long LL; 
const int NN=(1<<9)-1; 
  
int n,k,nm,tot,N; 
int g[NN*NN],next[NN*NN],c[NN]; 
LL F[10][100][NN]; 
int sn[NN],num[NN]; 
  
int check(int x){ 
     return !(x & (x>>1)); 
} 
  
int check(int x,int y){ 
     if (x & y) return 0; 
     if ((x & (y>>1)) || (x & (y<<1))) return 0; 
     if ((y & (x>>1)) || (y & (x<<1))) return 0; 
     return 1; 
} 
  
void addedge(int x,int y){ 
     g[++nm]=y; 
     next[nm]=c[x]; 
     c[x]=nm; 
} 
  
int main(){ 
    scanf("%d%d",&n,&k); 
    N=(1<<n)-1; 
    for (int i=0;i<=N;i++) 
        if (check(i)){ 
           sn[++tot]=i; 
           for (int j=0;j<n;j++) 
               if (1<<j & i) num[tot]++; 
           F[1][num[tot]][tot]=1; 
           //printf("%d %d\n",i,num[tot]); 
        } 
    for (int i=1;i<=tot;i++) 
        for (int j=1;j<=tot;j++) 
            if (check(sn[i],sn[j])) addedge(j,i);//,printf("%d %d\n",j,i); 
    for (int i=2;i<=n;i++) 
        for (int j=0;j<=k;j++) 
           for (int p=1;p<=tot;p++){ 
               for (int l=c[p];l;l=next[l]){ 
                   int q=g[l]; 
                   F[i][j][p]+=F[i-1][j-num[p]][q]; 
               } 
               //printf("F[%d][%d][%d]  %d\n",i,j,sn[p],F[i][j][p]); 
           } 
    LL ans=0; 
    for (int i=1;i<=tot;i++) ans+=F[n][k][i]; 
    cout<<ans<<endl; 
    //system("pause"); 
}
