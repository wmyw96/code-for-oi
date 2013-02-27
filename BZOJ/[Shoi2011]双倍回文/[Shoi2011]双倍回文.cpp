#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<set>
using namespace std;

const int MAX_N = 1000011;
struct ls{
       int a, b, c;
       void mp(int x, int y, int z){
            a = x, b = y, c = z;
       }
}s1[MAX_N], s2[MAX_N];
int rk[MAX_N], H[28], sa[MAX_N];
char a[MAX_N];
int h[MAX_N], d[MAX_N];
int f[MAX_N][20];
int n, N;
set<int> S;
set<int>::iterator tmp, tmp2;

int build(int w){
    for (int i = 1; i <= n; ++i)
        s1[i].mp(rk[i], rk[i + w], i);
    memset(d, 0, sizeof d);
    for (int i = 1; i <= n; ++i) d[s1[i].b]++;
    for (int i = 1; i <= n; ++i) d[i] += d[i - 1];
    for (int i = n; i >= 1; --i) s2[d[s1[i].b]--] = s1[i];
    memset(d, 0, sizeof d);
    for (int i = 1; i <= n; ++i) d[s2[i].a]++;
    for (int i = 1; i <= n; ++i) d[i] += d[i - 1];
    for (int i = n; i >= 1; --i) s1[d[s2[i].a]--] = s2[i];
    for (int i = 1; i <= n; ++i)
        rk[s1[i].c] = rk[s1[i - 1].c] + (s1[i].a != s1[i - 1].a || s1[i].b != s1[i - 1].b);
    return rk[s1[n].c];
}

int lcp(int x, int y){
    if (y < x) return lcp(y, x);
    ++x;
    int k = (int)(log(y - x + 1) / log(2));
    return min(f[x][k], f[y - (1<<k) + 1][k]);
}

int main(){
    scanf("%d", &n);
    scanf("%s", &a[1]);
    for (int i = 0; i < n; ++i){
        a[i + 1] = a[i + 1] - 'a' + 1;
        H[a[i + 1]] = 1;
    }
    memset(d, 0, sizeof d);
    a[n + 1] = 27; H[27] = 1;
    for (int i = 1; i <= n; ++i)
        a[n + i + 1] = a[n - i + 1];
    n = n * 2 + 1;
    
    for (int i = 1; i <= 27; ++i) H[i] += H[i - 1];
    for (int i = 1; i <= n; ++i) rk[i] = H[a[i]];
    for (int i = 1; i < n && build(i) < n; i <<= 1);
    
    for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
    for (int i = 1, j = 0; i <= n; ++i){
        if (rk[i] == 0) continue;
        for (j = max(0, j - 1); j <= n && a[i + j] == a[sa[rk[i] - 1] + j]; ++j);
        h[rk[i]] = j;
    }
    
    for (int i = n; i >= 1; --i){
        f[i][0] = h[i];
        for (int k = 1; i + (1<<k) - 1 <= n; ++k)
            f[i][k] = min(f[i][k - 1], f[i + (1 << k-1)][k - 1]);
    }
    N = (n - 1) / 2;
    for (int i = 1; i < N; ++i)
        d[i] = lcp(rk[n - i + 1], rk[i + 1]);
        
    S.insert(1);
    int ans = 0, l, r;
    
    for (int i = 2; i < N; ++i){
        l = i - (d[i]) / 2;
        if (l <= i - 1){
           tmp = S.lower_bound(l);
           if (tmp != S.end()){
           
              while (*tmp + d[*tmp] < i){
                    tmp2 = tmp;
                    tmp++;
                    S.erase(tmp2);
                    if (tmp == S.end()) break;
              }
              if (tmp != S.end())
                 ans = max(ans, 4 * (i - *tmp));
           }
        }
        if (d[i]) S.insert(i);
    }
    printf("%d\n", ans);
}

/*
16
ggabaabaabaaball
*/
