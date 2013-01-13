/************************************************************** 
    Problem: 1044 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:8244 ms 
    Memory:3224 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
const int N=100001,MOD=10007; 
int l,r; 
int n,m,ans,ansn; 
int a[N],s[N],f1[N],f[N],g[N]; 
int check(int x){ 
    int p=0;int q=1; 
    for (int i=1;i<=n;i++){ 
        if (a[i]>x) return 0; 
        p+=a[i]; 
        if (p>x) q++,p=a[i];  
    } 
    return (q<=m); 
} 
    
int main(){      
    scanf("%d%d",&n,&m); 
    m++; 
    for (int i=1;i<=n;i++){ 
        scanf("%d",&a[i]); 
        if (a[i]>l) l=a[i]; 
        s[i]=s[i-1]+a[i]; 
    } 
    l--; 
    r=s[n]+1; 
    while (l+1<r){ 
          int mid=(l+r)/2; 
          if (check(mid)) r=mid; 
          else l=mid; 
    } 
    ans=r; 
    for (int i=1;i<=n;i++) if (s[i]<=ans) f[i]=1; 
    for (int i=2;i<=m;i++){ 
        for (int j=1;j<=n;j++) g[j]=(g[j-1]+f[j])%MOD,f[j]=0; 
        int k=i; 
        f[i]=1; 
        for (int j=i+1;j<=n;j++){ 
            while (s[j]-s[k-1]>ans) k++; 
            f[j]=(g[j-1]-g[k-2]>=0) ? (g[j-1]-g[k-2]) :(g[j-1]-g[k-2]+MOD); 
        } 
        ansn+=f[n];ansn%=MOD; 
    } 
    printf("%d %d\n",ans,ansn); 
}

