#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;
  
const int MAX_N=20001,MAX_M=20001,MOD=31011;
typedef long long LL;
int Fa[MAX_N],mark[MAX_N];
struct data{
    int x,y,w;
};
data E[MAX_M];
int n,m,top,ans1,ans,cnt,edge;
map<int,int> M;
map<int,int> M2;
int w[MAX_N],ct[MAX_N],cc[MAX_N];
int Fa_COPY[MAX_N],pp[MAX_N],p[MAX_N];
int MMM[MAX_N];
 
int find(int x){
    if (Fa[x]<0) return x;
    return Fa[x]=find(Fa[x]);
}
  
int check(int ft,int N){
    ft=M[w[ft]];int nd=ft+N-1;
    for (int i=1;i<=n;i++) Fa[i]=Fa_COPY[i];
    for (int i=ft;i<=nd;i++)
        if (mark[i-ft+1]==1){
            int x=find(E[i].x);
            int y=find(E[i].y);
            if (x==y) {return 0;}
            else{
                if (Fa[x]<Fa[y]) Fa[x]+=Fa[y],Fa[y]=x;
                            else Fa[y]+=Fa[x],Fa[x]=y;
            }
        }
    return 1;
}
  
void dfs(int num,int dep,int n,int limit){
    if (limit<0) return;
    if (dep==n+1){
        if (limit>0) return;
        if (check(num,n)) ans1++;
        return;
    }
    mark[dep]=1;
    dfs(num,dep+1,n,limit-1);
    mark[dep]=0;
    dfs(num,dep+1,n,limit);
}
  
int cmp(data x,data y){
    return x.w<y.w;
}
 
void solve(){
    memset(Fa,-1,sizeof Fa);
    edge=0;
    for (int i=1;i<=m;i++){
        int x=find(E[i].x);
        int y=find(E[i].y);        
        if (E[i].w!=E[i-1].w) M[E[i].w]=i;
        cc[M[E[i].w]]++; 
        if (x!=y){
            pp[M[E[i].w]]++;
            if (Fa[x]<Fa[y]) Fa[x]+=Fa[y],Fa[y]=x;
                        else Fa[y]+=Fa[x],Fa[x]=y;
            if (w[cnt]!=E[i].w) w[++cnt]=E[i].w,ct[cnt]=1; else ct[cnt]++;
            MMM[i]=1;
            edge++;
        }
    }
}
 
void solvel(int nono){
    memset(Fa,-1,sizeof Fa);
    for (int i=1;E[i].w<nono;i++){
        int x=find(E[i].x);
        int y=find(E[i].y);
        int pr=M[E[i].w];
        if (x!=y && E[i].w<nono){
            if (Fa[x]<Fa[y]) Fa[x]+=Fa[y],Fa[y]=x;
                        else Fa[y]+=Fa[x],Fa[x]=y;
        }
    }
}
 
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
        scanf("%d%d%d",&E[i].x,&E[i].y,&E[i].w);
    sort(E+1,E+1+m,cmp);
    solve();    
    ans=1;
    for (int i=1;i<=cnt;i++){
        ans1=0;
        int limit=cc[M[w[i]]];
        solvel(w[i]);
        for (int j=1;j<=n;j++) Fa_COPY[j]=Fa[j];
        dfs(i,1,limit,ct[i]); 
        ans=(LL)ans1*ans%MOD;
    }
    if (edge>=n-1)printf("%d\n",ans); else printf("0\n");
}

