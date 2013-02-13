#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
using namespace std;

const int MAX_N=300001;
typedef int LL;
struct sam{
	sam *f, *go[26];
	char re[26];
	int l, R, mk;
}; 
sam samn[MAX_N];
sam *lst;
int stot,nm;
LL f[MAX_N];
int calc[MAX_N];
int g[MAX_N], next[MAX_N], c[MAX_N], num[MAX_N], Q[MAX_N];
char st[MAX_N];
char ans[MAX_N];

inline void extend(int c){
	sam *p = lst;
	sam *np = samn + (++stot);
	np->l = p->l + 1;
	while (p && !p->go[c]) p->go[c] = np, p = p->f;
	if (!p) np->f = samn;
	else{
		sam *q = p->go[c];
		if (q->l == p->l + 1) np->f = q;
		else{
			sam *nq = samn + (++stot);
			nq->l = p->l + 1;
			memcpy(nq->go, q->go, sizeof nq->go);
			nq->f = q->f;
			q->f = np->f = nq;
			while (p && p->go[c]==q) p->go[c] = nq, p = p->f;
		}
	}
	lst = np; 
}

void addedge(int x,int y){
	g[++nm] = y; next[nm] = c[x]; c[x] = nm;
}

int main(){
	int l = 0;
	char ch;
	while ((ch = getchar()) != '\n') st[l++] = ch;
	lst = samn;
	
	for (int i = 0; i < l; i++) extend(st[i]-'a');
	
	for (int i = 0; i <= stot; ++i){
		sam *p = samn + i;
		for (int k = 0; k < 26; ++k)
		if (p->go[k]){
			++p->R;
			p->re[p->R] = k;
			num[i]++;
			addedge(p->go[k] - samn, i);
		}
	}
	int r = 0;
	for (int i = 0; i <= stot; ++i){
		if (num[i]==0) Q[++r] = i;
		f[i] = 1;
	}
	
	for (int l = 1; l <= r; ++l){
		int i = Q[l];
		for (int k = c[i]; k; k = next[k]){
			int j = g[k];
			num[j]--;
			if (!num[j]) Q[++r] = j;
			f[j] += f[i];
		}
	}
	
	int Q, k;
	scanf("%d", &Q);
	while (Q--){
		scanf("%d", &k);
		sam *now = samn;
		int ansn = 0;

		for (; k != 0;){
				for (int i = 1; i <= now->R; ++i){
					int j = now->re[i];
					if (f[now->go[j] - samn] >= k){
						k--;
						ans[ansn++] = j + 'a';
						now = now->go[j];
						break;
					}
					else k -= f[now->go[j] - samn];
				}
		}
		
		ans[ansn] = '\0';
		puts(ans);
	}
}

