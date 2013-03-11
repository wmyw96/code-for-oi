#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAX_N = 100001, MAX_M = 100001, SUP = 1000000000;
int g[MAX_M], next[MAX_M], c[MAX_N], flow[MAX_M], nm, d[MAX_N], Q[MAX_M];
int a[301][301];
int w[MAX_N], rest[MAX_N];
int n, S, T, cm;

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

int gt(int i){
    return i + 2 - 1;
}

int gm(){
    return ++cm + n - 1 + 2;
}

int main(){
    memset(c, -1, sizeof c);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &rest[i]);
    int limit = w[1] + rest[1];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d", &a[i][j]);
    S = 1;
    T = 2;
    int sup = 0;
    for (int i = 2; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (a[i][j] > 0){
               int ret = gm();
               add(gt(i), ret, a[i][j]);
               add(gt(j), ret, a[i][j]);
               add(ret, T, a[i][j]);
               sup += a[i][j];
            }
    int ck = 1;
    for (int i = 2; i <= n; ++i)
        if (limit - w[i] >= 0) add(S, gt(i), limit - w[i]);
                                else ck = 0;
    
    int ans = 0;
    while (bfs() && ck){
          int ret = dfs(S, SUP);
          ans += ret;
    }
    if (ans >= sup && ck) printf("YES\n"); else printf("NO\n");
}

/*
3
2 2 2
1 2 2
0 0 0
0 0 2
0 2 0
*/
