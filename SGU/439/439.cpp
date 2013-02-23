#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std;
const int MAX_N = 1000011;
/*
define of SAM

struct sam{
	sam *f;
	map<char, sam*> go;
	int l;
};
sam samn[MAX_N * 2];
sam *lst;
int tot;
*/

/*
define of main
*/
int n, m;
char st1[MAX_N * 2], st2[MAX_N], ans[MAX_N], st3[MAX_N * 2];

struct ex_kmp{
	int lcp[MAX_N * 2], nxt[MAX_N];
	
	void clear(){
		memset(lcp, 0, sizeof lcp);
		memset(nxt, 0, sizeof nxt);
	}
	
	void build(int N, int M, char *a, char *b){
		int j, k;
		for (j = 0; j < M && b[j] == b[j + 1]; ++j);
		nxt[1] = j;
		k = 1;
		for (int i = 2; i < M; ++i){
			int p = k + nxt[k], l = nxt[i - k];
			if (l + i < p) nxt[i] = nxt[i - k];
			else{
				for (j = max(0, p - i); j < M && b[j] == b[j + i]; ++j);
				nxt[i] = j;
				k = i;
			}
		}
		
		for (j = 0; j < N && j < M && b[j] == a[j]; ++j);
		lcp[0] = j;
		
		k = 0;
		for (int i = 1; i < N; ++i){
			int p = k + lcp[k], l = nxt[i - k];
			if (l + i < p) lcp[i] = l;
			else{
				for (j = max(0, p - i); j < N && j < M && b[j] == a[j + i]; ++j);
				lcp[i] = j;
				k = i;
			}
		}
	}
}s1, s2; 

void minget(){
	for (int i = 0; i < 2 * m; ++i) st3[i] = st2[i % m];
	int i = 0, k, p;
	for (int j = 1; j < m;){
		for (k = 0; k < m && st3[i + k] == st3[j + k]; ++k);
		if (k >= m) break;
		if (st3[i + k] < st3[j + k]) j += k + 1;
		else p = j, j = max(j, i + k) + 1, i = p;
	} 
	strncpy(st2, st3 + i, m);
}

/*void extend(int c){
	sam *p = lst;
	sam *np = samn + (++tot);
	np->l = p->l + 1;
	while (p && !p->go[c]) p->go[c] = np, p = p->f;
	if (!p) np->f = samn;
	else{
		sam *q = p->go[c];
		if (q->l == p->l + 1) np->f = q;
		else{
			sam *nq = samn + (++tot);
			nq->l = p->l + 1;
			nq->go = q->go;
			nq->f = q->f;
			q->f = np->f = nq;
			while (p && p->go[c] == q) p->go[c] = nq, p = p->f;
		}
	}
	lst = np;
}

void minget(){
	lst = samn;
	for (int i = 1; i <= m; ++i) extend(st2[i - 1] - 'A');
	for (int i = 1; i <= m; ++i) extend(st2[i - 1] - 'A');
	sam *p = samn;
	for (int i = 1; i <= m; ++i){
		for (int k = 0; k < 26; ++k)
			if (p->go[k]) {st2[i - 1] = k + 'A'; p = p->go[k]; break;}
	}
	st2[m] = '\0';
}*/

int main(){
	scanf("%d%d", &n, &m);
	scanf("%s", &st1);
	scanf("%s", &st2);
	minget();
	for (int i = n; i < 2 * n; ++i) st1[i] = st1[i - n];
	st1[2 * n] = '\0';
	n *= 2;
	printf("%s\n", st2);
	s1.clear();
	s1.build(n, m, st1, st2);
	
	s2.clear();
	
	for (int i = 0; i < n / 2; ++i) swap(st1[i], st1[n - i - 1]);
	for (int i = 0; i < m / 2; ++i) swap(st2[i], st2[m - i - 1]);
	s2.build(n, m, st1, st2);
	
	for (int i = 0; i < n / 2; ++i) swap(st1[i], st1[n - i - 1]);
	
	int ansn = n + 1, ansp = n + 1;
	for (int i = 0; i < n / 2; ++i){
		if (s1.lcp[i] + s2.lcp[n - (i + m - 1) - 1] == m - 1 || s1.lcp[i] == m){
			if (min(i, n / 2 - i) < ansp) ansp = min(i, n / 2 - i), ansn = i;
			    else if (min(i, n / 2 - i) == ansp) ansn = min(i, ansn);
		}
	}
	strncpy(ans, st1 + ansn, n / 2);
	ans[n] = '\0';
	printf("%s\n", ans);
} 


