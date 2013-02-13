#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<map>
#include<queue>
using namespace std;

struct sam{
	sam *f;
	map<int, sam*> go;
	int l, num, rt;
};
sam samn[41001];
sam *lst;
int tot, st[41001];
queue<int> Q;

void extend(int c){
	sam *p = lst;
	sam *np = samn + (++tot);
	np->l = p->l + 1;
	while (p && !p->go[c]) p->go[c] = np, p = p->f;
	if (!p) np->f = samn, samn[0].num++;
	else{
		sam *q = p->go[c];
		if (q->l == p->l + 1) np->f = q, q->num++;
		else{
			sam *nq = samn + (++tot);
			nq->l = p->l + 1;
			nq->go = q->go;
			nq->f = q->f;
			q->f = np->f = nq;
			nq->num += 2;
			while (p && p->go[c] == q) p->go[c] = nq, p = p->f;
		}
	}
	lst = np;
}

int main(){
	int l, k;
	scanf("%d%d", &l, &k);
	for (int i = 0; i < l; ++i) scanf("%d", &st[i]);
	lst = samn;
	
	for (int i = 0; i < l; ++i) extend(st[i]);
	sam *p = samn;
	for (int i = 0; i < l; ++i) 
		p = p->go[st[i]], ++ p->rt;
	for (int i = 0; i <= tot; ++i) if (!samn[i].num) Q.push(i);
	while (!Q.empty()){
		int i = Q.front(); Q.pop();
		if (i == 0) continue;
		sam *p = samn + i; p->f->rt += p->rt; p->f->num--;
		if (!p->f->num) Q.push(p->f - samn);
	}
	int ans = 0;
	for (int i = 0; i <= tot; ++i) if (samn[i].rt >= k) ans = max(ans, samn[i].l);
	printf("%d\n", ans);
}

