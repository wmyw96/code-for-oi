/************************************************************** 
    Problem: 1055 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:6252 ms 
    Memory:7184 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<cmath> 
#include<cstdlib> 
#include<algorithm> 
  
using namespace std; 
  
const int N=5,MAX_N=501; 
char st[MAX_N]; 
int F[MAX_N][MAX_N][N]; 
int Done[MAX_N][MAX_N]; 
int ch[N][MAX_N][3]; 
int c[N]; 
char ans[101]; 
int ansn; 
  
int Deal(char x){ 
    if (x=='W') return 1; 
    if (x=='I') return 2; 
    if (x=='N') return 3; 
    if (x=='G') return 4; 
} 
  
void dfs(int l,int r){ 
     if (Done[l][r]) return; 
     Done[l][r]=1; 
     if (l==r) F[l][r][Deal(st[l-1])]=1; 
     for (int i=1;i<N;i++) 
        for (int j=1;j<=c[i];j++) 
            for (int k=l;k<r;k++){ 
                dfs(l,k); 
                dfs(k+1,r); 
                if (F[l][k][ch[i][j][0]] && F[k+1][r][ch[i][j][1]]) 
                   F[l][r][i]=1; 
            } 
} 
  
int main(){ 
    scanf("%d%d%d%d",&c[1],&c[2],&c[3],&c[4]); 
    for (int i=1;i<N;i++) 
        for (int j=1;j<=c[i];j++){ 
            char ch1,ch2; 
            scanf(" %c%c",&ch1,&ch2); 
            ch[i][j][0]=Deal(ch1); 
            ch[i][j][1]=Deal(ch2); 
        } 
    scanf("%s",&st); 
    int n=strlen(st); 
    dfs(1,n); 
    if (F[1][n][1]) ans[ansn++]='W'; 
    if (F[1][n][2]) ans[ansn++]='I'; 
    if (F[1][n][3]) ans[ansn++]='N'; 
    if (F[1][n][4]) ans[ansn++]='G'; 
    if (ansn) printf("%s\n",ans); else printf("The name is wrong!\n"); 
}

