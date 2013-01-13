/************************************************************** 
    Problem: 1008 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:0 ms 
    Memory:1272 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cmath> 
#include<cstring> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
  
typedef long long LL; 
const LL MOD=100003; 
  
LL sqr(LL x){ 
   return  x*x; 
} 
LL calc(LL x,LL n){ 
   if (n==1) return x; 
   LL ret=sqr(calc(x,n/2))%MOD; 
   return ret * ((n%2) ? x : 1) %MOD; 
} 
  
int main(){ 
    LL n,m; 
    cin>>m>>n; 
    LL p=calc(m,n); 
    LL q=calc(m-1,n-1)*m%MOD; 
    cout<<((p-q>=0) ? (p-q) : (p-q+MOD))<<endl; 
}

