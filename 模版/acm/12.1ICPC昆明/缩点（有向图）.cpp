#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10010, M = 50010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, Size[N];//每个强连通分的节点个数
int dout[N];

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void tarjan(int u)
{
    //u的时间戳
    dfn[u] = low[u] = ++timestamp;
    //把当前点加到栈中  当前点在栈中
    stk[++top] = u,in_stk[u] = true;

    for(int i=h[u];i!=-1;i=ne[i])
    {
        int j=e[i];
        if(!dfn[j])//j点未被遍历过
        {
            tarjan(j);//继续dfs 遍历j
            //j也许存在反向边到达比u还高的层,所以用j能到的最小dfn序(最高点)更新u能达到的(最小dfn序)最高点
            low[u] = min(low[u],low[j]);
        }
        //j点在栈中  说明还没出栈 是dfs序比当前点u小的
        //则其 1要么是横插边(左边分支的点)
        //         o
        //        / \
        //       j ← u    
        //     2要么是u的祖宗节点
        //         j
        //      ↗/ 
        //       u    
        //    两种情况u的dfs序都比j大 所以用dfn[j]更新low[u]
        else if(in_stk[j])
        {
            low[u] = min(low[u],dfn[j]);//直接用j的时间戳更新u
        }
        //栈代表当前未被搜完的强连通分量的所有点
    }
    // ⭐
    // 解释一下为什么tarjan完是逆dfs序
    // 假设这里是最高的根节点fa
    // 上面几行中 fa的儿子节点j都已经在它们的递归中走完了下面9行代码
    // 其中就包括 ++scc_cnt 
    // 即递归回溯到高层节点的时候 子节点的scc都求完了
    // 节点越高 scc_id越大
    // 在我们后面想求链路dp的时候又得从更高层往下
    // 所以得for(int i=scc_cnt(根节点所在的scc);i;i--)开始

    // 所以当遍历完u的所有能到的点后 发现u最高能到的点是自己
    // 1 则u为强连通分量中的最高点,则以u为起点往下把该强连通分量所有节点都找出来
    // 2 要么它就没有环,就是一个正常的往下的点
    if(dfn[u]==low[u])
    {
        int y;
        ++scc_cnt;//强连通分量总数+1
        do
        {
            y = stk[top--];//取栈顶元素y
            in_stk[y] = false;//则y不再在栈中
            id[y] = scc_cnt;
            Size[scc_cnt] ++;//第scc_cnt个连通块点数+1
        }while(y!=u);
        //1 因为栈中越高的元素的dfs序越大,那么我们只需要把dfs序比u大的这些pop到u
        //即因为最终会从下至上回到u 所以当y==u     
        //则说明点u所在的所有强连通分量都标记了id
        //           →  u
        //          /  /
        //         /  ne1
        //         ← ne2
        //      因为ne2会在u能到的dfs序里最大的,也就是此时的栈顶
        //      那么我们就逐一pop出ne2和ne1
        //2 要么它就是一个没有环的点 则该点单点成一个连通分量
    }
}

int main()
{
    cin >> n >> m;
    memset(h,-1,sizeof h);
    while(m--)
    {
        int a,b;
        cin >> a >> b;
        add(a,b);
    }

    for (int i = 1; i <= n; i ++ )
        if (!dfn[i])
            tarjan(i);
    //统计新图中点的出度 
    for (int i = 1;i <= n; i ++ )
        for (int j = h[i];j!=-1; j = ne[j])
        {
            int k = e[j];
            int a = id[i], b = id[k];//a,b不为一个连通分量
            if (a != b) dout[a] ++ ;//a出度+1  dout[a] += i→k
        }
    int zeros = 0, sum = 0;//sum 存的所有出度为0的强连通分量的点的数量
    for (int i = 1; i <= scc_cnt; i ++ )
        if (!dout[i])//如果第i个强连通分量出度==0
        {
            zeros ++ ;
            sum += Size[i];//则加上第i个强连通分量的点的个数
            if (zeros > 1)//如果有k>1个出度为0的 则会存在k-1头牛不被所有牛欢迎
            {
                sum = 0;
                break;
            }
        }

    cout << sum;
    return 0;
}