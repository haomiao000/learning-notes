#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 5010, M = 20010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
int id[N], dcc_cnt;
bool is_bridge[M];//每条边是不是桥
int d[N];//度数

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void tarjan(int u, int from)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u;

    for (int i = h[u]; i!=-1; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])//j未遍历过
        {
            tarjan(j, i);//dfs(j)
            low[u] = min(low[u], low[j]);//用j更新u
            if (dfn[u] < low[j])//j到不了u
                // 则x-y的边为桥,
                //正向边is_bridge[i] 反向边is_bridge[i ^ 1]都是桥
                is_bridge[i] = is_bridge[i ^ 1] = true;
                // 这里i==idx 如果idx==奇数 则反向边=idx-1 = idx^1
                //            如果idx==偶数 则反向边=idx+1 = idx^1
        }
        // j遍历过 且i不是反向边(即i不是指向u的父节点的边)
        // 因为我们不能用u的父节点的时间戳更新u
        else if (i != (from ^ 1))
            low[u] = min(low[u], dfn[j]);
    }
    //双连通分量起点u  /
    //                u
    //               /
    //              ne1
    //             ne2 
    if (dfn[u] == low[u])
    {
        ++ dcc_cnt;
        int y;
        do {
            y = stk[top -- ];
            id[y] = dcc_cnt;
        } while (y != u);
    }
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    tarjan(1, -1);//防止搜反向边 用一个from

    for (int i = 0; i < idx; i ++ )
        //如果边i是桥 在其所连的出边的点j所在强连通分量的度+1
        // 桥两边的双连通分量各+1
        if (is_bridge[i])
            d[id[e[i]]] ++ ;

    int cnt = 0;
    for (int i = 1; i <= dcc_cnt; i ++ )
        if (d[i] == 1)//多少个度数为1的节点(强连通分量)
            cnt ++ ;//需要加的边的数量

    cout << (cnt + 1) / 2 << endl;

    return 0;
}