#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N = 2e5 + 7;
int n, m, s;
int dis[N], vis[N];
const int MAXN = 0x3f3f3f3f3f3f3f3f;
struct node {
	int dis;
	int pos;
};
//struct cmp1 {
//	bool operator ()(int &a, int &b) {
//		return dis[a] > dis[b];
//	}
//};
//priority_queue<int, vector<int>, cmp1> pr_que;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pr_que;
struct Edge {
	int v, w;
};
vector<Edge>vec[N];
void init() {
	for (int i = 1; i <= n; i++) dis[i] = MAXN;
}
void dijkstra() {
	dis[s] = 0;
	pr_que.push({0, s});
	while (!pr_que.empty()) {
		int now = pr_que.top().second;
		pr_que.pop();
		if (vis[now]) continue;
		vis[now] = 1;
		int sz = vec[now].size();
		for (int i = 0; i < sz; i++) {
			if(dis[now] + vec[now][i].w < dis[vec[now][i].v]) {
				dis[vec[now][i].v] = min(dis[vec[now][i].v], dis[now] + vec[now][i].w);
				pr_que.push({dis[vec[now][i].v],vec[now][i].v});
			}
		}
	}
}
signed main() {
	cin >> n >> m >> s;
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		vec[u].push_back({v, w});
	}
	init();
	dijkstra();
	for (int i = 1; i <= n; i++) cout << dis[i] << " ";
	cout << endl;
	return 0;
}
