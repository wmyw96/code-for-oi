/************************************************************** 
    Problem: 1026 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:0 ms 
    Memory:1432 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
typedef long long LL; 
const int MAX_L=101,N=10; 
LL F[101][101],G[101][101]; 
int a[101]; 
int calc(int pre,int dep){ 
    if (dep==0){ 
              int ret=0; 
              for (int i=0;i<=a[dep];i++) 
                  if (abs(i-pre)>=2 && !(pre==-2 && i==0)) ret++; 
              //printf("%d %d \n",pre,ret); 
              return ret; 
    } 
    int num=dep;int p10=1;int first=a[dep]; 
    //printf("calc %d\n",num); 
    int ret=0; 
    for (int i=0;i<first;i++){ 
        if (abs(i-pre)>=2) 
           if (pre==-2 && i==0){ 
              for (int j=0;j<num;j++) 
                  for (int k=1;k<=9;k++) ret+=F[j+1][k]; 
           }  
           else ret+=F[num+1][i]; 
   
    } 
    return ret+((abs(first-pre)>=2) ? calc(first,dep-1) : 0); 
} 
   
int calc(int N){ 
    if (N==0) return 0; 
    memset(a,0,sizeof a); 
    int tot=0; 
    for (;N;N/=10) a[tot++]=N%10; 
    //for (int i=1;i<=tot/2;i++) swap(a[i],a[tot-i+1]); 
    //printf("-- %d\n",tot-1); 
    return calc(-2,tot-1); 
} 
  
int main(){ 
    int aa,bb; 
    scanf("%d%d",&aa,&bb); 
    for (int i=0;i<10;i++) F[1][i]=1; 
    for (int i=2;i<=N+1;i++) 
        for (int j=0;j<10;j++) 
            for (int k=0;k<10;k++) 
                if (abs(j-k)>=2) F[i][j]+=F[i-1][k]; 
    printf("%d\n",calc(bb)-calc(aa-1)); 
    //system("pause"); 
}
