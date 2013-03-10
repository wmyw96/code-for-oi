#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;

const int MAX_N = 500001, MAX_M = 1000001, INF = -100000000;
int c[MAX_N], next[MAX_M], cost[MAX_M], g[MAX_M], ok[MAX_M], nm;
int s[MAX_N], pr[MAX_N];
int mxd[MAX_N], mark[MAX_N], lt, a[MAX_N];
int nowsize, prmn, ctr;
int n, ans, K, m;

struct data{
       int a, b;
};
bool operator < (data x, data y){
     return x.b < y.b;
}
priority_queue<data> Q;

data mp(int x, int y){
     data ret;
     ret.a = x;
     ret.b = y;
     return ret;
}

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

void dfs_getdep(int root, int i, int pre, int dep){
     if (mark[i]) dep++;
     if (dep > K) return;
     mxd[root] = max(mxd[root], dep);
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (j != pre && ok[k])
            dfs_getdep(root, j, i, dep);
     }
}

void dfs_calcans(int i, int pre, int dep, int cc){
     if (mark[i]) dep++;
     if (dep > K) return;
     int up = min(K - dep, lt);
     ans = max(ans, a[up] + cc);
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (j != pre && ok[k]){
            dfs_calcans(j, i, dep, cc + cost[k]);
         }
     }
}

void dfs_upd(int i, int pre, int dep, int cc){
     if (mark[i]) dep++;
     if (dep > K) return;
     a[dep] = max(a[dep], cc);
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (j != pre && ok[k]){
            dfs_upd(j, i, dep, cc + cost[k]);
         }
     }
}

void calc(int i){
     lt = 0;
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (ok[k]){
            mxd[j] = 0;
            dfs_getdep(j, j, i, mark[i]);
            Q.push(mp(k, mxd[j]));
            lt = max(mxd[j], lt);
         }
     }
     
     data ret = Q.top();
     for (int k = 0; k <= lt; ++k) a[k] = 0; // mistaken : a[k] = INF
     while (!Q.empty()){
           ret = Q.top();Q.pop();
           int k = ret.a;
           int j = g[k];
           dfs_calcans(j, i, 0, cost[k]); //mistaken : dfs_calcans(j, i, 1, cost[k]);
           dfs_upd(j, i, mark[i], cost[k]);
           int mxn = INF;
           if (ret.b <= lt / 2){
              for (k = mark[i]; k <= ret.b; ++k) mxn = max(mxn, a[k]);
              for (int k = lt - ret.b; k <= lt - mark[i]; ++k) a[k] = max(a[k], mxn);
           }
           else
              for (int k = 1; k <= lt; ++k) a[k] = max(a[k], a[k - 1]);
     }
     
     findroot(i, -1);
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
    scanf("%d%d%d", &n, &K, &m);
    memset(c, -1, sizeof c);
    int x;
    for (int i = 1; i <= m; ++i) scanf("%d", &x), mark[x] = 1;
    for (int i = 1; i < n; ++i){
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        addedge(x, y, w);
        addedge(y, x, w);
    }
    ans = 0;
    nowsize = prmn = n;
    findroot(1, -1);
    calc(ctr);
    printf("%d\n", ans);
}

/*
10 2 5
7
8
2
4
9
2 1 0
3 2 4
4 1 0
5 2 6
6 2 8
7 5 5
8 2 1
9 4 7
10 4 2
3729
*/
