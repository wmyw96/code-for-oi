/************************************************************** 
    Problem: 1045 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:2644 ms 
    Memory:12992 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cmath> 
#include<cstring> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
  
typedef long long LL; 
const int MAX_N=1000001; 
int a[MAX_N]; 
int n; 
LL ans,k,sum,x; 
LL s[MAX_N]; 
  
int main(){ 
    scanf("%d",&n); 
    for (int i=1;i<=n;i++){ 
        scanf("%d",&a[i]); 
        sum+=a[i]; 
    } 
    x=sum/n; 
    for (int i=1;i<=n;i++) 
        s[i]=s[i-1]+a[i]-x; 
    sort(s+1,s+1+n); 
    k=-s[(n+1)/2]; 
    for (int i=1;i<=n;i++) 
        ans+=abs(s[i]+k); 
    cout<<ans<<endl; 
}

