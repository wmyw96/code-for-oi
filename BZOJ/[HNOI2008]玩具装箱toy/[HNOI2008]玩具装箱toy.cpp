#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef long long LL;
struct que{
       int s, t, i;
};
const int MAX_N = 1000001;
que q[MAX_N];
LL f[MAX_N], s[MAX_N];
int a[MAX_N], g[MAX_N];
int n, L;

LL  sqr(LL x){
    return x * x;
}

LL  calc(int j, int i){
    return f[j] + sqr(L - ((i - j - 1) + s[i] - s[j]));
}

int main(){
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]), s[i] = s[i - 1] + a[i];
    
    int l = 1, r = 0;
    q[r = 1].s = 1;
    q[1].t = n;
    q[1].i = 0;
    for (int i = 1; i <= n; ++i){
        f[i] = calc(q[l].i, i);
        g[i] = q[l].i;
        q[l].s++;
        if (q[l].s > q[l].t) ++l;
        while (l <= r && calc(q[r].i, q[r].s) > calc(i, q[r].s)){
              q[r].s = q[r].t = q[r].i = 0;
              r--;
        }
        int ll = (l <= r) ? (q[r].t + 1) : (i + 1);
        if (l <= r && calc(q[r].i, q[r].s) <= calc(i, q[r].s) && calc(q[r].i, q[r].t) > calc(i, q[r].t)){
           int f = q[r].s, t = q[r].t;
           while (f + 1 < t){
                 int mid = (f + t) / 2;
                 if (calc(q[r].i, mid) <= calc(i, mid)) f = mid; else t = mid;
           }
           q[r].t = f;
           ll = t;
        }
        if (ll <= n){
           q[++r].s = ll;
           q[r].t = n;
           q[r].i = i;
        }
    }
    cout<<f[n]<<endl;
}
