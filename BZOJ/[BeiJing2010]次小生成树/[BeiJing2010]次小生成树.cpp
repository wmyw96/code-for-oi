/**************************************************************
    Problem: 1977
    User: wmyw96
    Language: C++
    Result: Accepted
    Time:1956 ms
    Memory:38168 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring> 
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<queue>
  
using namespace std;
  
const int MAX_N=111111,MAX_M=333333,MAX_K=21;
typedef long long LL;
struct data{
    int v,dep;
};
queue<data> Q;
struct Edg{
    int x,y,w;
}E[MAX_M];
struct atype{
    int v,mx;
};
int fa[MAX_N][MAX_K],mx[MAX_N][MAX_K],mx2[MAX_N][MAX_K];
int g[MAX_N*2],next[MAX_N*2],c[MAX_N],Ew[MAX_N*2];
int Fa[MAX_N],d[MAX_N],mark[MAX_M],lg[MAX_N];
int n,m,nm,limit;
LL ans,ansn;
  
void bfs(){
    data x;
    x.v=1;x.dep=0;
    Q.push(x);
    while (!Q.empty()){
        x=Q.front();
        Q.pop();
        int i=x.v;
        int dep=x.dep;
        d[i]=dep;
        for (int k=1;k<=lg[dep];k++){
            fa[i][k]=fa[fa[i][k-1]][k-1];
            mx[i][k]=max(mx[i][k-1],mx[fa[i][k-1]][k-1]);
            int ret=(mx[i][k-1]<mx[i][k])?mx[i][k-1]:mx2[i][k-1];
            int ret2=(mx[fa[i][k-1]][k-1]<mx[i][k])?mx[fa[i][k-1]][k-1]:mx2[fa[i][k-1]][k-1];
            mx2[i][k]=max(ret,ret2);
            //if (mx2[i][k]==mx[i][k]) printf("ERROR\n");
        }
        //if (mx2[i][0]==mx[i][0]) printf("ERROR  %d\n",fa[i][0]);
        for (int k=c[i];k;k=next[k]){
            int j=g[k];
            if (!~d[j]){
                x.v=j;x.dep=dep+1;
                fa[j][0]=i;
                mx[j][0]=Ew[k];
                Q.push(x);
            }
        }
    }
}
  
void addedge(int x,int y,int w){
    g[++nm]=y;
    next[nm]=c[x];
    c[x]=nm;
    Ew[nm]=w;
}
  
int find(int x){
    if (Fa[x]<0) return x;
    return Fa[x]=find(Fa[x]);
}
  
atype up(int i,int k){
    atype ret;
    ret.mx=0;
    for (;k>0;k-=(1<<lg[k])){
        ret.mx=max(ret.mx,(mx[i][lg[k]]<limit)?(mx[i][lg[k]]):(mx2[i][lg[k]]));
        i=fa[i][lg[k]];
    }
    ret.v=i;
    return ret;
}
  
int lca(int a,int b){
    if (d[a]<d[b]) swap(a,b);
    if ((a=up(a,d[a]-d[b]).v)==b) return b;
    for (int k=lg[d[a]];k>=0;k--)
        if (fa[a][k]!=fa[b][k]){
            a=fa[a][k];
            b=fa[b][k];
        }
    return fa[a][0];
}
  
void init(){
    lg[1]=0;
    lg[2]=1;
    for (int i=3;i<MAX_N;i++)
        lg[i]=lg[i-1]+((1<<(lg[i-1]+1))<=i);
}
  
int cmp(Edg x,Edg y){
    return x.w<y.w;
}
  
int main(){
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
     
    init();
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++){
        scanf("%d%d%d",&E[i].x,&E[i].y,&E[i].w);
        //if (E[i].w==0) printf("---ERROR---\n");
    }
    sort(E+1,E+m+1,cmp);
    for (int i=1;i<=n;i++) d[i]=Fa[i]=-1;
    int edge=0;
    for (int i=1;i<=m && edge<n-1;i++){
        int x=find(E[i].x);int y=find(E[i].y);
        if (x!=y){
            if (Fa[x]<Fa[y]) Fa[x]+=Fa[y],Fa[y]=x;
                        else Fa[y]+=Fa[x],Fa[x]=y;
            ans=ans+E[i].w;
            mark[i]=1;
            edge++;
            addedge(E[i].x,E[i].y,E[i].w);
            addedge(E[i].y,E[i].x,E[i].w);
        }
    }
     
    //cout<<ans<<endl;
    //printf("%d\n",nm);
    bfs();
    /*
    for (int i=1;i<=n;i++){
        for (int j=0;j<=lg[d[i]];j++)
            printf("%d ",mx2[i][j]);
        printf("\n");
    }
      */     
    ansn=1LL<<62;
    for (int i=1;i<=m;i++){
        if (!mark[i]){
            int a=E[i].x;int b=E[i].y;
            int t=lca(a,b);
            limit=E[i].w;
            int ret=max(up(a,d[a]-d[t]).mx,up(b,d[b]-d[t]).mx);
            if (ret<E[i].w) 
               if (ans-ret+E[i].w<ansn && E[i].x!=E[i].y){ 
                    ansn=ans-ret+E[i].w;
                    //("%d %d %d %d\n",E[i].x,E[i].y,E[i].w,ret);
               }
               
        }
    }
      
    cout<<ansn<<endl;
}

