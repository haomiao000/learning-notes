
#define Fill(a , b) memset(a , b , sizeof(a));
using  namespace std;
const int maxn = 1e5 + 5;
int up[maxn][23], maxx[maxn][23];
int dep[maxn], dis[maxn];
int cnt, head[maxn];
int n, m, q;
struct node {
    int to, next, w;
}e[maxn<<1];
void init() {	
    Fill(head,-1); Fill(dis,0);
    Fill(up,0); Fill(dep,0);
    cnt = 0; Fill(maxx, 0);
}
void add(int u, int v, int w) {
    e[cnt] = node{v, head[u], w};
    head[u] = cnt++;
}
void dfs(int u,int fa,int d) {
    dep[u] = d + 1;
    for(int i = 1 ; i < 20 ; i ++) {
        up[u][i] = up[up[u][i-1]][i-1];
       // maxx[u][i] = max(maxx[up[u][i-1]][i-1], maxx[u][i-1]);
    }
    for(int i = head[u] ; ~i ; i = e[i].next) {
        int to = e[i].to;
        if(to == fa) continue;
        dis[to] = dis[u] + e[i].w;
        up[to][0] = u;
       // maxx[to][0] = e[i].w;
        dfs(to, u, d+1);
    }
}
int LCA_BZ(int u,int v) {
    int mx = 0;
    if(dep[u] < dep[v]) swap(u,v);
    int k = dep[u] - dep[v];
    for(int i = 19 ; i >= 0 ; i --) {
        if((1<<i) & k) {
        //  mx = max(mx, maxx[u][i]);
            u = up[u][i];
        }
    }
    if(u == v) return u;
    for(int i = 19 ; i >= 0 ; i --) {
        if(up[u][i] != up[v][i]){
        //  mx = max(mx, maxx[u][i]);
        //  mx = max(mx, maxx[v][i]);
            u = up[u][i];
            v = up[v][i];
        }
    }
//     return max(mx, max(maxx[u][0], maxx[v][0]));
    return up[u][0];
}
int kth(int u, int v, int k) {  // 算u到v的路径的第k个结点.
    --k; int f = LCA_BZ(u, v);
    if (dep[u] - dep[f] < k) {
        k = dep[v] - dep[f] - k + dep[u] - dep[f];
        swap(u, v);
    }
    for (int i = 19 ; i >= 0 ; i --) {
        if (k & (1 << i)) u = up[u][i];
    }
    return u;
}
void solve() {
    scanf("%d%d",&n,&m);
    init();
    for(int i = 1 ; i < n ; i ++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    //maxx[1][0] = 0;
    dfs(1, -1, 0);
    while(m--) {
        int u, v;
        scanf("%d%d",&u, &v);
        int res = dis[u] + dis[v] - 2 * dis[LCA_BZ(u,v)];
        printf("%d\n", res);
    }
}