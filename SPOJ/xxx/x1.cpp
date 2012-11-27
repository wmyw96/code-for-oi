#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
inline void gi(int&x) {
char ch;
while(!isdigit(ch= getchar()) && ch!='-');
if(ch == '-'){
x= 0;
while(isdigit(ch= getchar())) x= x*10 + ch-'0';
x= -x;
}else{
x= ch-'0';
while(isdigit(ch= getchar())) x= x*10 + ch-'0';
}
}
using namespace std;
typedef long long ll;
map<int, set<int> > hsh;
const int MaxN= 50010;
int N, M, a[MaxN], pre[MaxN], ky;
ll v;
struct __node{
ll v, sum;
int ky, sz;
__node*l, *r;
inline void rz(){
sz= l->sz + 1 + r->sz;
sum= l->sum + v + r->sum ;
}
}*bit[MaxN], nil[MaxN*30], *tot;
inline void zig(__node*&cur) {
__node*tmp= cur->l;
cur->l= tmp->r;
tmp->r= cur;
cur->rz();
tmp->rz();
cur= tmp;
}
inline void zag(__node*&cur){
__node*tmp= cur->r;
cur->r= tmp->l;
tmp->l= cur;
cur->rz();
tmp->rz();
cur= tmp;
}
inline void maintain(__node*&cur, bool d){
if(d){
if(cur->r->r->sz > cur->l->sz)
zag(cur);
else
if(cur->r->l->sz > cur->l->sz)
zig(cur->r),
zag(cur);
}else{
if(cur->l->l->sz > cur->r->sz)
zig(cur);
else
if(cur->l->r->sz > cur->r->sz)
zag(cur->l),
zig(cur);
}
}
void insert(__node*&cur){
if(cur == nil){
cur= ++tot;
cur->ky= ky;
cur->sum= cur->v= v;
cur->sz= 1;
cur->l= cur->r= nil;
}else{
if(cur->ky == ky)
cur->v+= v,
cur->rz();
else{
if(ky > cur->ky)
insert(cur->r);
else
insert(cur->l);
cur->rz();
maintain(cur, ky > cur->ky);
}
}
}
inline void erase(__node*cur){
while(cur->ky != ky){
cur->sum-= v;
(ky > cur->ky) ? cur= cur->r : cur= cur->l;
}
cur->v-= v;
cur->sum-= v;
/*if(cur->ky == ky)
cur->v-= v;
else
(ky > cur->ky) ?  erase(cur->r, ky, v) : erase(cur->l, ky, v);
cur->rz();*/
}
inline void modify(bool p, int i){
for(;i<= N;i+= i&-i)
p ? insert(bit[i]) : erase(bit[i]);
}
inline ll rank(int idx, ll ky){
register ll ret(0);
for(__node*cur= bit[idx];cur != nil;ky > cur->ky ? cur= cur->r : cur= cur->l)
ret+= ky > cur->ky ? cur->l->sum + cur->v : 0;
return ret;
}
inline ll query(int i, int pos){
ll ret(0);
for(;i;i-= i&-i)
ret+= i<pos ? bit[i]->sum : rank(i, pos);
return ret;
}
int main(){
	freopen("xxxxxxxx.in","r",stdin);
	freopen("x1.out","w",stdout);
gi(N);
tot= nil->l= nil->r= nil;
for(int i= 1;i<= N;++ i)
bit[i]= nil;
for(int i= 1;i<= N;++ i){
gi(a[i]);
hsh[a[i]].insert(i);
set<int> ::iterator it= hsh[a[i]].find(i);
pre[i]= it == hsh[a[i]].begin() ? 0 : (*--it);
ky= pre[i], v= a[i];
modify(1, i);
}
gi(M);
while(M --){
register char p;
register int x, y;
while(p= getchar(), p<'A' || p>'Z');
gi(x);
gi(y);
if(p == 'U'){
set<int>&tmmmmp= hsh[a[x]];
set<int> ::iterator it= tmmmmp.upper_bound(x);
if(it != tmmmmp.end()){
ky= x, v= a[x];
modify(0, *it);
ky= pre[x], v= a[x];
modify(1, *it);
pre[*it]= pre[x];
}
tmmmmp.erase(x);
ky= pre[x], v= a[x];
modify(0, x);
set<int>&tmp= hsh[a[x]= y];
tmp.insert(x);
it= tmp.find(x);
pre[x]= it == tmp.begin() ? 0 : (*--it);
ky= pre[x], v= a[x];
modify(1, x);
it= tmp.upper_bound(x);
if(it != tmp.end()){
ky= pre[*it], v= a[x];
modify(0, *it);
pre[*it]= x;
ky= pre[*it], v= a[x];
modify(1, *it);
}
}else
printf("%lld\n", query(y, x) - query(x-1, x));
}
return 0;
}
