#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
#define ff ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const int N=2e5+7;
int n;
int fa[N];


void init()
{
	for(int i=1;i<N-5;i++) fa[i]=i;
}
int get(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=get(fa[x]);
}
void Merge(int x , int y)
{
	fa[get(x)]=get(y);
}
struct Edge
{
	int u , v , w;
	bool operator < (const Edge &b) const{
        return w < b.w;
    }
};
vector<Edge>edge;
signed main()
{
	// ff;
	int t;
	// cin>>t;
	t=1;
	while(t--)
	{
		int n , m;
		cin>>n>>m;
		for(int i=1;i<=m;i++)
		{
			int u , v , w;
			cin>>u>>v>>w;
			edge.push_back({u , v , w});
		}
		sort(edge.begin() , edge.end());
		init();	
		int ans=0;
		for(int i=0;i<m;i++)
		{
			if(get(edge[i].u)!=get(edge[i].v))
			{
				ans+=edge[i].w;
				Merge(edge[i].u , edge[i].v);
			}
		}
//		for(int i=0;i<m;i++) cout<<edge[i].u<<" "<<edge[i].v<<" "<<edge[i].w<<endl;
		bool flag=0;
		for(int i=2;i<=n;i++)
		{
			if(get(i)!=get(i-1)) flag=1; 
		}
		if(flag) cout<<"orz"<<endl;
		else cout<<ans<<endl;
	}

	return 0;
}