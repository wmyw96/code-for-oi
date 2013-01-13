/************************************************************** 
    Problem: 2783 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:264 ms 
    Memory:101840 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
typedef long long LL; 
const int MAX_N=100001; 
  
bool h[100000001]; 
int ans,nm,n,S,now; 
int a[MAX_N],g[MAX_N*2],next[MAX_N*2],c[MAX_N]; 
  
void addedge(int x,int y){ 
     g[++nm]=y; 
     next[nm]=c[x]; 
     c[x]=nm; 
} 
  
void dfs(int i){ 
     now+=a[i]; 
     h[now]=true; 
     if (now>=S) 
        if (h[now-S]==true) ans++; 
     for (int k=c[i];k;k=next[k]) 
         dfs(g[k]); 
     h[now]=false;now-=a[i]; 
} 
  
int main(){ 
      
    scanf("%d%d",&n,&S); 
    for (int i=1;i<=n;i++) 
        scanf("%d",&a[i]); 
    for (int i=1;i<n;i++){ 
        int x,y; 
        scanf("%d%d",&x,&y); 
        addedge(x,y); 
    }  
    h[0]=true; 
    dfs(1); 
    printf("%d\n",ans); 
    //system("pause"); 
}

