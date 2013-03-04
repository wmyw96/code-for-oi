#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAX_N = 2001;
const double SUP = 1000000000.0, EPS = 1e-9;
int a[MAX_N], b[MAX_N];
double c[MAX_N];
int n, m;

int cmp(double x, double y){
    return x > y;
}

double ck(double l){
     for (int i = 1; i <= n; ++i)
         c[i] = a[i] - b[i] * l;
     sort(c + 1, c + 1 + n, cmp);
     double ans = 0.0;
     for (int i = 1; i <= m; ++i) ans += c[i];
     return ans;
}
 
int main(){
    while (scanf("%d%d", &n ,&m) != EOF){
          if (n == 0 && m == 0) break;
          m = n - m;
          for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
          for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
          double l = 0.0, r = SUP + EPS;
          while (l + EPS < r){
                double mid = (l + r) / 2;
                if (ck(mid) > -EPS) l = mid; else r = mid;
          }
          int ans = (l + 0.005) * 100;
          printf("%d\n", ans);
    }
}
