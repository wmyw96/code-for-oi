/************************************************************** 
    Problem: 1827 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:500 ms 
    Memory:14636 kb 
****************************************************************/
  
/* 
基于模拟的换根法。。。 
可见，对于一对父子x，y和连接它们的变的权值w，如果y及其所有儿子的人数为N_Y, 
那么val就要+上 (N_SUM - N_Y) * w - N_y * w ,然后就可以O(N)处理 
注意longlong啊。  
___________ 
val+=(LL)(s[j]+a[j])*w[k]; 
___________ 
WA一次。 
2012-10-30  
*/
#include<iostream>  
#include<cstdio>  
#include<cstring>  
#include<cmath>  
#include<cstdlib>  
#include<algorithm>  
using namespace std;  
  
typedef long long LL; 
LL val,ans,sum; 
const int MAX_N=300001; 
int g[MAX_N],next[MAX_N],c[MAX_N],w[MAX_N]; 
int s[MAX_N],a[MAX_N]; 
int n,m,nm; 
int vi[MAX_N]; 
  
  
void addedge(int x,int y,int we){ 
     g[++nm]=y; 
     next[nm]=c[x]; 
     c[x]=nm; 
     w[nm]=we; 
} 
  
void dfs(int i){  
     vi[i]=1;  
     for (int k=c[i];k;k=next[k]){  
         int j=g[k]; 
         if (!vi[j]){ 
            dfs(j); 
            s[i]+=s[j]+a[j]; 
            val+=(LL)(s[j]+a[j])*w[k]; 
         } 
     } 
} 
  
void dfs2(int i){ 
     vi[i]=1; 
     for (int k=c[i];k;k=next[k]){ 
         int j=g[k]; 
         if (!vi[j]){ 
            LL ret=val; 
            val+=(LL)(sum-s[j]-a[j])*w[k]; 
            val-=(LL)(s[j]+a[j])*w[k]; 
            ans=min(val,ans); 
            dfs2(j); 
            val=ret; 
         } 
     } 
} 
  
int main(){  
    scanf("%d",&n);  
    for (int i=1;i<=n;i++) scanf("%d",&a[i]),sum+=a[i];   
        
    for (int i=1;i<n;i++){  
        int x,y,ww; 
        scanf("%d%d%d",&x,&y,&ww);  
        addedge(x,y,ww);  
        addedge(y,x,ww);  
    }  
    memset(vi,0,sizeof vi); 
    dfs(1); 
    ans=val; 
    memset(vi,0,sizeof vi);  
    dfs2(1); 
    cout<<ans<<endl; 
}

