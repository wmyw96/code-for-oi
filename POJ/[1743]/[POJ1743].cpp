#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;
const int SUP = 2147483647;
struct sam{
	sam *f;
	int l, num, rt, ft, mn, mx;
	sam *go[178];
	void rec(int ll, int ftt, int mnn, int mxx, int rtt){
		memset(this->go, NULL, sizeof this->go);
		this->l = ll;
		this->ft = ftt;
		this->mn = mnn;
		this->mx = mxx;
		this->rt = rtt;
		this->num = 0;
		this->f = NULL;
	}
	void up(int mn1, int mx1, int rt1){
		this->rt += rt1;
		this->mn = min(this->mn, mn1);
		this->mx = max(this->mx, mx1);
	}
}; 
sam samn[40101];
sam *lst;
char a[20001];
int tot, n;
queue<int> Q;

void extend(int c, int ll){
	sam *p = lst;
	sam *np = samn + (++tot);
	np->rec(p->l + 1, ll, ll, ll, 1);
	while (p && !p->go[c]) p->go[c] = np, p = p->f;
	if (!p) np->f = samn, samn[0].num++;
	else{
		sam *q = p->go[c];
		if (q->l == p->l + 1) np->f = q, q->num++;
		else{
			sam *nq = samn + (++tot);
			nq->rec(p->l + 1, 0, SUP, -SUP, 0);
			memcpy(nq->go, q->go, sizeof nq->go);
			nq->f = q->f;
			q->f = np->f = nq;
			while (p && p->go[c] == q) p->go[c] = nq, p = p->f;
		}
	}
	lst = np;
} 

int main(){
	while (scanf("%d",&n)!=EOF){
		if (!n) break;
		tot = 0;
		lst = samn;
		lst->rec(0, 0, SUP, -SUP, 0);
		for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
		for (int i = 1; i < n; ++i) extend(a[i] - a[i-1] + 88, i);
		for (int i = 0; i <= tot; ++i)
			if (samn[i].num == 0) Q.push(i);
		while (!Q.empty()){
			int i = Q.front(); Q.pop();
			if (i == 0) continue;
			sam *p = samn + i; sam *q = p->f;
			q->up(p->mn, p->mx, p->rt);
			q->num--;
			if (q->num == 0) Q.push(q - samn);
		} 
		int ans = 0;
		for (int i = 0 ; i <= tot; ++i)
			if (samn[i].rt >= 2) ans = max(ans, min(samn[i].mx - samn[i].mn - 1, samn[i].l));
		if (ans > 3) printf("%d\n", ans + 1); else printf("%d\n", 0);
	}
}

