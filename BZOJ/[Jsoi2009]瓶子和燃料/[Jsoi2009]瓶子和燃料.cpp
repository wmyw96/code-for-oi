/************************************************************** 
    Problem: 2257 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:2392 ms 
    Memory:5204 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
int n,k; 
int a[1001],ans[1001*1001]; 
int cnt,now,num; 
int sqr(int x){return x*x;} 
int main(){ 
    scanf("%d%d",&n,&k); 
    for (int i=1;i<=n;i++) scanf("%d",&a[i]); 
    for (int i=1;i<=n;i++){ 
        for (int j=2;j*j<a[i];j++) 
            if (a[i]%j==0) ans[++cnt]=j,ans[++cnt]=a[i]/j; 
        if (sqr((int)sqrt(a[i]))==a[i]) ans[++cnt]=(int)sqrt(a[i]); 
        ans[++cnt]=a[i]; 
    } 
    sort(ans+1,ans+cnt+1); 
    for (int i=cnt;i>=1;i--){ 
        if (ans[i]==now) num++; 
        else now=ans[i],num=1; 
        if (num>=k) { 
                    printf("%d\n",now); 
                    return 0; 
        } 
    } 
    printf("1\n"); 
}

