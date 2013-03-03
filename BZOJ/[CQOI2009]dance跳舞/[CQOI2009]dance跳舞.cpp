#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 100001, MAX_M = 100001, SUP = 10000000, MAX_L = 101;
int g[MAX_M], next[MAX_M], c[MAX_N], flow[MAX_M], nm, d[MAX_N], Q[MAX_M];
int n, S, T, Ti;
int a[MAX_L][MAX_L];
char st[MAX_L];
int ans;

void addedge(int x, int y, int w){
	g[nm] = y;
	next[nm] = c[x];
	c[x] = nm;
	flow[nm] = w;
	nm++;
}

void add(int x, int y, int w){
	//printf("%d %d %d\n", x, y, w);
	addedge(x, y, w);
	addedge(y, x, 0);
}

int m(int i, int j){
	return (i - 1) * n + j;
}

int bfs(){
	int l, r;
	memset(d, -1, sizeof d);
	d[S] = 0;
	Q[l = r = 1] = S;
	for (; l <= r; ++l){
		int i = Q[l];
		for (int k = c[i]; k != -1; k = next[k]){
			int j = g[k];
			if (d[j] == -1 && flow[k])
				d[j] = d[i] + 1, Q[++r] = j;
		}
	}
	return d[T] != -1;
}

int dfs(int i, int now){
	if (!now) return 0;
	if (i == T) return now;
	int w = 0;
	for (int k = c[i]; k != -1 && w < now; k = next[k]){
		int j = g[k];
		int rst = min(flow[k], now - w), ret = 0;
		if (d[j] == d[i] + 1)
			if (rst && ((ret = dfs(j, rst)) > 0)){
				flow[k] -= ret;
				flow[k ^ 1] += ret;
				w += ret;
			}
	}
	if (!w) d[i] = -1;
	return w;
}

int bm(int i){
	return i;
}
int b_like(int i){
	return i + n;
}
int b_ulike(int i){
	return i + n * 2;
}
int g_like(int i){
	return i + n * 3;
}
int g_ulike(int i){
	return i + n * 4;
}
int gm(int i){
	return i + n * 5;
}

int dinic(){
	while (bfs()){
		while (1){
			int ret = dfs(S, SUP);
			if (!ret) break; else ans += ret;
		}
	}
	//printf("%d\n", ans);
	return ans;
}

int main(){
	int k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i){
		scanf("%s", &st);
		for (int j = 1; j <= n; ++j)
			a[i][j] = (st[j - 1] == 'Y') ? (0) : (1);
	}
	
	S = n * 6 + 1;
	T = S + 1;
	Ti = ans = 0;
	memset(c, -1, sizeof c);
	
	for (int i = 1; i <= n; ++i){
		add(S, bm(i), 1);
		add(bm(i), b_like(i), SUP);
		add(bm(i), b_ulike(i), k);
		for (int j = 1; j <= n; ++j)
			if (a[i][j]) add(b_ulike(i), g_ulike(j), 1);
					else add(b_like(i), g_like(j), 1);
	}
	
	for (int i = 1; i <= n; ++i){
		add(g_like(i), gm(i), SUP);
		add(g_ulike(i), gm(i), k);
		add(gm(i), T, 1);
	}
	
	while (dinic() == (++Ti) * n){
		for (int k = c[S]; k != -1; k = next[k]) flow[k] ++;
		for (int i = 1; i <= n; ++i) flow[c[gm(i)]]++;
	}
	
	printf("%d\n", Ti - 1);
} 

/*
3 0
YYY
YYY
YYY

*/
