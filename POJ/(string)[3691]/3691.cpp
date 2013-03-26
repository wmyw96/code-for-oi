#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAX_N = 1111, INF = 1000000000;
int F[MAX_N][MAX_N], nxt[MAX_N][4], ok[MAX_N], f[MAX_N], Q[MAX_N];
int n, m, tot;
char st[MAX_N];

int gt(char ch){
    if (ch == 'A') return 0;
    if (ch == 'C') return 1;
    if (ch == 'G') return 2;
    if (ch == 'T') return 3;
}

int main1(int Ti){
    memset(nxt[0], 0, sizeof nxt[0]);
    memset(ok, 0, sizeof ok);
    memset(f, 0, sizeof f);
    tot = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i){
        scanf("%s", &st);
        int l = strlen(st);
        int p = 0;
        for (int j = 0; j < l; ++j){
            int c = gt(st[j]);
            if (!nxt[p][c]){
               nxt[p][c] = ++tot;
               memset(nxt[tot], 0, sizeof nxt[tot]);
            }
            p = nxt[p][c];
        }
        ok[p] = 1;
    }
    
    int l = 1, r = 0;
    for (int k = 0; k < 4; ++k)
        if (nxt[0][k]) Q[++r] = nxt[0][k];
    for (; l <= r; ++l){
        int i = Q[l];
        for (int k = 0; k < 4; ++k){
            int p = f[i], q = nxt[i][k];
            while (p && !nxt[p][k]) p = f[p];
            if (q){
                   f[q] = nxt[p][k];
                   ok[q] |= ok[f[q]];
                   Q[++r] = q;
            }
            else nxt[i][k] = nxt[p][k];
        }
    }
    scanf("%s", &st);
    m = strlen(st);
    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= tot; ++j)
            F[i][j] = -1;
    F[0][0] = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j <= tot; ++j)
          if (F[i][j] != -1){
            for (int k = 0; k < 4; ++k){
                int c = gt(st[i]), q = nxt[j][k];
                int ret = F[i][j] + (k != c);
                if (!ok[q])
                   F[i + 1][q] = (F[i + 1][q] == -1) ? (ret) : (min(ret, F[i + 1][q]));
            }
          }
    int ans = INF;
    for (int i = 0; i <= tot; ++i)
        if (F[m][i] != -1) ans = min(F[m][i], ans);
    printf("Case %d: ", Ti);
    if (ans != INF) printf("%d\n", ans); else printf("-1\n");
}

int main(){
    int Ti = 1;
    while (scanf("%d", &n) != EOF){
          if (n == 0) return 0;
          main1(Ti);
          Ti++;
    }
}
