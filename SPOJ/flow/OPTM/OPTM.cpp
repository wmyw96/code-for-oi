#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAX_N = 510, MAX_M = 20001, INF = 2147483647;
int n, m, nm, S, T, K;
int g[MAX_M], next[MAX_M], c[MAX_N], flow[MAX_M];
int d[MAX_N], Q[MAX_M];
int ans[MAX_N], x[MAX_M], y[MAX_M], p[MAX_N], a[MAX_N];

void addedge(int x, int y, int w){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     flow[nm] = w;
     nm++;
}

int bfs(){
    memset(d, -1, sizeof d);
    Q[1] = S;
    d[S] = 0;
    for (int l = 1, r = 1; l <= r; ++l){
        int i = Q[l];
        for (int k = c[i]; k != -1; k = next[k]){
            int j = g[k];
            if (flow[k] && d[j] == -1) d[j] = d[i] + 1, Q[++r] = j;
        }
    }
    return d[T] != -1;
}

int dfs(int i, int now){
    if (!now) return 0;
    if (i == T) return now;
    int w = 0;
    for (int k = c[i]; k != -1 && w < now; k = next[k]){
        int j = g[k], rst = min(now - w, flow[k]), ret = 0;
        if (d[j] == d[i] + 1)
           if ((ret = dfs(j, rst)) > 0){
              flow[k] -= ret;
              flow[k ^ 1] += ret;
              w += ret;
           }
    }
    if (!w) d[i] = -1;
    return w;
}

int main(){
    int Ti;
    scanf("%d", &Ti);
    while (Ti--){
          scanf("%d%d", &n, &m);
          for (int i = 1; i <= m; ++i)
              scanf("%d%d", &x[i], &y[i]);
          S = n + 1;
          T = n + 2;
          scanf("%d", &K);
          for (int i = 1; i <= K; ++i)
              scanf("%d%d", &p[i], &a[i]);
          memset(ans, 0, sizeof ans);
          for (int k = 0; k <= 30; ++k){
              int pp = (1<<k);
              nm = 0;
              memset(c, -1, sizeof c);
              for (int i = 1; i <= m; ++i)
                  addedge(x[i], y[i], 1), addedge(y[i], x[i], 1);
              for (int i = 1; i <= K; ++i)
                  if (a[i] & pp){
                     addedge(S, p[i], INF);
                     addedge(p[i], S, 0);
                  }
                  else{
                       addedge(p[i], T, INF);
                       addedge(T, p[i], 0);
                  }
              int ans1 = 0;
              while (bfs()) ans1 += dfs(S, INF);
              for (int i = 1; i <= n; ++i)
                  if (d[i] != -1) ans[i] |= 1 << k;
          }
          for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
    }
}

           
