#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 200001, MAX_M = 500001;
int next[MAX_M], g[MAX_M], c[MAX_N], nm, cost[MAX_M], mk[MAX_N];
int lt, s[MAX_N], pr[MAX_N], d[MAX_N], a[MAX_N], nowsize;
int n, k, ans;
int prmn, ctr;

void addedge(int x, int y, int w){
     g[nm] = y;
     next[nm] = c[x];
     c[x] = nm;
     cost[nm] = w;
     mk[nm] = 1;
     nm++;
}

void findroot(int i, int pre){
     s[i] = 1, pr[i] = 0;
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (j != pre && mk[k]){
            findroot(j, i);
            pr[i] = max(pr[i], s[j]);
            s[i] += s[j];
         }
     }
     pr[i] = max(pr[i], nowsize - s[i]);
     if (pr[i] < prmn) prmn = pr[i], ctr = i;
}

void dfs(int i, int pre){
     for (int k = c[i]; k != -1; k = next[k]){
         int j = g[k];
         if (pre != j && mk[k]){
            d[j] = d[i] + cost[k];
            a[++lt] = d[j];
            dfs(j, i);
         }
     }
}

int cmp(int x, int y){
    return x < y;
}

int getlist(int i, int ret, int fa){
    a[lt = 1] = ret;
    d[i] = ret;
    dfs(i, fa);
    sort(a + 1, a + lt + 1, cmp);
    int l = 1, r = lt, cnt = 0;
    while (l < r){
          if (a[l] + a[r] <= k){
             cnt += r - l;
             l++;
          }
          else r--;
    }
    return cnt;
}


void calc(int i){
     ans += getlist(i, 0, -1);
     for (int k = c[i]; k != -1; k = next[k])
         if (mk[k]){
            int j = g[k];
            ans -= getlist(j, cost[k], i);
         }
     findroot(i, -1);
     for (int k = c[i]; k != -1; k = next[k])
         if (mk[k]){
            int j = g[k];
            mk[k ^ 1] = 0;
            prmn = nowsize = s[i];
            findroot(j, -1);
            calc(ctr);
         }
}

int main(){
    while (scanf("%d", &n) !=EOF){
          if (n == 0) return 0;
          scanf("%d", &k);
          memset(c, -1, sizeof c);
          for (int i = 1; i < n; ++i){
              int x, y, w;
              scanf("%d%d%d", &x, &y, &w);
              addedge(x, y, w);
              addedge(y, x, w);
          }
          ans = 0;
          prmn = nowsize = n;
          findroot(1, -1);
          calc(ctr);
          printf("%d\n", ans);
    }
}
