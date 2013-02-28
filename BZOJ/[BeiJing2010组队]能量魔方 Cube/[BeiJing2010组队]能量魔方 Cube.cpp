#include<iostream> 
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int fx[6] = {1, -1, 0, 0, 0, 0},
		  fy[6] = {0, 0, -1, 1, 0, 0},
		  fz[6] = {0, 0, 0, 0, 1, -1};
const int MAX_L = 41, MAX_N = 200001, MAX_M = 3000001, SUP = 10000000;
int a[MAX_L][MAX_L][MAX_L], mk[MAX_L][MAX_L][MAX_L];
char pp[MAX_L][MAX_L][MAX_L];
int g[MAX_M], next[MAX_M], c[MAX_N], flow[MAX_M], nm, d[MAX_N], Q[MAX_M];
int S, T, N, ans, n;
char st[MAX_L];

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

int main(){
	scanf("%d", &n);
	memset(c, -1, sizeof c);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j){
			scanf("%s", &st);
			for (int k = 1; k <= n; ++k){
				if (st[k - 1] == '?') a[i][j][k] = 0, mk[i][j][k] = ++N;
				if (st[k - 1] == 'P') a[i][j][k] = 1;
				if (st[k - 1] == 'N') a[i][j][k] = -1;
			}
	}

	for (int i = 1; i <= n; ++i){
		pp[i][1][1] = pp[i - 1][1][1] ^ 1;
		for (int j = 1; j <= n; ++j){
			if (j != 1) pp[i][j][1] = pp[i][j - 1][1] ^ 1;
			for (int k = 2; k <= n; ++k)
				pp[i][j][k] = pp[i][j][k - 1] ^ 1;
		}
	}

	/*for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= n; ++j){
			for (int k = 1; k <= n; ++k)
				printf("%d ",pp[i][j][k]);
			printf("\n");
		}
		printf("\n");
	}*/

	S = N + 1;
	T = S + 1;
	int ans1 = 0;

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			for (int k = 1; k <= n; ++k)
				if (mk[i][j][k]){
					int lx = 0, ly = 0;
					for (int p = 0; p < 6; ++p){
						int ii = i + fx[p], jj = j + fy[p], kk = k + fz[p];
						if (ii > 0 && jj > 0 && kk > 0 && ii <= n && jj <= n && kk <= n){
							if (a[ii][jj][kk] == 0) add(mk[i][j][k], mk[ii][jj][kk], 1), ans1++;
							else {
								ans++;
								if (a[ii][jj][kk] == 1) lx++; else ly++;
							}
						}
					}
					if (pp[i][j][k])
					   add(S, mk[i][j][k], lx),
					   add(mk[i][j][k], T, ly);
		             		else add(S, mk[i][j][k], ly), add(mk[i][j][k], T, lx);
				}
				else{
					for (int p = 0; p < 6; ++p){
						int ii = i + fx[p], jj = j + fy[p], kk = k + fz[p];
						if (ii > 0 && jj > 0 && kk > 0 && ii <= n && jj <= n && kk <= n)
							if (a[ii][jj][kk] * a[i][j][k] == -1) ans1++;
					}					
				}
	ans = ans + ans1 / 2;
	while (bfs()){
		while (1){
			int ret = dfs(S, SUP);
			if (ret) ans -= ret; else break;
		}
	}
	printf("%d\n", ans);
} 

