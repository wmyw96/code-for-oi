#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAX_N = 100001, MAX_M = 20001, SUP = 1000000000;
int nm, g[MAX_M], next[MAX_M], c[MAX_N], flow[MAX_M], Q[MAX_N], d[MAX_N];
int gg[MAX_N], nextt[MAX_N], cc[MAX_N], floww[MAX_N];
int n, m, S, T, ansn;
int ans_lt[MAX_N], ans_mk[MAX_N];

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
	while (l <= r){
		int i = Q[l];
		l++;
		for (int k = c[i]; k != -1; k = next[k]){
			int j = g[k];
			if (flow[k] && d[j] == -1)
				d[j] = d[i] + 1, Q[++r] = j;
		}
	}
	return d[T] != -1;
}

int dfs(int i, int now){
	if (i == T) return now;
	if (now == 0) return 0;
	int w = 0;
	for (int k = c[i]; k != -1 && w < now; k = next[k]){
		int j = g[k], rst = min(flow[k], now - w), ret = 0;
		if (d[j] == d[i] + 1)
			if ((ret = dfs(j, rst)) > 0){
				flow[k] -= ret;
				flow[k ^ 1] += ret;
				w += ret;
			}
	}
	if (!w) d[i] = -1;
	return w;
}

int dinic(){
	int ans = 0;
	while (bfs()){
		while (1){
			int ret = dfs(S, SUP);
			if (!ret) break; else ans+=ret;
		}
	}
	return ans;
}

int in(int i){
	return n + i;
}

int out(int i){
	return i;
}

int cek(){
	memcpy(g, gg, sizeof g);
	memcpy(next, nextt, sizeof next);
	memcpy(c, cc, sizeof c);
	memcpy(flow, floww, sizeof flow);
	return dinic();
}

int main(){
	scanf("%d%d", &n, &m);
	memset(c, -1, sizeof c);
	int ct, x, y;
	S = n * 2 + 1;
	T = S + 1;
	for (int i = 1; i <= n; ++i)
		scanf("%d", &ct), add(in(i), T, ct);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &ct), add(S, out(i), ct);
		
	for (int i = 1; i <= m; ++i){
		scanf("%d%d", &x, &y);
		add(out(x), in(y), SUP);
	} 
	
	memcpy(gg, g, sizeof gg);
	memcpy(nextt, next, sizeof nextt);
	memcpy(cc, c, sizeof cc);
	memcpy(floww, flow, sizeof floww);
	
	int ans, ans1;
	printf("%d\n", ans = dinic());
	//out---> '-'
	for (int k = c[S]; k != -1; k = next[k]){
		int i = g[k];
		if (flow[k] == 0 && flow[k ^ 1] > 0){
			int ret = floww[k];
			floww[k] = 0;
			ans1 = cek();
			if (ans - ans1 == ret){
				ans_lt[++ansn] = i;
				ans_mk[ansn] = 0;	
				ans = ans1;		
			}
			else floww[k] = ret;
		}
	}
	//in--->'+'
	for (int k = c[T]; k != -1; k = next[k]){
		int i = g[k];
		if (flow[k ^ 1] == 0 && flow[k] > 0){
			int ret = floww[k ^ 1];
			floww[k ^ 1] = 0;
			ans1 = cek();
			if (ans - ans1 == ret){
				ans_lt[++ansn] = i - n;
				ans_mk[ansn] = 1;	
				ans = ans1;		
			}
			else floww[k ^ 1] = ret;
		}
	}
	printf("%d\n", ansn);
	for (int i = 1; i <= ansn; ++i){
		printf("%d %c\n", ans_lt[i], ((ans_mk[i]) ? ('+') : ('-')));
	}
} 
