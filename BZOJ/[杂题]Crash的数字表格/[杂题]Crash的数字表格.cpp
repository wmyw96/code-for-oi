#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
 
typedef long long LL;
const int MAX_N = 10000011,MOD=20101009;
int n, m, cnt, N;
int P[MAX_N], c[MAX_N];
char u[MAX_N];
LL g[MAX_N], s[MAX_N];
int ans;
 
void init(){
	u[1] = 1;
	g[1] = 1;
	for (int i = 2; i < N; i++){
		if (!c[i]){
			c[i] = i;
			u[i] = -1;
			g[i] = -i+1;
			P[++cnt] = i;
		}
		else{
             int now = i;
             while (now > 1){
                   int ret = c[now];
                   now /= ret;
                   if (now==1) g[i] = -ret + 1;
                   else
                        if (c[now] != ret) {g[i] = g[now] * g[i/now];break;}
             }
        }
		for (int j = 1; j <= cnt; j++){
			if ((LL)i * P[j] >= N) break;
			c[i * P[j]] = P[j];
			if (c[i] == P[j]) u[i * P[j]] =0;
						else u[i * P[j]] = -u[i];
			if (i % P[j] == 0) break;
		}
		s[i] = s[i - 1] + g[i];
	}
}

int main(){
	scanf("%d%d", &n, &m);
	N = max(n, m)+1;
	init();
	for (int T = 1; T <= min(n,m); T++){
		int x = (n / T);
		int y = (m / T);
		int nn = ((LL)x * (x + 1) / 2) % MOD; 
		int mm = ((LL)y * (y + 1) / 2) % MOD;
		ans += g[T] * T %MOD *nn %MOD *mm %MOD;
		if (ans < 0) ans += MOD;
		ans %= MOD;
	}
	cout<< ans <<endl;
} 
