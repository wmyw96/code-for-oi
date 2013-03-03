#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 100001, MAX_M = 1000001, SUP = 100000000;
int g[MAX_M], next[MAX_M], c[MAX_N], flow[MAX_M], nm, d[MAX_N], Q[MAX_M];
int n, S, T, m;
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

int dinic(){
	while (bfs()){
		while (1){
			int ret = dfs(S, SUP);
			if (!ret) break; else ans -= ret;
		}
	}
	return ans;
}

int main(){
	scanf("%d%d", &n, &m);
	S = n + m + 1;
	T = S + 1;
	memset(c, -1, sizeof c);
	int x, y, w;
	for (int i = 1; i <= n; ++i)
		scanf("%d", &x),
		add(i + m, T, x);
	for (int i = 1; i <= m; ++i){
		scanf("%d%d%d", &x, &y, &w);
		add(i, x + m, SUP);
		add(i, y + m, SUP);
		add(S, i, w);
		ans += w;
	}
	printf("%d\n", dinic());
} 

