/************************************************************** 
    Problem: 1085 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:2360 ms 
    Memory:1272 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
using namespace std; 
int n,ans,limit; 
int a[6][6],b[6][6]; 
const int fl[6][6] = { 
0,0,0,0,0,0, 
0,2,2,2,2,2, 
0,1,2,2,2,2, 
0,1,1,0,2,2, 
0,1,1,1,1,2, 
0,1,1,1,1,1 
}; 
const int fx[8] = {-2, -2, -1, -1, 1, 1, 2, 2},  
          fy[8] = {-1, 1, -2, 2, -2, 2, -1, 1}; 
  
int S(){ 
    int ret=0; 
    for (int i=1;i<=n;i++) 
        for (int j=1;j<=n;j++) ret+=(a[i][j]!=fl[i][j] && a[i][j] && fl[i][j]); 
    return ret; 
} 
              
void dfs(int x,int y,int dep){ 
     int ret=S(); 
     if (ret==0 && a[3][3]==0) {ans=dep;return;} 
     if (limit-dep<ret) return; 
     for (int k=0;k<8;k++){ 
         int xx=x+fx[k]; 
         int yy=y+fy[k]; 
         if (xx>0 && yy>0 && xx<=n && yy<=n){ 
            int tmp=a[x][y];int tmp1=a[xx][yy]; 
            a[xx][yy]=tmp;a[x][y]=tmp1; 
            dfs(xx,yy,dep+1); 
            if (ans!=-1) return; 
            a[x][y]=tmp;a[xx][yy]=tmp1; 
         } 
     } 
} 
       
int main(){ 
    int T; 
    int sx,sy;char ch; 
    scanf("%d",&T); 
    n=5; 
    while (T--){ 
          for (int i=1;i<=n;i++){ 
              getchar(); 
              for (int j=1;j<=n;j++){ 
                  ch=getchar(); 
                  if (ch=='*') a[i][j]=0,sx=i,sy=j; 
                     else a[i][j]=ch-'0'+1; 
              } 
          } 
          ans=-1; 
          for (int dep=1;dep<=15;dep++){ 
              for (int i=1;i<=n;i++) 
                  for (int j=1;j<=n;j++) b[i][j]=a[i][j]; 
              limit=dep; 
              dfs(sx,sy,0); 
              if (ans>=0) break; 
              for (int i=1;i<=n;i++) 
                  for (int j=1;j<=n;j++) a[i][j]=b[i][j]; 
          } 
          printf("%d\n",(ans>15) ? - 1 : ans ); 
    } 
}

