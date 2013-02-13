#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;

const int MAX_N=600000;
struct sam{
	sam *f, *go[26];
	int l;
};
sam samn[MAX_N];
sam *lst;
char st[MAX_N];
int tot;

inline void extend(int c){
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

int main(){
	scanf("%s", &st);
	int l = strlen(st);
	lst = samn;
	for (int i = 0; i < l; ++i) extend(st[i] - 'a');
	scanf("%s", &st);
	l = strlen(st);
	sam *p = samn;
	int now = 0, ans = 0;
	for (int i = 0; i < l; ++i){
		int c = st[i] - 'a';
		while (p != samn && !p->go[c]){
			p = p->f;
			if (p->l < now) now = p->l;
		}
		if (p->go[c]) p = p->go[c], ++now;
		ans = max(ans, now);
	}
	printf("%d\n", ans);
} 
