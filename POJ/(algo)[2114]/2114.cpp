#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 10001, MAX_M = 20001, MAX_Q = 2001;
int g[MAX_M], next[MAX_M], c[MAX_N], cost[MAX_M], nm, ok[MAX_M];
int s[MAX_N], pr[MAX_N], prmn, ctr, nowsize, n, m, d[MAX_N], lt, a[MAX_M], b[MAX_M];
int ans[MAX_Q], qy[MAX_Q], p[MAX_M];
int pp, ltt;

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
     if (pr[i] < prmn){
        prmn = pr[i];
        ctr = i;
     }
}

void dfs(int i, int pre){
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (j != pre && ok[k]){
            d[j] = d[i] + cost[k];
            p[++ltt] = d[j];
            dfs(j, i);
         } 
     }
}

int cmp(int x, int y){
    return x < y;
}

void solve(int i, int pre, int ct, int fh){
     d[i] = ct;
     p[ltt = 1] = ct;
     dfs(i, pre);
     sort(p + 1, p + 1 + ltt, cmp);
     lt = 0;
     for (int i = 1; i <= ltt; ++i){
         a[++lt] = p[i]; b[lt] = 1;
         while (p[i + 1] == p[i] && i < ltt) ++i, b[lt]++;
     }
     for (int i = 1; i <= m; ++i){
         int k = qy[i];
         int l = 1, r = lt;
         while (l < r){
               if (a[l] + a[r] > k) r--;
               else if (a[l] + a[r] < k) l++;
               else if (a[l] + a[r] == k){
                       ans[i] += fh * b[l] * b[r];
                       ++l;
                       }
               if (l == r){
                  if (a[l] + a[r] == k)
                     ans[i] += fh * b[l] * b[r];
                  break;
               }
         }
     }
}

void calc(int i, int dep){
     solve(i, -1, 0, 1);
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (ok[k]){
            solve(j, i, cost[k], -1);
         }
     }
     findroot(i, -1);
     pp += s[i] * (int)(log(s[i]) / log(2));
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (ok[k]){
            ok[k ^ 1] = 0;
            nowsize = prmn = s[j];
            findroot(j, -1);
            calc(ctr, dep + 1);
         }
     }
}
         
int main(){
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    while (scanf("%d", &n) != EOF){
          if (n == 0) break;
          memset(c, -1, sizeof c);
          memset(ok, 0, sizeof ok);
          nm = 0;
          for (int i = 1; i <= n; ++i){
              int x, y;
              scanf("%d", &x);
              while (x != 0){
                    scanf("%d", &y);
                    addedge(i, x, y);
                    addedge(x, i, y);
                    scanf("%d", &x);
              }
          }
          int x;
          m = 0;
          pp = 0;
          scanf("%d", &x);
          while (x != 0){
                qy[++m] = x;
                ans[m] = 0;
                scanf("%d", &x);
          }
          nowsize = prmn = n;
          findroot(1, -1);
          calc(ctr, 0);
          for (int i = 1; i <= m; ++i)
              if (ans[i] > 0) printf("AYE\n"); else printf("NAY\n"); 
          printf(".\n");
          printf("%d\n", pp);
    }
}
