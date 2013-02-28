#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int N = 50005 * 2;
struct node{
int f, s;
int pos;
node(int f = 0, int s = 0, int pos = 0){
   this->set(f, s, pos);
}
void set(int f, int s, int pos){
   this->f = f;
   this->s = s;
   this->pos = pos;
}
bool operator==(node n){
   return this->f == n.f && this->s == n.s;
}
bool operator!=(node n){
   return ! this->operator ==(n);
}
}nodes[N];
struct e{
node y;
int next;
}edges[N];
struct seg{
int l, r;
}segs[N * 2];
char str[N];
int sa[N], rank[N], first[N], h[N], Min[20][N];
int n, tot;
int compu_rank(){
int p = 1, i;
rank[nodes[0].pos] = 1;
for(i = 1; i < n; i++){
   if(nodes[i] != nodes[i - 1]) p++;
   rank[nodes[i].pos] = p;
}
return p;
}
bool cmp1(node n1, node n2){
return n1.f < n2.f;
}
bool cmp2(seg s1, seg s2){
if(s1.l != s2.l) return s1.l < s2.l;
return s1.r > s2.r;
}
void radix_sort(){
int e, tot, i, cur;
for(i = 0; i <= n; i++) first[i] = -1;
//根据第二个关键字排序
e = 0;
for(i = 0; i < n; i++){ //很类似于构有向图
   edges[e].y = nodes[i];
   edges[e].next = first[nodes[i].s];
   first[nodes[i].s] = e++;
}
tot = 0;
for(i = 0; i < n; i++){
   cur = first[i];
   while(cur != -1){
    nodes[tot++] = edges[cur].y;
    cur = edges[cur].next;
   }
}
//根据第一个关键字排序
e = 0;
for(i = 0; i <= n; i++) first[i] = -1;
for(i = n - 1; i >= 0; i--){ 
   //这个是为了保证在下一个循环语句中访问第一个关键字相同的串时，会从第二个关键字小的开始
   edges[e].y = nodes[i];
   edges[e].next = first[nodes[i].f];
   first[nodes[i].f] = e++;
}
tot = 0;
for(i = 0; i < n; i++){
   cur = first[i];
   while(cur != -1){
    nodes[tot++] = edges[cur].y;
    cur = edges[cur].next;
   }
}
}
void compu_sa(){
int i, p, j;
for(i = 0; i < n; i++) nodes[i].set(str[i], 0, i);
sort(nodes, nodes + n, cmp1);
p = compu_rank();
for(j = 1; j < n && p < n; j *= 2){
   for(i = 0; i < n; i++){
    nodes[i].set(rank[i], 0, i);
    if(i + j < n) nodes[i].s = rank[i + j];
   }
   radix_sort();
   p = compu_rank(); 
}
//rank变为从0开始
for(i = 0; i < n; i++) rank[i]--; 
for(i = 0; i < n; i++) sa[rank[i]] = i;

}
void compu_h(){
int i, k = 0, s;
h[0] = 0;
for(i = 0; i < n; i++){
   if(rank[i] == 0){
    h[rank[i]] = k = 0;
   }else{
    if(k > 0) k--;
    s = sa[rank[i] - 1];
    while(s + k < n && i + k < n && str[s + k] == str[i + k]) 
     k++;
    h[rank[i]] = k;
   }
}
//for(i = 0; i < n; i++) printf("h[%d] = %d\n", i, h[i]);
}
void compu_min(){
int i, _k = log((double)n) / log(2.0), k;
for(i = 0; i < n; i++) Min[0][i] = h[i];
for(k = 1; k <= _k; k++){
   for(i = 0; i + (1<<k) - 1 < n; i++){
    Min[k][i] = min(Min[k - 1][i], Min[k - 1][i + (1<<(k - 1))]);
   }
}
}
int check(int i, int j){
if(i > j) return 0;
int k = log((double)j - i + 1) / log(2.0);
return min(Min[k][i], Min[k][j + 1 - (1<<k)]);
}
void find_segs(){
int i, s = (n - 1) / 2, ii, len, ll, rr;
tot = 0;
for(i = 0; i < s; i++){ //奇区间
   ii = n - i - 1;
   ll = rank[i], rr = rank[ii];
   if(ll > rr) swap(ll, rr);
   len = check(ll + 1, rr);
   segs[tot].l = i - len + 1;
   segs[tot].r = i + len - 1;
   tot++;
}
for(i = 0; i < s - 1; i++){ //偶区间
   ii = n - i - 1;
   ll = rank[i + 1], rr = rank[ii];
   if(ll > rr) swap(ll, rr);
   len = check(ll + 1, rr);
   if(len > 0){
    segs[tot].l = i - len + 1;
    segs[tot].r = i + len;
    tot++;
   }
}
sort(segs, segs + tot, cmp2);
//for(i = 0; i < tot; i++) printf("(%d, %d)\n", segs[i].l, segs[i].r);
}
int Ans(){
int i, now = 0, k, ans = 0, s = (n - 1) / 2;
for(i = 0; i < tot; i++){
   k = i;
   while(i < tot && segs[i].l <= now){
    if(segs[i].r > segs[k].r) k = i;
    i++;
   }
   i--;
   ans++;
   now = segs[k].r + 1;
   if(now >= s) break;
}
return ans;
}
int main(){
int i, k;
//freopen("3296.in", "r", stdin);
while(scanf("%s", str) != EOF){
   n = strlen(str);
   str[n] = 'a' - 1;
   for(k = n + 1, i = n - 1; i >= 0; i--, k++) str[k] = str[i];
   str[k] = '\0';
   n = k;
   compu_sa();
   compu_h();
   compu_min();
   find_segs();
   printf("%d\n", Ans() - 1);
}
return 0;
}

