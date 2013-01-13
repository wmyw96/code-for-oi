/************************************************************** 
    Problem: 1024 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:172 ms 
    Memory:1272 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
  
using namespace std; 
  
typedef double LD; 
  
LD dfs(LD x,LD y,int n){ 
   if (x<y) { LD tmp=x;x=y;y=tmp;} 
   if (n==1) return x/y; 
   LD tmp=(LD)1.0/n; LD ret=10000.0; 
   for (int i=1;i<n;i++){ 
       ret=min(ret,max(dfs(x*tmp*i,y,i),dfs(x-x*tmp*i,y,n-i))); 
       ret=min(ret,max(dfs(x,y*tmp*i,i),dfs(x,y-y*tmp*i,n-i))); 
   } 
   return ret; 
} 
int main(){ 
    LD x,y;int n; 
    scanf("%lf %lf %d",&x,&y,&n); 
    printf("%.6f\n",dfs(x,y,n)); 
}

