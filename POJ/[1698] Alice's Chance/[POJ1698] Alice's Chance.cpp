#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
 
queue<int> Q;
const int MAX_N=5001,MAX_M=1000001,INF=1000000000;
int g[MAX_M],next[MAX_M],flow[MAX_M],c[MAX_N];
int dep[MAX_N],d[MAX_N],w[MAX_N],ok[501][11];
int wx,S,T,n,nm;
 
int bfs(){
    Q.push(S);
    memset(dep,-1,sizeof dep);
    dep[S]=0;
    while (!Q.empty()){
          int i=Q.front();Q.pop();
          for (int k=c[i];k!=-1;k=next[k]){
              int j=g[k];
              if (flow[k]>0 && dep[j]==-1){
                 dep[j]=dep[i]+1;
                 Q.push(j);
              }
          }
    }
    return dep[T]!=-1;
}
 
int dfs(int i,int now){
    if (now==0) return 0;
    if (i==T) return INF;
    for (int k=c[i];k!=-1;k=next[k]){
        int j=g[k];
        int ret=0;
        if (dep[j]==dep[i]+1)
        if (flow[k] && (ret=dfs(j,min(now,flow[k])))){
		   ret=min(ret,flow[k]);
           flow[k]-=ret;flow[k^1]+=ret;
           return ret;
        }
    }
    return 0;
}
 
void addedge(int x,int y,int f){
     g[nm]=y;
     next[nm]=c[x];
     c[x]=nm;
     flow[nm]=f;
     nm++;
}
 
void add(int x,int y,int f){
     addedge(x,y,f);
     addedge(y,x,0);
}
 
int main(){
	int Ti;
    scanf("%d",&Ti);
    while (Ti--){
          memset(c,-1,sizeof c);
          scanf("%d",&n);
          wx=0;int pr=0;nm=0;
          for (int i=1;i<=n;i++){
              for (int j=1;j<=7;j++) scanf("%d",&ok[i][j]);
              scanf("%d%d",&d[i],&w[i]);
              pr+=d[i];
              wx=max(wx,w[i]);
          }
          S=n+7*wx+1;
          T=S+1;
          for (int i=1;i<=n;i++){
              add(S,i,d[i]);
              for (int k=1;k<=7;k++)
                  if (ok[i][k]){
                     for (int j=1;j<=w[i];j++)
                         add(i,n+7*(j-1)+k,1);
                  }
          }
          for (int i=n+1;i<S;i++) add(i,T,1);
          int ans=0;
          while (bfs()){
                int ret=0;
                while (1){
                	ret=dfs(S,INF);
                	if (!ret) break;
                	ans+=ret;
				}
          }
          if (pr==ans) printf("Yes\n");else printf("No\n");
    }
}

