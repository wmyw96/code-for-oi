/************************************************************** 
    Problem: 1006 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:1528 ms 
    Memory:24864 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cstdio> 
#include<cmath> 
using namespace std; 
  
const int MAX_M=3000001,MAX_N=10001; 
int g[MAX_M],next[MAX_M],c[MAX_N],h[MAX_N],lab[MAX_N],color[MAX_N]; 
int n,m,nm; 
  
void addedge(int x,int y){ 
     g[++nm]=y; 
     next[nm]=c[x]; 
     c[x]=nm; 
} 
  
void dfs(int i){ 
     //printf("%d\n",i); 
     for (int k=c[i];k;k=next[k]) 
         h[color[g[k]]]=i; 
     for (int j=1;j<=n;j++) if (h[j]!=i) {color[i]=j;break;} 
     int pv=0;int v=0; 
     for (int k=c[i];k;k=next[k]){ 
         int j=g[k]; 
         if (!color[j]) 
             lab[j]++; 
     } 
     for (int j=1;j<=n;j++) if (lab[j]>pv && color[j]==0) pv=lab[j],v=j; 
     if (v!=0) 
     dfs(v); 
     else return; 
} 
  
int main(){ 
    scanf("%d%d",&n,&m); 
    for (int i=1;i<=m;i++){ 
        int x,y; 
        scanf("%d%d",&x,&y); 
        addedge(x,y);addedge(y,x); 
    } 
    dfs(1); 
    int ans=0; 
    for (int i=1;i<=n;i++) if (color[i]>ans) ans=color[i]; 
    printf("%d\n",ans); 
    //system("pause"); 
}

