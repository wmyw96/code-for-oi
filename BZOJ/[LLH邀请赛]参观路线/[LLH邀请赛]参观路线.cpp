/************************************************************** 
    Problem: 1301 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:3516 ms 
    Memory:23856 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
  
int n,m,nm,head,tot; 
const int MAX_N=200001,MAX_M=2000001; 
int pre[MAX_N],nxt[MAX_N],ans[MAX_N]; 
int vi[MAX_N],c[MAX_N],g[MAX_M],next[MAX_M]; 
  
void addedge(int x,int y){ 
     g[++nm]=y; 
     next[nm]=c[x]; 
     c[x]=nm; 
} 
  
void seethechain(int x){ 
     for (;x!=0;x=nxt[x]) printf("%d ",x); 
     printf("\n"); 
} 
  
void dfs(int i){ 
       
        for (int k=c[i];k;k=next[k]){ 
            vi[g[k]]=i; 
        } 
          
        for (int k=head;k;k=nxt[k]) 
            if (vi[k]!=i){ 
               ans[++tot]=k; 
               if (!pre[k]) head=nxt[k]; 
                  else nxt[pre[k]]=nxt[k]; 
               if (nxt[k]) pre[nxt[k]]=pre[k]; 
               //seethechain(head); 
               dfs(k); 
               if (tot>=n) return; 
            } 
} 
  
int main(){ 
    scanf("%d%d",&n,&m); 
    for (int i=1;i<=m;i++){ 
        int x,y; 
        scanf("%d%d",&x,&y); 
        addedge(x,y); 
        addedge(y,x); 
    } 
    for (int i=3;i<n;i++) pre[i]=i-1,nxt[i]=i+1; 
    head=2; 
    pre[2]=0;nxt[2]=3; 
    pre[n]=n-1; 
      
    ans[1]=1;tot=1; 
      
    dfs(1); 
      
    for (int i=1;i<=tot;i++) printf("%d\n",ans[i]); 
      
    //system("pause"); 
} 

