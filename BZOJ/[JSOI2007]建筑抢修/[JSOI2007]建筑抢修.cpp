/************************************************************** 
    Problem: 1029 
    User: wmyw96 
    Language: C++ 
    Result: Accepted 
    Time:392 ms 
    Memory:4392 kb 
****************************************************************/
  
#include<iostream> 
#include<cstdio> 
#include<cmath> 
#include<cstring> 
#include<cstdlib> 
#include<algorithm> 
#include<queue> 
using namespace std; 
const int MAX_N=300001; 
struct data{ 
    int t,end; 
}; 
bool operator < (data x,data y){ 
    return x.t<y.t; 
} 
data d[MAX_N]; 
priority_queue<data> H; 
int cmp(data x,data y){ 
    return x.end<y.end; 
} 
int n,tn,ans; 
  
  
int main(){ 
    scanf("%d",&n); 
    for (int i=1;i<=n;i++){ 
        scanf("%d%d",&d[i].t,&d[i].end); 
    } 
    sort(d+1,d+1+n,cmp); 
    tn=0; 
    for (int i=1;i<=n;i++){ 
        if (d[i].end>=tn+d[i].t){ 
            ans++; 
            tn+=d[i].t; 
            H.push(d[i]); 
        } 
        else{ 
            data p=H.top(); 
            if (d[i].t<p.t){ 
                tn+=d[i].t-p.t; 
                H.pop(); 
                H.push(d[i]); 
            } 
        } 
    } 
    /*for (;!H.empty();){ 
        printf("%d %d\n",H.top().t,H.top().end); 
        H.pop(); 
    }*/
    printf("%d\n",ans); 
    //system("pause"); 
}

