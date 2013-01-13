/************************************************************** 
    Problem: 1090 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:36 ms 
    Memory:1312 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
  
using namespace std; 
  
const int MAX_L=101; 
  
char st[MAX_L]; 
int f[MAX_L][MAX_L]; 
  
int check(int s,int len,int k){ 
    if (len%k) return 0; 
    for (int i=0;i<len;i++) 
        if (st[i+s]!=st[i%k+s]) return 0; 
    return 1; 
} 
  
int calc(int x){ 
    int ret=0; 
    while (x){ 
          x/=10; 
          ret++; 
    } 
    return ret; 
} 
  
int dfs(int l,int r){ 
    if (f[l][r]) return f[l][r]; 
    int len=r-l+1; 
    int ret=len; 
    if (ret==1) return f[l][r]=ret; 
    for (int k=l;k<r;k++) ret=min(ret,dfs(l,k)+dfs(k+1,r)); 
    for (int k=1;k<len;k++) 
        if (check(l-1,len,k)) ret=min(ret,dfs(l,l+k-1)+calc(len/k)+2); 
    return f[l][r]=ret; 
} 
  
int main(){ 
    scanf("%s",&st); 
    int l=strlen(st); 
    printf("%d\n",dfs(1,l)); 
}
