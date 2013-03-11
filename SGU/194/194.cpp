#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 301, MAX_M = 160001, INF = 100000000;

int n, m, S, T;
int nm, g[MAX_M], next[MAX_M], c[MAX_N], flow[MAX_M], mark[MAX_M], x[MAX_M], y[MAX_M], wl[MAX_M], wr[MAX_M];
int Q[MAX_M], d[MAX_N];

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
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d%d", &x[i], &y[i], &wl[i], &wr[i]);
    S = n + 1, T = n + 2;
    int ans1 = 0;
    memset(c, -1, sizeof c);
    for (int i = 1; i <= m; ++i){
        add(S, y[i], wl[i]);
        add(x[i], T, wl[i]);
        ans1 += wl[i];
        add(x[i], y[i], wr[i] - wl[i]);
        mark[i] = nm - 1;
    }
    int ans = 0;
    while (bfs()){
          ans += dfs(S, INF);
    }
    if (ans != ans1) printf("NO\n");
    else{
         printf("YES\n");
         for (int i = 1; i <= m; ++i)
             printf("%d\n", flow[mark[i]] + wl[i]);
    }
    //system("pause");
}
