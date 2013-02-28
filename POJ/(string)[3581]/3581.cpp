#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
using namespace std;

set<int> S;
map<int, int> M;
set<int>::iterator tmp, tmp2;
const int MAX_N = 1000001;
struct se{
	int a, b, c;
	void mp(int x, int y, int z){
		a = x; b = y; c = z;
	}
};
se s1[MAX_N], s2[MAX_N];
int rk[MAX_N], cnt[MAX_N], a[MAX_N], b[MAX_N];
int n, N;

int build(int w){
	if (w > n) return n + 1;
	for (int i = 1; i <= n; ++i) s1[i].mp(rk[i], rk[i + w], i);
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) cnt[s1[i].b]++;
	for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) s2[cnt[s1[i].b]--] = s1[i];
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) cnt[s2[i].a]++;
	for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) s1[cnt[s2[i].a]--] = s2[i];
	int ret = 0;
	for (int i = 1; i <= n; ++i)
		rk[s1[i].c] = rk[s1[i - 1].c] + (s1[i].a != s1[i - 1].a || s1[i].b != s1[i - 1].b),
		ret = max(ret, rk[s1[i].c]);
	return ret;
}

int build2(int w){
	if (w >= n) return n + 1;
	for (int i = 1; i <= n; ++i) s1[i].mp(rk[i], rk[(i + w > n) ? ((i + w) % (n + 1) + 1) : (i + w)], i);
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) cnt[s1[i].b]++;
	for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) s2[cnt[s1[i].b]--] = s1[i];
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) cnt[s2[i].a]++;
	for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) s1[cnt[s2[i].a]--] = s2[i];
	int ret = 0;
	for (int i = 1; i <= n; ++i)
		rk[s1[i].c] = rk[s1[i - 1].c] + (s1[i].a != s1[i - 1].a || s1[i].b != s1[i - 1].b),
		ret = max(ret, rk[s1[i].c]);
	return ret;
}

int calc(int l, int r){
    n = 0;
    memset(rk, 0, sizeof rk);
    memset(a, 0, sizeof a);
    S.clear();
    M.clear();
    
    for (int i = l; i <= r; ++i) a[++n] = b[i];
    
    for (int i = 1; i <= n; ++i) S.insert(a[i]);
    for (int i = 1; i <= n / 2; ++i) swap(a[i], a[n - i + 1]);
    for (tmp = S.begin(); tmp != S.end(); tmp++){
        if (tmp == S.begin()) M[*tmp] = 1;
        tmp2 = tmp;
        tmp2++;
        if (tmp2 != S.end()) M[*tmp2] = M[*tmp] + 1;
    }
    for (int i = 1; i <= n; ++i) rk[i] = M[a[i]];
    
	for (int i = 1; i <= n && build(i) < n; i <<= 1);
	
    for (int i = 1; i <= n; ++i)
        if (rk[i] == 1) return n - i + l;
}

int calc2(int l, int r){
    n = 0;
    memset(rk, 0, sizeof rk);
    memset(a, 0, sizeof a);
    S.clear();
    M.clear();
    
    for (int i = l; i <= r; ++i) a[++n] = b[i];
    
    for (int i = 1; i <= n; ++i) S.insert(a[i]);
    for (int i = 1; i <= n / 2; ++i) swap(a[i], a[n - i + 1]);
    for (tmp = S.begin(); tmp != S.end(); tmp++){
        if (tmp == S.begin()) M[*tmp] = 1;
        tmp2 = tmp;
        tmp2++;
        if (tmp2 != S.end()) M[*tmp2] = M[*tmp] + 1;
    }
    for (int i = 1; i <= n; ++i) rk[i] = M[a[i]];
    
	for (int i = 1; i <= n && build2(i) < n; i <<= 1);
    if (rk[1] == 1){
       for (int i = 2; i <= n; ++i)
           if (rk[i] == 2 || rk[i] == 1) return n - i + l;
	}
    else {
    	for (int i = 2; i <= n; ++i)
    		if (rk[i] == 1) return n - i + l;
	}
}

int main(){
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", &b[i]);
    int a1 = calc(1, N - 2);
    int a2 = calc2(a1 + 1, N);
    for (int i = a1; i >= 1; --i) printf("%d\n", b[i]);
    for (int i = a2; i > a1; --i) printf("%d\n", b[i]);
    for (int i = N; i > a2; --i) printf("%d\n", b[i]);
}

/*
20
20 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

7
10 0 2 2 2 2 1

7
10 0 2 2 2 2 3
*/
