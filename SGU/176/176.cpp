#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 201, MAX_M = 30001, INF = 1000000000;
int flow[MAX_M], g[MAX_M], next[MAX_M], c[MAX_N], nm;
int Q[MAX_M], d[MAX_N];
int x[MAX_M], y[MAX_M], w[MAX_M], mk[MAX_M], mark[MAX_M];
int X, Y, S, T, n, m, ans, ans1, ans_can, ans_back;

void addedge(int x, int y, int w){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     flow[nm] = w;
     nm++;
}

void add(int x, int y, int w){
     //printf("%d %d %d\n", x, y, w);
     addedge(x, y, w);
     addedge(y, x, 0);
}

int bfs(){
    memset(d, -1, sizeof d);
    d[S] = 0, Q[1] = S;
    for (int l = 1, r = 1; l <= r; ++l){
        int i = Q[l];
        for (int k = c[i]; k != -1; k = next[k]){
            int j = g[k];
            if (flow[k] && d[j] == -1) Q[++r] = j, d[j] = d[i] + 1;
        }
    }
    return d[T] != -1;
}

int dfs(int i, int now){
    if (now == 0) return now;
    if (i == T) return now;
    int w = 0;
    for (int k = c[i]; k != -1 && w < now; k = next[k]){
        int j = g[k], rst = min(now - w, flow[k]), ret;
        if (flow[k] && d[j] == d[i] + 1)
           if ((ret = dfs(j, rst)) > 0){
              flow[k] -= ret;
              flow[k ^ 1] += ret;
              w += ret;
           }
    }
    if (!w) d[i] = -1;
    return w;
}

void build(){
     memset(c, -1, sizeof c);
     X = n + 1, Y = n + 2;
     ans1 = 0;
     for (int i = 1; i <= m; ++i){
         if (mk[i] == 1){
            add(Y, y[i], w[i]);
            add(x[i], X, w[i]);
            ans1 += w[i];
         }
         else add(x[i], y[i], w[i]), mark[i] = nm - 1;
     }
     add(n, 1, INF);
     S = Y, T = X;
     while (bfs()){
           ans += dfs(S, INF);
     }
     if (ans < ans1) {printf("Impossible\n"); return;}
     ans_can = flow[nm - 1];
     flow[nm - 2] = flow[nm - 1] = 0;
     S = n, T = 1;
     while (bfs()){
           ans_back += dfs(S, INF);
     }
     if (ans_can >= ans_back){
        printf("%d\n", ans_can - ans_back);
     }
     else{
          printf("0\n");
          S = Y, T = n;
          addedge(S, 1, ans_back - ans_can);
          while (bfs()){
                dfs(S, INF);
          }
     }
     for (int i = 1; i < m; ++i){
         if (mk[i]) printf("%d ", w[i]); else printf("%d ", flow[mark[i]]);
     }
     if (mk[m]) printf("%d\n", w[m]); else printf("%d\n", flow[mark[m]]);
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d%d", &x[i], &y[i], &w[i], &mk[i]);
    build();
    //system("pause");
}
