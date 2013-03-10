#include <stdio.h>
#include <string.h>
#include <algorithm>
#define clr(a,b) memset(a,b,sizeof(a))
using namespace std;
 
const int N=400005,inf=0x7fffffff;
int n,m,eid,col[N],minn;
int head[N],ed[N<<1],nxt[N<<1];int val[N<<1],ans,k;
int vis[N],fa[N],dep[N],siz[N],num[N];int g[N],mg[N];
 
void addedge(int s,int e,int v){
    ed[eid]=e;val[eid]=v;nxt[eid]=head[s];head[s]=eid++;
}
 
bool cmp(int a,int b){
    return dep[ed[a]]<dep[ed[b]];
}
 
int dfssize(int s,int f){
    fa[s]=f;siz[s]=1;
    for(int i=head[s];~i;i=nxt[i])
        if(ed[i]!=f&&!vis[ed[i]])siz[s]+=dfssize(ed[i],s);
    return siz[s];
}
 
void dfsroot(int s,int sum,int&root){
    int maxx=sum-siz[s];
    for(int i=head[s];~i;i=nxt[i]){
        int e=ed[i];if(e==fa[s]||vis[e])continue;
        dfsroot(e,sum,root);maxx=max(maxx,siz[e]);
    }
    if(maxx<minn){minn=maxx;root=s;}
}
 
int dfsdepth(int s,int f){
    dep[s]=col[s];int maxx=0;
    for(int i=head[s];~i;i=nxt[i])
        if(ed[i]!=f&&!vis[ed[i]])maxx=max(maxx,dfsdepth(ed[i],s));
    return dep[s]+=maxx;
}
 
void dfsg(int s,int f,int d,int c){
    g[c]=max(g[c],d);
    for(int i=head[s];~i;i=nxt[i]){
        int e=ed[i];int v=val[i];if(e==f||vis[e])continue;
        dfsg(e,s,d+v,c+col[e]);
    }
}
 
void solve(int s){
    int sum=dfssize(s,-1),top;minn=inf;
    int root;dfsroot(s,sum,root);vis[root]=1;
    for(int i=head[root];~i;i=nxt[i])
        if(ed[i]!=root&&!vis[ed[i]])solve(ed[i]);top=0;
    for(int i=head[root];~i;i=nxt[i])
        if(ed[i]!=root&&!vis[ed[i]]){dfsdepth(ed[i],root);num[top++]=i;}
    sort(num,num+top,cmp);
    for(int i=0;i<=dep[ed[num[top-1]]];i++)mg[i]=-inf;
    for(int i=0;i<top;i++){
        int e=ed[num[i]],d=dep[e];int v=val[num[i]];
        for(int j=0;j<=d;j++)g[j]=-inf;
        dfsg(e,root,v,col[e]);
        if(i){
            for(int j=0;j<=k-col[root]&&j<=d;j++){
                int r=min(dep[ed[num[i-1]]],k-col[root]-j);
                if(mg[r]==-inf)break;
                if(g[j]!=-inf)ans=max(ans,mg[r]+g[j]);
            }
        }
        for(int j=0;j<=d;j++){
            mg[j]=max(g[j],mg[j]);
            if(j)mg[j]=max(mg[j],mg[j-1]);
            if(j+col[root]<=k)ans=max(ans,mg[j]);
        }
    }
    vis[root]=0;
}
 
int main(){
//    freopen("/home/axorb/in","r",stdin);
//    freopen("/home/axorb/out","w",stdout);
//printf("%d %d\n",inf,-inf);
    scanf("%d%d%d",&n,&k,&m);
    eid=0;
    for(int i=1;i<=n;i++){
        col[i]=vis[i]=0;head[i]=-1;
    }
    for(int i=1;i<=m;i++){
        int a;scanf("%d",&a);col[a]=1;
    }
    for(int i=1;i<n;i++){
        int a,b;int c;scanf("%d%d%d",&a,&b,&c);
        addedge(a,b,c);addedge(b,a,c);
    }
    ans=0;solve(1);
    printf("%d\n",ans);
}
