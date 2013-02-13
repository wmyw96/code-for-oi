#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;

struct sam{
	sam *f, *go[256];
	int l, rt, num;
	void rec(int rtt, int ll){
		memset(this->go, NULL, sizeof this->go);
		this->rt = rtt, this->l = ll;
	} 
};
sam samn[100101];
char st[50001];
sam *lst;
int tot;
queue<int> Q;

void extend(int c){
	sam *p = lst;
	sam *np = samn + (++tot);
	np->rec(1, p->l + 1);
	while (p && !p->go[c]) p->go[c] = np, p = p->f;
	if (!p) np->f = samn, samn[0].num++;
	else{
		sam *q = p->go[c];
		if (q->l == p->l + 1) np->f = q, q->num++;
		else{
			sam *nq = samn + (++tot);
			nq->rec(0, p->l + 1);
			memcpy(nq->go, q->go, sizeof nq->go);
			nq->f = q->f;
			q->f = np->f = nq;
			nq->num += 2;
			while (p && p->go[c] == q) p->go[c] = nq, p = p->f;
		}
	} 
	lst = np;
}
int main(){
	int Ti;
	scanf("%d", &Ti);
	while (Ti--){
		lst = samn;
		lst->rec(0, 0);
		tot = 0;
		scanf("%s", &st);
		int l = strlen(st);
		for (int i = 0; i < l; ++i) extend(st[i]);
		/*for (int i = 0; i <= tot; ++i)
			if (!samn[i].num) Q.push(i);
		while (!Q.empty()){
			int i = Q.front(); Q.pop();
			if (!i) continue;
			sam *p = samn + i;
			p->f->rt += p->rt; p->f->num--;
			if (p->f->num == 0) Q.push(p->f - samn);
		}*/
		int ans = 0;
		for (int i = 1; i <= tot; ++i){
			sam *p = samn + i;
			ans += (p->l - p->f->l);
		}
		printf("%d\n", ans);
	}
} 
