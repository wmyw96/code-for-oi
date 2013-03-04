#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 2001, MAX_M = 1000001;
const double EPS = 1e-5, SUP = 1e9;
struct gph{
       int x, y;
       double w;
       void mp(int a, int b, double c){
            x = a, y = b, w = c;
       }
};
gph E[MAX_M];
int x[MAX_M], y[MAX_M], fa[MAX_N];
double w1[MAX_M], w2[MAX_M];
int u[MAX_N], v[MAX_N], d[MAX_N], vd[MAX_N];
double g[MAX_N][MAX_N], dt[MAX_N];
int n, m;

double ck(double l){
       for (int i = 1; i <= m; ++i)
           g[x[i]][y[i]] = g[y[i]][x[i]] = w1[i] - l * w2[i];
       for (int i = 1; i <= n; ++i) dt[i] = SUP;
       memset(vd, 0, sizeof vd);
       for (int i = 1; i <= n; ++i) dt[i] = min(dt[i], g[i][1]);
       vd[1] = 1;
       double ans = 0.0;
       for (int i = 2; i <= n; ++i){
           double mn = SUP;
           int mnr = 0;
           for (int j = 1; j <= n; ++j)
               if (dt[j] < mn && !vd[j]) mn = dt[j], mnr = j;
           ans += mn;
           vd[mnr] = 1;
           for (int j = 1; j <= n; ++j)
                if (!vd[j] && dt[j] > g[mnr][j]) dt[j] = g[mnr][j];
       }
       return ans;
}

double sqr(int x){
       return x * x;
}

int main(){
    while (scanf("%d", &n) != EOF){
    if (n == 0) return 0;
    m = 0;
    for (int i = 1; i <= n; ++i)
        scanf("%d%d%d", &u[i], &v[i], &d[i]);
    double l, r;
    l = r = 0.0;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j){
            x[++m] = i;
            y[m] = j;
            w1[m] = abs(d[i] - d[j]);
            w2[m] = sqrt(sqr(u[i] - u[j]) + sqr(v[i] - v[j]));
            r = max(r, (double)w1[m] / w2[m]);
        }
    r += EPS;
    while (l + EPS < r){
          double mid = (l + r) / 2;
          if (ck(mid) > EPS) l = mid; else r = mid;
    }
    printf("%.3f\n", l);
    }
    //system("pause");
}
