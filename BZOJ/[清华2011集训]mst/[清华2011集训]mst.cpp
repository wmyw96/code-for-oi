#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;

const int MAX_N = 300001, MAX_M = 500001, SUP = 10000000;
struct gh{
       int x, y, w;
};
gh E[MAX_M];
int n, m, S, T, wt;
int d[MAX_N], Q[MAX_M], c[MAX_N], next[MAX_M], g[MAX_M], flow[MAX_M], nm;

int cmp(gh x, gh y){
    return x.w < y.w;
}

void addedge(int x, int y, int w){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     flow[nm] = w;
     nm++;
}

void add(int x, int y){
     addedge(x, y, 1);
     addedge(y, x, 1);
}

int bfs(){
    int l, r;
    memset(d, -1, sizeof d);
    d[S] = 0;
    Q[l = r = 1] = S;
    while (l <= r){
          int i = Q[l++];
          for (int k = c[i]; k != -1; k = next[k]){
              int j = g[k];
              if (d[j] == -1 && flow[k]){
                 d[j] = d[i] + 1;
                 Q[++r] = j;
              }
          }
    }
    return d[T] != -1;
}

int dfs(int i, int now){
    if (!now) return 0;
    if (i == T) return now;
    int w = 0;
    for (int k = c[i]; k != -1 && w < now; k = next[k]){
        int j = g[k];
        int rst = min(flow[k] ,now - w), ret = 0;
        if (d[j] == d[i] + 1)
           if (rst && (ret = dfs(j, rst)) > 0){
              flow[k] -= ret;
              flow[k ^ 1] += ret;
              w += ret;
           }
    }
    if (!w) d[i] = -1;
    return w;
}

void clear(){    
     nm = 0;
     memset(c, -1, sizeof c);
     memset(next, 0, sizeof next);
     memset(g, 0, sizeof g);
     memset(flow, 0, sizeof flow);
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &E[i].x, &E[i].y, &E[i].w);
    sort(E + 1, E + 1 + m, cmp);
    scanf("%d%d%d", &S, &T, &wt);
    
    clear();
    for (int i = 1; i <= m; ++i)
        if (E[i].w < wt) add(E[i].x, E[i].y);
    int ans = 0;
    
    while (bfs()){
          while (1){
                int ret = dfs(S, SUP);
                if (!ret) break; else ans += ret;
          }
    }
    clear();
    for (int i = 1; i <= m; ++i)
        if (E[i].w > wt) add(E[i].x, E[i].y);
    
    while (bfs()){
          while (1){
                int ret = dfs(S, SUP);
                if (!ret) break; else ans += ret;
          }
    }
    printf("%d\n", ans);
}

/*
4 5
1 2 10
1 3 5
3 4 9
1 4 1
3 2 3
4 3 5
*/
