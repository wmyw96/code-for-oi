#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 200001, MAX_M = 500001, MAX_L = 1000001, SUP = 1000000000;
int c[MAX_N], next[MAX_M], cost[MAX_M], g[MAX_M], ok[MAX_M], nm;
int s[MAX_N], pr[MAX_N], d[MAX_N];
int h[MAX_L], stack[MAX_L], top;
int nowsize, prmn, ctr;
int n, ans, K;

void addedge(int x, int y, int w){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     cost[nm] = w;
     ok[nm] = 1;
     nm++;
}

void findroot(int i, int pre){
     s[i] = 1, pr[i] = 0;
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (j != pre && ok[k]){
            findroot(j, i);
            s[i] += s[j];
            pr[i] = max(pr[i], s[j]);
         }
     }
     pr[i] = max(pr[i], nowsize - s[i]);
     if (pr[i] < prmn) prmn = pr[i], ctr = i;
}

void dfs(int i, int pre, int len){
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (j != pre && ok[k]){
            d[j] = d[i] + cost[k];
            if (d[j] <= K){
               if (h[K - d[j]] > -1) ans = min(len + h[K - d[j]], ans);
            }
            dfs(j, i, len + 1);
         }
     }
}

void dfs2(int i, int pre, int len){
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (j != pre && ok[k]){
            d[j] = d[i] + cost[k];
            if (d[j] <= K){
               if (h[d[j]] > -1) h[d[j]] = min(h[d[j]], len);
               else h[d[j]] = len, stack[++top] = d[j];
            }
            dfs2(j, i, len + 1);
         }
     }
}

void clear(){
     while (top){
           h[stack[top--]] = -1;
     }
}

void calc(int i){
     h[0] = 0;
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (ok[k]){
            d[j] = cost[k];
            if (d[j] <= K){
               if (h[K - d[j]] > -1) ans = min(1 + h[K - d[j]], ans);
            }
            dfs(j, i, 2);
            dfs2(j, i, 2);            
            if (d[j] <= K){
               if (h[d[j]] > -1) h[d[j]] = min(h[d[j]], 1);
               else h[d[j]] = 1, stack[++top] = d[j];
            }
         }
     }
     clear();
     //findroot(i, -1);
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (ok[k]){
            ok[k ^ 1] = 0;
            nowsize = prmn = s[j];
            findroot(j, -1);
            calc(ctr);
         }
     }
}
            
int main(){
    scanf("%d%d", &n, &K);
    memset(c, -1, sizeof c);
    for (int i = 0; i < MAX_L; ++i) h[i] = -1;
    for (int i = 1; i < n; ++i){
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        x++; y++;
        addedge(x, y, w);
        addedge(y, x, w);
    }
    ans = SUP;
    nowsize = prmn = n;
    findroot(1, -1);
    calc(ctr);
    
    if (ans != SUP) printf("%d\n", ans); else printf("%d\n", -1);
}

/*
7 4
1 2 1
2 3 1
2 4 1
1 5 1
5 6 1
5 7 1

*/
