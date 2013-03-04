#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;

const double EPS = 1e-9;
const int MAX_N = 2001, MAX_M = 20001;
int g[MAX_M], next[MAX_M], c[MAX_N], ew[MAX_M], nm;
double d[MAX_N];
int Q[MAX_M * 100], cnt[MAX_N], vd[MAX_N], p[MAX_N];
int n, m;

void addedge(int x, int y, int w){
	g[nm] = y;
	next[nm] = c[x];
	c[x] = nm;
	ew[nm] = w;
	nm++;
}

int ck(double la){
	memset(cnt, 0, sizeof cnt);
	int r = 0;
	for (int i = 1; i <= n; ++i){
		d[i] = 0.0;
		Q[++r] = i;
		vd[i] = 1;
		cnt[i] = 1;
	}
	for (int l = 1; l <= r; ++l){
		int i = Q[l];
		vd[i] = 0;
		for (int k = c[i]; k != -1; k = next[k]){
			int j = g[k];
			if (d[j] > d[i] - p[j] + ew[k] * la){
				d[j] = d[i] - p[j] + ew[k] * la;
				if (!vd[j]){
					vd[j] = 1;
					Q[++r] = j;
					cnt[j]++;
					if (cnt[j] > n) return 1;
				}
			}
		}
	}
	return 0;
}

int main(){
	scanf("%d%d", &n, &m);
	double l, r;
	l = r = 0.0;
	memset(c, -1, sizeof c);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &p[i]), r = max(r, (double)p[i]);
	for (int i = 1; i <= m; ++i){
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		addedge(x, y, w);
	}
	while (l + EPS < r){
		double mid = (l + r) / 2;
		if (ck(mid)) l = mid; else r = mid;
	}
	printf("%.2f\n", l);
} 

