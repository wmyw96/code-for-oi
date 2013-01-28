the main part of dinic is wrong
why?
because we must augment several paths every time,but i only augment only one augment every time.so,it gets TLE at first

the changed main body of dinic

	int w=0;
	for (int k=c[i];k!=-1 && w<now;k=next[k]){
		int j=g[k],ret=min(flow[k],now-w);
		if (d[j]==d[i]+1 && flow[k])
		if ((ret=dfs(j,ret))){
			flow[k]-=ret;flow[k^1]+=ret;
			w+=ret;
		}
	}
	if (!w) d[i]=-1;
