#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 601, MAX_M = 160001, INF = 100000000;

int n, m, S, T, s, t, X, Y;
int nm, g[MAX_M], next[MAX_M], c[MAX_N], flow[MAX_M];
int Q[MAX_M], d[MAX_N];
int ans_li[MAX_N][MAX_N], num[MAX_N];

void addedge(int x, int y, int w){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     flow[nm] = w;
     nm++;
}

void add(int x, int y, int w){
     addedge(x, y, w);
     addedge(y, x, 0);
}

void add_2(int x, int y, int wl, int wr){
     add(Y, y, wl);
     add(x, X, wl);
     add(x, y, wr - wl);
}

int bfs(){
    memset(d, -1, sizeof d);
    d[S] = 0, Q[1] = S;
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
    if (now == 0) return now;
    int w = 0;
    for (int k = c[i]; k != -1 && w < now; k = next[k]){
        int j = g[k], rst = min(now - w, flow[k]), ret = 0;
        if (d[j] == d[i] + 1 && rst)
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
    scanf("%d%d", &n, &m);
    s = n + m + 1;
    t = n + m + 2;
    X = t + 1;
    Y = X + 1;
    memset(c, -1, sizeof c);
    for (int i = 1; i <= n; ++i){
        add(s, i, 1);
        int wt, j;
        scanf("%d", &wt);
        while (wt--){
              scanf("%d", &j);
              add(i, j + n, 1);
        }
    }
    for (int i = 1; i <= m; ++i)
        add_2(i + n, t, 2, INF);
    addedge(t, s, INF);
    int ans1 = m * 2, ans = 0;
    S = Y, T = X;
    while (bfs()){
          ans += dfs(S, INF);
    }
    if (ans == ans1){
       printf("YES\n");
       S = s, T = t;
       flow[nm - 1] = 0;
       while (bfs()){
             dfs(S, INF);
       }
       for (int i = 1; i <= n; ++i)
           for (int k = c[i]; k != -1; k = next[k])
               if (g[k] != s && flow[k ^ 1]) ans_li[g[k] - n][++num[g[k] - n]] = i;
       for (int i = 1; i <= m; ++i){
           printf("%d", num[i]);
           for (int j = 1; j <= num[i]; ++j)
               printf(" %d", ans_li[i][j]);
           printf("\n");
       }
    }
    else printf("NO\n");
    //system("pause");
}
