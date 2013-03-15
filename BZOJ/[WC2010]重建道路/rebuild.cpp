#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
 
const int MAX_N = 200001, MAX_M = 400001;
const double INF = 1000000000;
int g[MAX_M], c[MAX_N], next[MAX_M], ok[MAX_M], nm;
double cost[MAX_M], a[MAX_N], nd[MAX_N];
int pr[MAX_N], s[MAX_N], Q[MAX_N], pre[MAX_N], dep[MAX_N];
int n, m, L, R, nowsize, ctr, prmn, dnow;
double ans, ansn;
int x[MAX_N], y[MAX_N], w[MAX_N], ww[MAX_N], d[MAX_N];
int mm[MAX_M];
int lt; 
int pp;
double dat; 

struct TTT{
       int l, r, t[300001];
       double Q[300001];
       void clear(int n){
            l = 1, r = 0;
       }
       void upd(int tt){
            while (l <= r && t[l] > tt) l++;
       }
       void push(double ret, int time){
            while (l <= r && Q[r] <= ret) r--;
            Q[++r] = ret;
            t[r] = time;
       }
       double get(){
              if (l <= r) return Q[l];
       }
}T;
 
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
     if (pr[i] < prmn){
        prmn = pr[i];
        ctr = i;
     }
}

void dfs_upd(int i, int pre, int dd, double now){
     if (dd > R) return;
     a[dd] = max(a[dd], now);
     if (dd <= R && dd >= L && a[dd] > 0){ans = 1; return;}
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (j != pre && ok[k]) dfs_upd(j, i, dd + 1, now + cost[k] - dat);
         if (ans > 0) return;
     }
}
 
void getans(int ii, int jj, int dd, double now){
     //若当前计算到的dep为k,在[max(L - k, 0), R - k]中找到最大值.
     Q[1] = ii;
     dep[0] = dd - 1;
     pre[1] = jj;
     dep[1] = dd;
     nd[1] = now;
     dnow = d[ii];
     T.clear(dnow);
      
     if (R - dnow > L) for (int i = R; i >= R - dnow; --i) T.push(a[i], i);
                  else for (int i = R; i >= L; --i) T.push(a[i], i);
     
     for (int l = 1, r = 1; l <= r; ++l){
         if (dep[l] > R) return;
         int i = Q[l];
         if (dep[l] != dep[l - 1]){
            T.upd(R - dep[l]);
            if (L - dep[l] >= 0)
               T.push(a[L - dep[l]], L - dep[l]);
            if (ans > 0) return;
         }
         
         ans = max(ans, T.get()+ nd[l]);
         for (int k = c[i]; k != -1; k = next[k]){
             int j = g[k];
             if (j != pre[l] && ok[k]){
                Q[++r] = j;
                pre[r] = i;
                dep[r] = dep[l] + 1;
                nd[r] = nd[l] + cost[k] - dat;
             }
         }
     }
}
 

double ck(int i){
     dnow = d[i];
     ans = -INF;
     pp++;
     if (dnow < L / 2) return -10;
     a[0] = 0;
     for (int j = 1; j <= dnow; ++j) a[j] = -INF;
     for (int j = max(0, R - dnow); j <= R; ++j) a[j] = -INF;
     for (int j = max(0, L - dnow); j <= min(L, R - dnow); ++j) a[j] = -INF;
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (ok[k]){
            getans(j, i, 1, cost[k] - dat);
            if (ans > 0) return ans;
            dfs_upd(j, i, 1, cost[k] - dat);
         }
     }
     return ans;
}

void dfs(int i, int pre, int dd){
     d[i] = dd;
     if (dd > R) return;
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (j != pre && ok[k]){
            d[j] = d[i] + 1;
            dfs(j, i, dd + 1);
            d[i] = max(d[i], d[j]);
         }
     }
}

void dfs(int i, int pre){
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (pre != j && ok[k]){
            ww[++lt] = w[mm[k]];
            dfs(j, i);
         }
     }
}

void calc(int i){
     //即可计算出要更新[0, dnow]，计算[L - dnow, R]
     //同时, 若当前计算到的dep为k,在[max(L - k, 0), R - k]中更新 
     lt = 0;
     dfs(i, -1, 0);
     dfs(i, -1);
     sort(ww + 1, ww + 1 + lt);
     double l = 0, r = 0;
     for (int j = lt; j >= lt - L + 1; --j) r += ww[j];
     r /= L;
     while (l + 1e-4 < r){
           double mid = (l + r) / 2;
           dat = mid;
           if (ck(i) > 0) l = mid; else r = mid;
     }
     ansn = max(ansn, l);
      
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
 
void addedge(int x, int y, double w, int mmm){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     cost[nm] = w;
     ok[nm] = 1;
     mm[nm] = mmm;
     nm++;
}
 
int main(){
    scanf("%d", &n);
    scanf("%d%d", &L, &R);
    for (int i = 1; i < n; ++i){
        scanf("%d%d%d", &x[i], &y[i], &w[i]);
    }
    memset(c, -1, sizeof c);
    for (int i = 1; i < n; ++i){
        addedge(x[i], y[i], w[i], i);
        addedge(y[i], x[i], w[i], i);
    }
    nowsize = prmn = n;
    findroot(1, -1);
    calc(ctr);
    printf("%.3f\n", ansn);
}

