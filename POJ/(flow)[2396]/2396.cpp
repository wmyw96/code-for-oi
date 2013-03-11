#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 801, MAX_M = 1600001, INF = 100000000;

int n, m, S, T, s, t, X, Y, k;
int nm, g[MAX_M], next[MAX_M], c[MAX_N], flow[MAX_M];
int Q[MAX_M], d[MAX_N];
int ans_li[MAX_N][MAX_N];
int al[MAX_N][MAX_N], ar[MAX_N][MAX_N];

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

int work(){
    scanf("%d%d", &n, &m);
    s = n + m + 1;
    t = n + m + 2;
    X = t + 1;
    Y = t + 2;
    int x;
    memset(c, -1, sizeof c);
    nm = 0;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &x), add(s, i, x);
    for (int i = 1; i <= m; ++i)
        scanf("%d", &x), add(i + n, t, x);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            al[i][j] = 0, ar[i][j] = INF;
    scanf("%d", &k);
    int ans = 1;
    for (int p = 1; p <= k; ++p){
        int x, y, num; char ch;
        scanf("%d%d %c %d", &x, &y, &ch, &num);
        if (ch == '='){
           if (!x)
              for (int i = 1; i <= n; ++i)
                  if (!y)
                     for (int j = 1; j <= m; ++j)
                         if (al[i][j] <= num && num <= ar[i][j]) al[i][j] = ar[i][j] = num; else ans = 0;
                  else 
                     for (int j = y; j <= y; ++j)
                         if (al[i][j] <= num && num <= ar[i][j]) al[i][j] = ar[i][j] = num; else ans = 0;
           else
               for (int i = x; i <= x; ++i)
                  if (!y)
                     for (int j = 1; j <= m; ++j)
                         if (al[i][j] <= num && num <= ar[i][j]) al[i][j] = ar[i][j] = num; else ans = 0;
                  else 
                     for (int j = y; j <= y; ++j)
                         if (al[i][j] <= num && num <= ar[i][j]) al[i][j] = ar[i][j] = num; else ans = 0;
        }
        if (ch == '>'){
           num++;
           if (!x)
              for (int i = 1; i <= n; ++i)
                  if (!y)
                     for (int j = 1; j <= m; ++j)
                         if (ar[i][j] >= num) al[i][j] = max(al[i][j], num); else ans = 0;
                  else 
                     for (int j = y; j <= y; ++j)
                         if (ar[i][j] >= num) al[i][j] = max(al[i][j], num); else ans = 0;
           else
               for (int i = x; i <= x; ++i)
                  if (!y)
                     for (int j = 1; j <= m; ++j)
                         if (ar[i][j] >= num) al[i][j] = max(al[i][j], num); else ans = 0;
                  else 
                     for (int j = y; j <= y; ++j)
                         if (ar[i][j] >= num) al[i][j] = max(al[i][j], num); else ans = 0;      
        }
        if (ch == '<'){
           num--;
           if (!x)
              for (int i = 1; i <= n; ++i)
                  if (!y)
                     for (int j = 1; j <= m; ++j)
                         if (al[i][j] <= num) ar[i][j] = min(ar[i][j], num); else ans = 0;
                  else 
                     for (int j = y; j <= y; ++j)
                         if (al[i][j] <= num) ar[i][j] = min(ar[i][j], num); else ans = 0;
           else
               for (int i = x; i <= x; ++i)
                  if (!y)
                     for (int j = 1; j <= m; ++j)
                         if (al[i][j] <= num) ar[i][j] = min(ar[i][j], num); else ans = 0;
                  else 
                     for (int j = y; j <= y; ++j)
                         if (al[i][j] <= num) ar[i][j] = min(ar[i][j], num); else ans = 0;         
        }
    }
    if (!ans) printf("IMPOSSIBLE\n");
    else{
         ans = 0;
         int ans1 = 0, ans2 = 0;
         for (int i = 1; i <= n; ++i)
             for (int j = 1; j <= m; ++j)
                 add_2(i, j + n, al[i][j], ar[i][j]), ans1 += al[i][j];
         S = Y, T = X;
         addedge(t, s, INF);
         while (bfs()) ans += dfs(S, INF);
         if (ans == ans1){
            flow[nm - 1] = 0;
            S = s, T = t;
            while (bfs()) dfs(S, INF);
            for (int i = 1; i <= n; ++i)
                for (int k = c[i]; k != -1; k = next[k])
                    if (g[k] != s) ans_li[i][g[k] - n] = flow[k ^ 1] + al[i][g[k] - n];
            for (int i = 1; i <= n; ++i){
                for (int j = 1; j < m; ++j)
                    printf("%d ", ans_li[i][j]); 
                printf("%d\n", ans_li[i][m]);
            }
         }
         else printf("IMPOSSIBLE\n");
    }
}
                   
int main(){
    int Ti, TT;
    scanf("%d", &Ti); TT = Ti; 
    while (Ti--){
          if (Ti != TT - 1) scanf("\n");
          work();
          if (Ti != 0) printf("\n");
    }
}
