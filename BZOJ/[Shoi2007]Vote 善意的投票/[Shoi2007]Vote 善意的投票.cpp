#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 10001, MAX_M = 300001, INF = 1000000000;
int flow[MAX_M], d[MAX_N], g[MAX_M], next[MAX_M], c[MAX_N], nm, Q[MAX_M];
int n, m, S, T, t0, t1;

int bfs(){
    memset(d, -1, sizeof d);
    d[S] = 0;
    Q[1] = S;
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
    if (i == T) return now;
    if (!now) return now;
    int w = 0;
    for (int k = c[i]; k != -1 && w < now; k = next[k]){
        int j = g[k], rst = min(flow[k], now - w), ret;
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

void addedge(int x, int y, int w){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     flow[nm] = w;
     nm++;
}

void add(int x, int y, int w1, int w2){
     addedge(x, y, w1);
     addedge(y, x, w2);
}

int main(){
    scanf("%d%d", &n, &m);
    memset(c, -1, sizeof c);
    // 0 : n + 1, 1 : n + 2, S : n + 3, T : n + 4
    S = n + 3;
    T = n + 4;
    t0 = n + 1;
    t1 = n + 2;
    add(t1, T, INF, 0);
    add(S, t0, INF, 0);
    for (int i = 1; i <= n; ++i){
        int x;
        scanf("%d", &x);
        if (x) add(i, t1, 1, 0);
          else add(t0, i, 1, 0);
    }
    for (int i = 1; i <= m; ++i){
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y, 1, 1);
    }
    int ans = 0;
    while (bfs())
          ans += dfs(S, INF);
    printf("%d\n", ans);
}
