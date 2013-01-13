/************************************************************** 
    Problem: 1040 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:2152 ms 
    Memory:92580 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
#include<vector> 
using namespace std; 
  
const int MAX_N=1111111; 
  
typedef long long LL; 
int vi[MAX_N],stack[MAX_N],mark[MAX_N]; 
LL F[MAX_N][2],f[MAX_N][2]; 
int top,nm,n,cnt,ok; 
int g[MAX_N*2],next[MAX_N*2],c[MAX_N]; 
int va[MAX_N]; 
int l[MAX_N]; 
vector<int> C[MAX_N]; 
  
void dfsc(int i,int pre){ 
    stack[++top]=i; 
    mark[i]=0; 
    vi[i]=1; 
    for (int k=c[i];k;k=next[k]){ 
        int j=g[k]; 
        if (!vi[j]) dfsc(j,i); 
        else{ 
            int v; 
            if (pre!=j && !ok){ 
                ++cnt;ok=1; 
                C[cnt].push_back(0); 
                do{ 
                    v=stack[top--]; 
                    C[cnt].push_back(v); 
                    l[cnt]++; 
                    mark[v]=1; 
                }while (v!=j && top>0); 
            } 
        } 
    } 
    top--; 
} 
  
void dfs(int i){ 
    vi[i]=1; 
    f[i][1]=va[i]; 
    for (int k=c[i];k;k=next[k]){ 
        int j=g[k]; 
        if (!vi[j] && mark[j]==0){ 
            dfs(j); 
            f[i][0]+=max(f[j][0],f[j][1]); 
            f[i][1]+=f[j][0]; 
        } 
    } 
} 
  
void addedge(int x,int y){ 
    g[++nm]=y; 
    next[nm]=c[x]; 
    c[x]=nm; 
} 
  
int main(){ 
    scanf("%d",&n); 
    for (int i=1;i<=n;i++){ 
        int y; 
        scanf("%d%d",&va[i],&y); 
        addedge(i,y); 
        addedge(y,i); 
    } 
    for (int i=1;i<=n;i++) mark[i]=-1; 
    memset(vi,0,sizeof vi); 
    for (int i=1;i<=n;i++) 
        if (mark[i]==-1){ 
           ok=0,top=0,dfsc(i,0); 
           if (!ok) mark[i]=1; 
       } 
    memset(vi,0,sizeof vi); 
    for (int i=1;i<=n;i++) 
        if (mark[i]==1) dfs(i); 
    memset(vi,0,sizeof vi); 
    LL ans=0; 
    for (int i=1;i<=cnt;i++){ 
        F[2][1]=f[C[i][1]][0]+f[C[i][2]][1]; 
        F[2][0]=f[C[i][1]][0]+f[C[i][2]][0]; 
        for (int j=3;j<=l[i];j++){ 
            F[j][0]=f[C[i][j]][0]+max(F[j-1][0],F[j-1][1]); 
            F[j][1]=f[C[i][j]][1]+F[j-1][0]; 
        } 
        LL ans1=max(F[l[i]][0],F[l[i]][1]); 
        F[2][1]=0; 
        F[2][0]=max(f[C[i][1]][0],f[C[i][1]][1])+f[C[i][2]][0]; 
        for (int j=3;j<=l[i];j++){ 
            F[j][0]=f[C[i][j]][0]+max(F[j-1][0],F[j-1][1]); 
            F[j][1]=f[C[i][j]][1]+F[j-1][0]; 
        } 
        ans1=max(ans1,F[l[i]][0]); 
        ans+=(ans1) ? ans1 : max(f[C[i][1]][0],f[C[i][1]][1]); 
    } 
    cout<<ans<<endl; 
}

