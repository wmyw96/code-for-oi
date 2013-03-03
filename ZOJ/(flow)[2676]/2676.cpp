#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 501, MAX_M = 5001;
double SUP = 1000000000.0, EPS = 1e-9;
int g[MAX_M], next[MAX_M];
int c[MAX_N], d[MAX_N], Q[MAX_M], nm;
double flow[MAX_M];
int n, m, S, T;
int x[MAX_M], y[MAX_M], w[MAX_M];
int ans_list[MAX_M], ansn, vd[MAX_N];

void addedge(int x, int y, double w){
	g[nm] = y;
	next[nm] = c[x];
	c[x] = nm;
	flow[nm] = w;
	nm++;
}

void add(int x, int y, double w){
	addedge(x, y, w);
	addedge(y, x, w);
}

int bfs(){
	memset(d, -1, sizeof d);
	d[S] = 1;
	Q[1] = S;
	for (int l = 1, r = 1; l <= r; ++l){
		int i = Q[l];
		for (int k = c[i]; k != -1; k = next[k]){
			int j = g[k];
			if (flow[k] > EPS && d[j] == -1)
				d[j] = d[i] + 1, Q[++r] = j; 
		}
	}
	return d[T] != -1;
}

double dfs(int i, double now){
	if (i == T) return now;
	if (now < EPS) return now;
	double w = 0.0;
	for (int k = c[i]; k != -1 && w + EPS < now; k = next[k]){
		int j = g[k];
		double rst = min(now - w, flow[k]), ret = 0.0;
		if (d[j] == d[i] + 1)
			if (rst > EPS && (ret = dfs(j, rst)) > 0){
				flow[k] -= ret;
				flow[k ^ 1] += ret;
				w += ret;
			}
	}
	if (w < EPS) d[i] = -1;
	return w;
}

double gh(double l){
	memset(c, -1, sizeof c);
	nm = 0;
	
	double ans = 0.0;
	for (int i = 1; i <= m; ++i){
		double wt = w[i] - l;
		if (wt > EPS) add(x[i], y[i], wt);
		else ans += wt;
	}
	S = 1; T = n;
	while (bfs()){
		while (1){
			double ret = dfs(S, SUP);
			if (ret > EPS) ans += ret; else break; 
		}
	}
	return ans;
}

void dfs1(int i){
	vd[i] = 1;
	for (int k = c[i]; k != -1; k = next[k]){
		int j = g[k];
		if (vd[j] == 0 && flow[k] > EPS) dfs1(j);
	}
}

void dfs2(int i){
	vd[i] = -1;
	for (int k = c[i]; k != -1; k = next[k]){
		int j = g[k];
		if (vd[j] == 0 && flow[k] > EPS) dfs2(j);
	}
}

int cmp(int x, int y){
	return x < y;
}

void getans(double l){
	memset(c, -1, sizeof c);
	memset(vd, 0, sizeof vd);
	nm = 0;
	ansn = 0;
	memset(ans_list, 0, sizeof ans_list);
	
	double ans = 0.0;
	for (int i = 1; i <= m; ++i){
		double wt = w[i] - l;
		if (wt > EPS) add(x[i], y[i], wt);
		else ans += wt, ans_list[++ansn] = i;
	}
	S = 1; T = n;
	while (bfs()){
		while (1){
			double ret = dfs(S, SUP);
			if (ret > EPS) ans += ret; else break; 
		}
	}
	memset(vd, 0, sizeof vd);
	dfs1(S);
	dfs2(T);
	for (int i = 1; i <= m; ++i){
		if (w[i] - l > EPS && vd[x[i]] * vd[y[i]] == -1) ans_list[++ansn] = i;
 	}
 	sort(ans_list + 1, ans_list + 1 + ansn, cmp);
}

int main(){
	int T_T = 0;
	while (scanf("%d%d", &n, &m) != EOF){
		if (T_T == 0) T_T = 1; else printf("\n");
		for (int i = 1; i <= m; ++i) scanf("%d%d%d", &x[i], &y[i], &w[i]);
		double l = 0.0, r = 10000000.0 + EPS;
		while (l + EPS < r){
			double mid = (l + r) / 2.0;
			double ch = gh(mid);
			if (fabs(ch) < EPS) break;
			if (ch > EPS) l = mid; else r = mid;
		}
		getans(l);
		printf("%d\n", ansn);
		for (int i = 1; i < ansn; ++i) printf("%d ", ans_list[i]);
		if (ansn) printf("%d\n", ans_list[ansn]);
	}
}

