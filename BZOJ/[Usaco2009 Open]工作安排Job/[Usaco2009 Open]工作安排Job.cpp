/************************************************************** 
    Problem: 1572 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:300 ms 
    Memory:5160 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cmath> 
#include<cstring> 
#include<cstdlib> 
#include<algorithm> 
#include<queue> 
using namespace std; 
typedef long long LL; 
const int MAX_N=300001; 
struct data{ 
    int v,end; 
}; 
bool operator < (data x,data y){ 
    return x.v>y.v; 
} 
data d[MAX_N]; 
priority_queue<data> H; 
int cmp(data x,data y){ 
    return x.end<y.end; 
} 
int n,tn; 
LL ans; 
   
   
int main(){ 
    scanf("%d",&n); 
    for (int i=1;i<=n;i++){ 
        scanf("%d%d",&d[i].end,&d[i].v); 
    } 
    sort(d+1,d+1+n,cmp); 
    tn=0; 
    for (int i=1;i<=n;i++){ 
        if (d[i].end>=tn+1){ 
            ans=ans+d[i].v; 
            tn++; 
            H.push(d[i]); 
        } 
        else{ 
            data p=H.top(); 
            if (d[i].v>p.v){ 
                ans=ans+d[i].v-p.v; 
                H.pop(); 
                H.push(d[i]); 
            } 
        } 
    } 
    printf("%lld\n",ans); 
}

