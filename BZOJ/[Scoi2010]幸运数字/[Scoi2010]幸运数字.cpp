/************************************************************** 
    Problem: 1853 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:464 ms 
    Memory:2060 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cmath> 
#include<cstring> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
typedef unsigned long long LL; 
   
int tot; 
LL ans,a,b,last; 
LL num[101]; 
LL key[100001]; 
   
LL gcd(LL a,LL b){ 
    while (b){ 
          LL r=a%b;a=b;b=r; 
    } 
    return a; 
} 
   
void dfs(LL now,int k,int dep){ 
     if (dep > tot) {         
        if (now!=1 && now<=b) 
              ans +=( (k % 2) ? 1 : -1 ) * (b / now - (a - 1) / now); 
        return ; 
     } 
     if ((LL)key[dep]/gcd(key[dep],now)*now<=b) dfs((LL)now/gcd(key[dep],now)*key[dep],k+1,dep+1); 
     dfs(now,k,dep+1); 
} 
   
int main(){ 
    cin>>a>>b; 
    num[0]=1; 
    for (int i=1;i<=11;i++) 
        num[i]=num[i-1]*10; 
    for (int i=1;i<=11;i++){ 
        for (int j=0;j<=(1<<i)-1;j++){ 
            LL n=0; 
            for (int k=0;k<i;k++) 
               if (j&(1<<k)) n+=num[k]*8; else n+=num[k]*6;  
            if (n>b) break; 
               
            key[++tot]=n; 
            for (int p=1;p<tot;p++) 
                if (key[tot] % key[p]==0){ tot--;break;} 
        } 
    } 
    sort(key,key+1+tot); 
    for (int i=1;i<=tot/2;i++) swap(key[i],key[tot-i+1]); 
    dfs(1,0,1); 
    cout<<ans<<endl; 
}

