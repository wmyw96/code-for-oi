/************************************************************** 
    Problem: 1088 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:20 ms 
    Memory:1508 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
  
int n; 
int a[20001],b[20001],c[20001]; 
  
int check(int x){ 
    b[1]=x; 
    for (int i=1;i<=n;i++) a[i]=c[i]; 
    if (x==1){ 
      if (a[1]==0 || a[2]==0) return 0; 
      a[1]--;a[2]--; 
    } 
    for (int i=2;i<=n;i++){ 
        if (a[i-1]>0){ 
           b[i]=1; 
           a[i-1]--; 
           a[i]--; 
           a[i+1]--; 
        } 
    } 
    for (int i=1;i<=n;i++) 
        if (a[i]!=0) return 0; 
    return 1; 
} 
  
int main(){ 
    scanf("%d",&n); 
    for (int i=1;i<=n;i++) scanf("%d",&a[i]),c[i]=a[i]; 
    printf("%d\n",check(1)+check(0)); 
}

