#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;
struct O_O{
       int i;
       LL dd;
};
 
 
const int MAX_N = 10000 * 21 + 1, MAX_M = 50000 * 4 * 21 + 1;
const LL INF = 100000000000000LL;
int n, m, k, N, nm, pp;
LL d[MAX_N];
int cost[MAX_M], g[MAX_M], c[MAX_N], next[MAX_M];
int ok[MAX_N];
int x[50001], y[50001], w[50001];
 
bool operator < (O_O x, O_O y){
     return x.dd > y.dd;
}
priority_queue<O_O> Q;
 
O_O T_T(int i, LL dd){
    O_O ret;
    ret.i = i;
    ret.dd = dd;
    return ret;
}
 
int nd(int i, int j){
    return i * n + j;
}
 
void work(){
     d[1] = 0;
     ok[1] = 0;
     Q.push(T_T(1, d[1]));
      
     for (int i = 2; i <= N; ++i){
         d[i] = INF;
         ok[i] = 0;
         //Q.push(T_T(i, d[i]));
     }
      
     for (; !Q.empty();){
         O_O p; p = Q.top();
         int i = p.i;
         for (int kk = c[i]; kk != -1; kk = next[kk]){
             int j = g[kk];
             if (d[i] + cost[kk] < d[j]){
                d[j] = d[i] + cost[kk];
                Q.push(T_T(j, d[j]));
             }
         }
         ok[i] = 1;
         pp++;
         p = Q.top();
         while (ok[p.i] && !Q.empty()) Q.pop(), p = Q.top();
     }
     LL ans = INF;
     for (int i = 0; i <= k; ++i)
         ans = min(ans, d[nd(i, n)]);
     cout<<ans<<endl;
}
 
void addedge(int x, int y, int w){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     cost[nm] = w;
     nm++;
}
 
int main(){
     
    memset(c, -1, sizeof c);
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &x[i], &y[i], &w[i]);
     
    for (int i = 0; i <= k; ++i){
        for (int j = 1; j <= m; ++j){
            addedge(nd(i, x[j]), nd(i, y[j]), w[j]);
            addedge(nd(i, y[j]), nd(i, x[j]), w[j]);
        }
        if (i != 0){
           for (int j = 1; j <= m; ++j){
               addedge(nd(i - 1, x[j]), nd(i, y[j]), 0);
               addedge(nd(i - 1, y[j]), nd(i, x[j]), 0);
           }
        }
    }
    N = (k + 1) * n;
    work();
}
