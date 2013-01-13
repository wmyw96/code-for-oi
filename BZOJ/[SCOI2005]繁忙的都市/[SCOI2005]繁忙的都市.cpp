/************************************************************** 
    Problem: 1083 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:32 ms 
    Memory:11820 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
const int MAX_N=601,MAX_M=900001; 
struct node{int x,y,w;}E[MAX_M]; 
int Fa[MAX_N],ans,n,m; 
int cmp(node x,node y){return x.w<y.w;} 
int find(int x){ 
    if (Fa[x]<0) return x; 
    return Fa[x]=find(Fa[x]); 
} 
int main(){ 
    scanf("%d%d",&n,&m); 
    for (int i=1;i<=m;i++) 
        scanf("%d%d%d",&E[i].x,&E[i].y,&E[i].w); 
    sort(E+1,E+1+m,cmp); 
    for (int i=1;i<=n;i++) Fa[i]=-1; 
    for (int i=1,j=0;i<=m,j<n-1;i++){            
  
        int x=find(E[i].x);int y=find(E[i].y); 
        if (x!=y){ 
           if (Fa[x]<Fa[y]) {Fa[x]+=Fa[y];Fa[y]=x;} 
                       else {Fa[y]+=Fa[x];Fa[x]=y;} 
           ans=max(ans,E[i].w); 
           j++; 
        } 
    } 
    printf("%d %d\n",n-1,ans); 
}

