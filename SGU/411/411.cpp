#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
  
const int MAX_N = 12001;
struct se{
       int a, b, c;
       void mp(int x, int y, int z){
            a = x, b = y, c = z;
       }
}s1[MAX_N], s2[MAX_N];
char st[MAX_N];
int a[MAX_N], Na, Nb, N, n, sa[MAX_N], rk[MAX_N], h[MAX_N], cnt[MAX_N], H[31], mk[MAX_N];
int f[MAX_N][20], maxn[MAX_N], mx[3];
  
int build(int w){
    if (w > n) return n + 1;
    for (int i = 1; i <= n; ++i)
        s1[i].mp(rk[i], rk[i + w], i);
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; ++i) cnt[s1[i].b]++;
    for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; --i) s2[cnt[s1[i].b]--] = s1[i];
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; ++i) cnt[s2[i].a]++;
    for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; --i) s1[cnt[s2[i].a]--] = s2[i];
    for (int i = 1; i <= n; ++i)
        rk[s1[i].c] = rk[s1[i - 1].c] + (s1[i - 1].a != s1[i].a || s1[i - 1].b != s1[i].b);
    return rk[s1[n].c];
}
  
int lcp(int l, int r){
    if (l > r) return lcp(r, l);
    l++;
    if (r == l) return h[l];
    int k = (int)(log(r - l + 1) / log(2));
    return min(f[l][k], f[r - (1<<k) + 1][k]);
}
  
void init(){    
     scanf("%s", &st);
     int l = strlen(st);
     for (int i = 1; i <= l; ++i)
         a[i] = st[i - 1] - 'a' + 1, H[a[n + i]] = 1, mk[i] = 0;
     n = l + 1;
     Na = n - 1;
     a[n] = 27;
     mk[n] = -1;
     scanf("%s", &st);
     l = strlen(st);
     Nb = l;
     for (int i = 1; i <= l; ++i)
         a[n + i] = st[i - 1] - 'a' + 1, H[a[n + i]] = 1, mk[i + n] = 1;
     n += l + 1;
     a[n] = 28;
     mk[n] = -1;
     H[27] = H[28] = 1;
     for (int i = n + 1; i <= n + Na; ++i)
         a[i] = a[Na - (i - n) + 1], mk[i] = -1;
     for (int i = 1; i <= 28; ++i) H[i] += H[i - 1];
     n += Na;
       
     for (int i = 1; i <= n; ++i)
         rk[i] = H[a[i]];
       
     for (int i = 1; i < n && build(i) < n; i <<= 1);
     for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
       
     for (int i = 1, j = 0; i <= n; ++i){
         if (rk[i] == 1) continue;
         for (j = max(j - 1, 0); j <= n && a[i + j] == a[sa[rk[i] - 1] + j]; ++j);
         h[rk[i]] = j;
     }
       
     for (int i = n; i >= 1; --i){
         f[i][0] = h[i];
         for (int k = 1; i + (1<<k) - 1 <= n; ++k)
             f[i][k] = min(f[i][k - 1], f[i + (1<<k-1)][k - 1]);
     }
}
  
int main(){
    init();
    mx[1] = (mk[sa[1]] == 1) ? (sa[1] - Na - 1) : (0);
    for (int i = 2; i <= n; ++i){
        mx[1] = min(mx[1], h[i]);
        if (mk[sa[i]] == 0) maxn[sa[i]] = max(maxn[sa[i]], mx[1]);
        if (mk[sa[i]] == 1) mx[1] = h[i + 1];
    }
    mx[1] = 0;
    for (int i = n - 1; i >= 1; --i){
        mx[1] = min(mx[1], h[i + 1]);
        if (mk[sa[i]] == 0) maxn[sa[i]] = max(maxn[sa[i]], mx[1]);
        if (mk[sa[i]] != -1) mx[mk[sa[i]]] = h[i];
    }
      
    int ans = 0, lt = 0;
      
    for (int i = 1; i <= Na; ++i){
        int w = lcp(rk[i], rk[n - i + 1]);
        int l = 0, r = w + 1;
        while (l + 1 < r){
              int mid = (l + r) / 2;
              if (maxn[i - mid + 1] >= mid * 2 - 1) l = mid; else r = mid;
        }
        if (l * 2 - 1 > ans){
           ans = l * 2 - 1;
           lt = i - l + 1;
        }
    }
      
    for (int i = 1; i < Na; ++i){
        int w = lcp(rk[i + 1], rk[n - i + 1]);
        int l = 0, r = w + 1;
        while (l + 1 < r){
              int mid = (l + r) / 2;
              if (maxn[i - mid + 1] >= mid * 2) l = mid; else r = mid;
        }
        if (l * 2 > ans){
           ans = l * 2;
           lt = i - l + 1;
        }
    }
      
    for (int i = lt; i <= lt + ans - 1; ++i) printf("%c", a[i] + 'a' - 1);
    printf("\n");
}
