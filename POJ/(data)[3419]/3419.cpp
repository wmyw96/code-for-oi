#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std;

map<int, int> lst;
const int MAX_N = 1000001;
int mx[MAX_N << 2];
int a[MAX_N], f[MAX_N];
int n, m;

void build(int x, int l, int r){
     if (l == r) {mx[x] = f[l];return;}
     int mid = (l + r) / 2;
     build(x * 2, l, mid);
     build(x * 2 + 1, mid + 1, r);
     mx[x] = max(mx[x * 2], mx[x * 2 + 1]);
}

int query(int x, int l, int r, int f, int t){
    if (f > t) return 0;
    if (f <= l && r <= t) return mx[x];
    int mid = (l + r) / 2;
    int ret = 0;
    if (f <= mid) ret = max(ret, query(x * 2, l, mid, f, t));
    if (t > mid) ret = max(ret, query(x * 2 + 1, mid + 1, r, f, t));
    return ret;
}
 
int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = n; i >= 1; --i){
        int ret = lst[a[i]];
        if (ret != 0) f[i] = min(ret - i, f[i + 1] + 1); 
                 else f[i] = min(n - i + 1, f[i + 1] + 1);
        lst[a[i]] = i;
    }
    build(1, 1, n);
    while (m--){
          int l, r, x, y;
          scanf("%d%d", &x, &y);
          x++, y++;
          int ed = f[y];
          l = x - 1, r = y;
          while (l + 1 < r){
                int mid = (l + r) / 2;
                if (f[mid] + mid - 1 > y) r = mid; else l = mid;
          }
          int ans = max(query(1, 1, n, x, l), y - r + 1);
          printf("%d\n", ans);
    }
}
