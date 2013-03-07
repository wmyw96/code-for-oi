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

struct data{
       int a, b;
};
bool operator < (data x, data y){
     return x.b < y.b;
}

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
     mxd[root] = max(mxd[root], dep);
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (j != pre && ok[k])
            dfs_getdep(root, j, i, dep);
     }
}

void dfs_calcans(int i, int pre, int dep, int cc){
     if (mark[i]) dep++;
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
     a[dep] = max(a[dep], cc);
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (j != pre && ok[k]){
            dfs_upd(j, i, dep, cc + cost[k]);
         }
     }
}

void calc(int i){
     while (!Q.empty()) Q.pop();
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (ok[k]){
            mxd[j] = 0;
            dfs_getdep(j, j, i, mark[i]);
            Q.push(mp(j, mxd[j]));
         }
     }
     data ret = Q.top();
     lt = ret.b;
     for (int i = 0; i <= lt; ++i) a[i] = 0;
     while (!Q.empty()){
           ret = Q.top();
           j = ret.a;
           dfs_calcans(j, i, mark[i]), cost[k]);
           dfs_upd(j, i, mark[i], cost[k]);
           for (int k = 1; k <= ret.b; ++k) a[k] = max(a[k], a[k - 1]);
     }
     
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
    scanf("%d%d", &n, &m, &K);
    memset(c, -1, sizeof c);
    for (int i = 1; i <= m; ++i) scanf("%d", &x), mark[x] = 1;
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
