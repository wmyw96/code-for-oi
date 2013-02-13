#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;

struct sam{
	sam *f;
	map<char, sam*> go;
 	int l, rt, num;
	void rec(int rtt, int ll){
		this->rt = rtt, this->l = ll;
	} 
};
sam samn[110101];
char st[50001];
sam *lst;
int tot;

void extend(int c){
	sam *p = lst;
	sam *np = samn + (++tot);
	np->rec(1, p->l + 1);
	np->go.clear();
	while (p && !p->go[c]) p->go[c] = np, p = p->f;
	if (!p) np->f = samn;
	else{
		sam *q = p->go[c];
		if (q->l == p->l + 1) np->f = q;
		else{
			sam *nq = samn + (++tot);
			nq->rec(0, p->l + 1);
			nq->go = q->go;
			nq->f = q->f;
			q->f = np->f = nq;
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
		lst->go.clear();
		tot = 0;
		scanf("%s", &st);
		int l = strlen(st);
		for (int i = 0; i < l; ++i) extend(st[i]);
		long long ans = 0;
		for (int i = 1; i <= tot; ++i){
			sam *p = samn + i;
			ans += (p->l - p->f->l);
		}
		cout<<ans<<endl;
	}
} 
