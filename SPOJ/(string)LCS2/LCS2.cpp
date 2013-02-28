#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<queue>
using namespace std;
queue<int> Q;
const int MAX_N=600000;
struct sam{
	sam *f, *go[26];
	int len[11];
	int l, num;
};
sam samn[MAX_N];
sam *lst;
char st[MAX_N];
int tot;

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
	scanf("%s", &st);
	int l = strlen(st);
	lst = samn;
	for (int i = 0; i < l; ++i) extend(st[i] - 'a');
	int ansf = l;
	
	int N = 0;
	while (scanf("%s", &st)!=-1 && ++N){
		l = strlen(st);
		sam *p = samn;
		int now = 0;
		for (int i = 0; i < l; ++i){
			int c = st[i] - 'a';
			while (p != samn && !p->go[c]){
				p = p->f;
				if (p->l < now) now = p->l;
			}
			if (p->go[c]) p = p->go[c], ++now;
			p->len[N] = max(p->len[N], now);
		}
	}
	for (int i = 0; i <= tot; ++i)
		if (samn[i].num == 0) Q.push(i);
	while (!Q.empty()){
		int i = Q.front();
		Q.pop();
		if (i == 0) continue;
		sam *rt = samn[i].f;
		for (int j = 1; j <= N; ++j)
			rt->len[j] = max(min(rt->l, samn[i].len[j]), rt->len[j]);
		rt->num --;
		if (rt->num == 0) Q.push(rt - samn); 
	}
	int ans = 0;
	for (int i = 0; i <= tot; ++i){
		int ans1 = ansf;
		for (int j = 1; j <= N; ++j)
			if (!samn[i].len[j]) { ans1 = 0; break;}
			else ans1 = min(ans1, samn[i].len[j]);
		ans = max(ans, min(ans1, samn[i].l));
	}
	
	printf("%d\n", ans);
} 

