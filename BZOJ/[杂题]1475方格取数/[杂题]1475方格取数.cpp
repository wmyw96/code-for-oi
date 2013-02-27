#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAX_N = 100001, MAX_M = 100001, SUP = 10000000;
int g[MAX_M], next[MAX_M], c[MAX_N], flow[MAX_M], nm, d[MAX_N], Q[MAX_M];
int a[301][301], mk[301][301];
int n, S, T;
LL ans;

void addedge(int x, int y, int w){
	g[nm] = y;
	next[nm] = c[x];
	c[x] = nm;
	flow[nm] = w;
	nm++;
}

void add(int x, int y, int w){
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

int main(){
	scanf("%d", &n);
	nm = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", &a[i][j]),
			ans += a[i][j],
			mk[i][j] = (j == 1) ? (i & 1) : (!mk[i][j - 1]);
	S = n * n + 1;
	T = S + 1;
	memset(c, -1, sizeof c);
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j){
			if (mk[i][j]) add(S, m(i, j), a[i][j]);
				else add(m(i, j), T, a[i][j]);
			if (mk[i][j]){
				if (i > 1) add(m(i, j), m(i - 1, j), SUP);
				if (j > 1) add(m(i, j), m(i, j - 1), SUP);
				if (i < n) add(m(i, j), m(i + 1, j), SUP);
				if (j < n) add(m(i, j), m(i, j + 1), SUP);
			}
		}
	while (bfs()){
		while (1){
			int ret = dfs(S, SUP);
			if (ret) ans -= ret; else break;
		}
	}
	cout<<ans<<endl;
} 

/*
3
10 3 1000
10000 1 10
1 10 100
*/
