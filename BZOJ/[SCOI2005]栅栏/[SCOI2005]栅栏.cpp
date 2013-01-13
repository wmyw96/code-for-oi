/************************************************************** 
    Problem: 1082 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:12 ms 
    Memory:1304 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
const int MAX_N=2001; 
int n,m,nows,sum,l,r; 
int s[MAX_N],a[MAX_N],b[MAX_N],now[MAX_N]; 
  
int dfs(int top,int i){ 
    if (top==0) return 1; 
    if (s[top]>nows) return 0; 
    for (;i<=m;i++) 
      if (now[i]>=b[top]){ 
        now[i]-=b[top];nows-=b[top]; 
        if (now[i]<b[1]) nows-=now[i]; 
          
        if (dfs(top-1,b[top-1]==b[top] ? i : 1)) return 1; 
          
        if (now[i]<b[1]) nows+=now[i]; 
        now[i]+=b[top];nows+=b[top]; 
      } 
    return 0; 
} 
      
int main(){ 
    scanf("%d",&m); 
    for (int i=1;i<=m;i++) scanf("%d",&a[i]),sum+=a[i]; 
    sort(a+1,a+1+m); 
    scanf("%d",&n); 
    for (int i=1;i<=n;i++) scanf("%d",&b[i]); 
    sort(b+1,b+1+n); 
    for (int i=1;i<=n;i++) s[i]=s[i-1]+b[i]; 
    while (s[n]>sum) n--; 
    l=0;r=n+1; 
    while (l+1<r){ 
          for (int i=1;i<=m;i++) now[i]=a[i]; 
          int mid=(l+r)/2; 
          nows=sum; 
          if (dfs(mid,1)) l=mid; 
                    else r=mid; 
    } 
    printf("%d\n",l); 
    //system("pause"); 
}

