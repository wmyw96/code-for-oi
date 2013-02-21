#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
/*
define of SAM
*/
struct sam{
	sam *f, *go[26];
	int l;
};
sam samn[2000001];
sam *lst;
int tot;

/*
define of main
*/
int n, m;
char st1[1000001], st2[1000001];

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
			if (p->go[k]) {st2[i - 1] = k + 'A'; p = p->go[k]; break;}
	}
	st2[m] = '\0';
}

int main(){
	scanf("%d%d", &n, &m);
	scanf("%s", &st1);
	scanf("%s", &st2);
	minget();
	printf("%s\n", st2);
} 

