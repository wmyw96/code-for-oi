#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAX_N = 1100001;
/*
define of SAM
*/
struct sam{
	sam *f, *go[26];
	int l;
};
sam samn[MAX_N * 2];
sam *lst;
int tot;

/*
define of main
*/
int n, m;
char st1[MAX_N], st2[MAX_N];

struct ex_kmp{
	int ret[MAX_N], nxt[MAX_N];
	
	void clear(){
		memset(ret, 0, sizeof ret);
		memset(nxt, 0, sizeof nxt);
	}
	
	void build(int N, int M, char *a, char *b){
		int i, j, k;
		for (j = 0; 1 + j <= M && b[j + 1] == b[j + 2]; j++) printf("%c",b[j]);
		nxt[1] = M;
		nxt[2] = j;
		printf("%d\n", nxt[2]);
		k = 2;
		for (int i = 3; i <= M; ++i){
			int r = k + nxt[k] - 1, L = nxt[i - k + 1];
			if (L + i - 1 < r) nxt[i] = L;
			else{
				for (j = max(0, r - i + 1); i + j <= M && a[j] == a[j + i]; ++j);
				nxt[i] = j;
				k = i;
			}
			printf("%d\n", nxt[i]);
		}
	}
	
}s1, s2; 

void extend(int c){
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
			memcpy(nq->go, q->go, sizeof nq->go);
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
			if (p->go[k]) {st2[i] = k + 'A'; p = p->go[k]; break;}
	}
	st2[m + 1] = '\0';
}



int main(){
	scanf("%d%d", &n, &m);
	scanf("%s", &st1);
	scanf("%s", &st2);
	minget();
	printf("%s\n", st2);
	s1.clear();
	s1.build(0, m, st1, st2);
} 

