#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAX_N = 2001, MAX_M = 100001;
double SUP = 1000000000.0, EPS = 1e-9;
int nm, n, m, S, T, g[MAX_M], next[MAX_M], c[MAX_N], d[MAX_N], Q[MAX_N];
double flow[MAX_M];
int x[MAX_N], y[MAX_N], ans_list[MAX_N], ansn, vd[MAX_N];

int ge(int i){
    return i;
}
int gv(int i){
    return i + m;
}

void addedge(int x, int y, double w){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     flow[nm] = w;
     nm++;
}

void add(int x, int y, double w){
     addedge(x, y, w);
     addedge(y, x, 0.0);
}

int bfs(){
    memset(d, -1, sizeof d);
    d[S] = 0;
    Q[1] = S;
    for (int l = 1, r = 1; l <= r; ++l){
        int i = Q[l];
        for (int k = c[i]; k != -1; k = next[k]){
            int j = g[k];
            if (d[j] == -1 && flow[k] > EPS)
               d[j] = d[i] + 1, Q[++r] = j;
        }
    }
    return d[T] != -1;
}

double dfs(int i, double now){
       if (i == T) return now;
       if (now < EPS) return 0.0;
       double w = 0.0;
       for (int k = c[i]; k != -1 && w < now; k = next[k]){
           int j = g[k];
           double rst = min(flow[k], now - w), ret = 0.0;
           if (rst > EPS && d[j] == d[i] + 1)
              if ((ret = dfs(j, rst)) > EPS){
                 flow[k] -= ret;
                 flow[k ^ 1] += ret;
                 w += ret;
              }
       }
       if (w < EPS) d[i] = -1;
       return w;
}

double gh(double l){
       S = n + m + 1;
       T = S + 1;
       double ans = (double)m;
       nm = 0;
       memset(c, -1, sizeof c);
       for (int i = 1; i <= m; ++i) add(S, ge(i), 1);
       for (int i = 1; i <= m; ++i) add(ge(i), gv(x[i]), SUP), add(ge(i), gv(y[i]), SUP);
       for (int i = 1; i <= n; ++i) add(gv(i), T, l);
       while (bfs()){
             while (1){
                   double ret = dfs(S, SUP);
                   if (ret > EPS) ans -= ret; else break;
             }
       }
       return ans;
}

void dfs1(int i){
	vd[i] = 1;
	for (int k = c[i]; k != -1; k = next[k]){
		int j = g[k];
		if (vd[j] == 0 && flow[k] > EPS) dfs1(j);
	}
}

void dfs2(int i){
	vd[i] = -1;
	for (int k = c[i]; k != -1; k = next[k]){
		int j = g[k];
		if (vd[j] == 0 && flow[k] > EPS) dfs2(j);
	}
}

void   getans(double l){
       S = n + m + 1;
       T = S + 1;
       double ans = (double)m;
       nm = 0;
       ansn = 0;
       memset(ans_list, 0, sizeof ans_list);
       memset(vd, 0, sizeof vd);
       memset(c, -1, sizeof c);
       for (int i = 1; i <= m; ++i) add(S, ge(i), 1);
       for (int i = 1; i <= m; ++i) add(ge(i), gv(x[i]), SUP), add(ge(i), gv(y[i]), SUP);
       for (int i = 1; i <= n; ++i) add(gv(i), T, l);
       while (bfs()){
             while (1){
                   double ret = dfs(S, SUP);
                   if (ret > EPS) ans -= ret; else break;
             }
       }
       dfs1(S);
       dfs2(T);
       for (int i = 1; i <= n; ++i) if (vd[gv(i)] * vd[T] == -1) ans_list[++ansn] = i;       
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d", &x[i], &y[i]);
    double l = 1.0 / n, r = m / 1.0 + EPS;
    double rt = 1.0 / ((double)n * n);
    //printf("%.5f\n", gh(2.0));
    while (l + rt / 100.0 < r){
          double mid = (l + r) / 2;
          //printf("%.9f %.9f %.9f %.9f %.9f\n", l, r, mid, gh(mid), -EPS);
          if (gh(mid) > EPS) l = mid; else r = mid;
    }
    if (r > EPS){
       getans(l);
       printf("%d\n", ansn);
       for (int i = 1; i <= ansn; ++i) printf("%d\n", ans_list[i]);
    }
    else printf("1\n1\n");
}

        
