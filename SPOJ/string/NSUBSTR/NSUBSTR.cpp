#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<queue>
#include<algorithm>
using namespace std;
queue<int> Q;
const int MAX_N=1000000;
int num[MAX_N], s[MAX_N], F[MAX_N];
struct sam{
	sam *par, *go[26];
	int l, mk;
};
sam samn[MAX_N];
sam *lst;
char st[MAX_N];
int stot,nm;

void extend(int c){
	sam *p = lst;
	sam *np = samn + (++stot);
	np->mk = stot;
	np->l = p->l + 1;
	for (; p && !p->go[c];) p->go[c] = np, p = p->par;
	if (!p) np->par = samn, num[0]++;
	else{
			sam *q = p->go[c];
			if (p->l + 1 == q->l) np->par = q, num[q->mk]++;
			else{
				sam *nq = samn + (++stot);
				nq->mk = stot;
				nq->l = p->l + 1;
				memcpy(nq->go, q->go, sizeof nq->go);
				nq->par = q->par;
				q->par = np->par = nq;
				num[nq->mk] += 2;
				//num[q->par->mk]++;
				while (p && p->go[c]==q) p->go[c] = nq, p = p->par;
			} 
	}
	lst = np;
}

int main(){
	lst = samn;
	scanf("%s", &st);
	int len = strlen(st);
	for (int i = 0; i < len; i++) extend(st[i]-'a');
	sam *a = samn;
	for (int i = 0; i < len; ++i) ++s[(a = a->go[st[i]-'a']) - samn];
	for (int i = 1; i <= lst->mk; ++i)
		if (num[i]==0) Q.push(i);
	while (!Q.empty()){
		int i = Q.front();
		Q.pop();
		if (i == 0) continue;
		s[samn[i].par->mk] += s[i];
		num[samn[i].par->mk]--;
		if (num[samn[i].par->mk] == 0) Q.push(samn[i].par->mk); 
	}
	for (int i = 1; i <= lst->mk; ++i) F[samn[i].l] = max(F[samn[i].l], s[i]);
	for (int i = len; i >= 2; --i) F[i-1] = max(F[i], F[i-1]);
	for (int i = 1; i <= len; ++i) printf("%d\n", F[i]);
} 
