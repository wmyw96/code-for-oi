#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAX_N = 300001;
int n;
LL s[MAX_N], e[MAX_N], d[MAX_N];

LL calc(LL l, LL r){
    LL ret = 0;
    for (int i = 1; i <= n; ++i){
        LL ll = (s[i] >= l) ? (s[i]) : (((l - s[i]) / d[i] + ((l - s[i]) % d[i] != 0)) * d[i] + s[i]);
        LL rr = (e[i] <= r) ? (e[i]) : (e[i] - ((e[i] - r) / d[i] + ((e[i] - r) % d[i] != 0)) * d[i]);
        if (ll <= rr) ret += ((rr - ll) / d[i]) + 1;
    }
    return ret;
}

int dfs(LL l, LL r){
    int ans = 0;
    if (calc(l, r) % 2 == 0) ans = -1;
    for (; l != r && ans != -1;){    
        LL mid = (LL)(l + r) / 2;
        LL lc = calc(l, mid);
        if (lc & 1) r = mid; else l = mid + 1;
    }
    if (ans != -1) ans = l;
    if (ans != -1) printf("%d %d\n", ans, calc(l, r));
    else printf("Poor QIN Teng:(\n");
}
         
int main(){
    int Ti;
    scanf("%d", &Ti);
    while (Ti--){
          scanf("%d", &n);
          LL r = 0, l = 2147483647;
          for (int i = 1; i <= n; ++i){
              scanf("%d%d%d", &s[i], &e[i], &d[i]);
              e[i] = ((e[i] - s[i]) / d[i]) * d[i] + s[i];
              l = min(l, s[i]);
              r = max(r, e[i]);
          }
          dfs(l, r);
    }
    //system("pause");
}
