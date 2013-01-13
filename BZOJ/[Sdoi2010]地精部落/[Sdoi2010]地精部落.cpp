/************************************************************** 
    Problem: 1925 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:1788 ms 
    Memory:1336 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstdlib> 
using namespace std; 
  
typedef long long LL; 
const int MAX_N=4201; 
int n; 
int C[MAX_N],c[MAX_N]; 
int f[MAX_N][2]; 
int MOD; 
  
int main(){; 
  
    scanf("%d%d",&n,&MOD); 
      
    c[0]=1;c[1]=2;c[2]=1; 
      
    f[1][0]=f[1][1]=f[0][0]=f[0][1]=f[2][0]=f[2][1]=1; 
      
    for (int i=3;i<=n;i++){ 
          
        C[0]=1; 
        for (int j=1;j<=i;j++) C[j]=(c[j-1]+c[j])%MOD; 
          
        for (int k=0;k<i;k++){ 
            LL x=0; 
            x =(LL) c[ k ] * f[ k ][ 0 ] % MOD * f[ i - k - 1 ][ ( i + k ) % 2] % MOD; 
              
            f[ i ][ (i + k) % 2] =( f[ i ][ (i + k) % 2] + x )% MOD; 
        } 
          
        for (int j=1;j<=i;j++) c[j]=C[j]; 
    } 
      
    int ans=(f[n][0]+f[n][1]) % MOD; 
      
    printf("%d\n",ans); 
      
    //system("pause"); 
}

