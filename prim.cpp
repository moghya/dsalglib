#include<bits/stdc++.h>
using namespace std;

const int N = int(1e5)+10;

vector<int> G[N],W[N];
int vis[N];

//int swap(int x, int y);
//int swap(int* x, int * y);
//int swap(int &x, int &y);

int main()
{
	int n,m; scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++)
	{
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		G[u].push_back(v);
		G[v].push_back(u);
		W[u].push_back(w);
		W[v].push_back(w);
	}
	set< pair<int,pair<int,int> > > S;
	vis[1] = 1;
	for(int i=0; i<G[1].size(); i++)
		S.insert(make_pair(W[1][i],make_pair(1,G[1][i])));
	int cnt=1;
	int ans=0;
	while(cnt < n)
	{
		pair<int,pair<int,int> > edge = *S.begin();
		S.erase(edge);
		int w = edge.first;
		int u = edge.second.first;
		int v = edge.second.second;

		if(vis[u] && vis[v]) continue;
		ans += w;
		if(vis[v]) swap(u,v);
		for(int i=0; i<G[v].size(); i++)
		{
			if(vis[G[v][i]]) continue;
			S.insert(make_pair(W[v][i],make_pair(v,G[v][i])));
		}
		vis[v] = 1;
	}
	printf("%d\n",ans);

















}
