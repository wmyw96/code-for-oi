#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
  
const int MAX_T = 7001, MAX_N = 201, MOD = 10007;
int nxt[MAX_T][26];
int f[MAX_T], ok[MAX_T];
int F[2][MAX_N][MAX_T], Q[MAX_T];
char st[MAX_N];
int n, m, tot;
  
int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i){
         scanf("%s", &st);
         int l = strlen(st);
         int p = 0;
         for (int j = 0; j < l; ++j){
             int c = st[j] - 'A';
             if (!nxt[p][c]) nxt[p][c] = ++tot;
             p = nxt[p][c];
         }
         ok[p] = 1;
    }
    int l = 1, r = 0;
    for (int k = 0; k < 26; ++k)
        if (nxt[0][k]) Q[++r] = nxt[0][k], f[nxt[0][k]] = 0;
    for (; l <= r; ++l){
        int i = Q[l];
        for (int k = 0; k < 26; ++k){
               int p = i, q = nxt[i][k];
               p = f[p];
               while (!nxt[p][k] && p) p = f[p];
               if (nxt[i][k]){
                  f[q] = nxt[p][k];
                  Q[++r] = q;
                  ok[q] |= ok[f[q]];
               }
               else nxt[i][k] = nxt[p][k];
        }
    }
    F[0][0][0] = 1;
    for (int p = 0; p < 2; ++p)
        for (int i = 0; i < m; ++i)
            for (int j = 0; j <= tot; ++j)
                if (F[p][i][j])
                   for (int k = 0; k < 26; ++k){
                       F[p | ok[nxt[j][k]]][i + 1][nxt[j][k]] += F[p][i][j];
                       F[p | ok[nxt[j][k]]][i + 1][nxt[j][k]] %= MOD;
                   }
    int ans = 0;
    for (int i = 0; i <= tot; ++i){
        ans += F[1][m][i];
        ans %= MOD;
    }
    printf("%d\n", ans);
    //system("pause");
}
