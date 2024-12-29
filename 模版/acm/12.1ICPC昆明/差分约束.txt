/*
差分约束两大应用
应用一:
1 求不等式组的可行解
   ⭐源点需要满足的条件: 从源点出发,一定可以走到所有的边
   否则 用单源最短路做的话 有一条边走不到 则该边对应的不等式就无法满足
   某一个点x[i]走不到无所谓(某个点走不到代表它不受限制,x[i]取任意数都可以)
过程:
1 把每个x[i] ≤ x[j] + C[k]不等式转化为一条从x[j]走到x[i]长度为C[k]的边
2 然后在这个图上找一个超级源点,使得该源点一定可以遍历到所有边 
3 从源点求一遍 单源最短路
  3.1 假如存在负环
      x[1]→x[2]→x[3]→x[k]
        ↑ c1   c2   c3 ↓
          ← ← ← ← ← ← 
              ck
    x[2]≤ x[1]+c[1]
         ...
    x[k]≤ x[k-1]+c[k-1]
    x[1]≤ x[k]+c[k]
    对第一个不等式用后面的不等式一直做松弛
    x[2] ≤ x[1]+c[1]
         ≤ x[k]+c[k]+c[1]
         ≤ x[k-1]+c[k-1]+c[k]+c[1]
         ...
         ≤ x[2]+c[2]+...+c[k-1]+c[k]+c[1]
         ≤ x[2]+(小于零的Σc[i])
    x[2] < x[2]
    即矛盾
    得出结论:不等式无解 <=> 存在负环

4 求完单源最短路之后
4.1 存在负环 => 不等式无解
4.2 没有负环 => 求完之后一定是满足这个不等式的 <=> 即一个可行解

x[i] ≤ x[j] + C[k]
  x1 ≤ x2+1
{ x2 ≤ x3+2
  x3 ≤ x1-5
 x1 =  0
 x2 = -1
 x3 = -2

类比最短路
  i→j   求之前 d[j] > d[i]+c 
   c    求完后 d[j] ≤ d[i]+c 
一个图里每个点求完最短距离后每个点的最短距离都有第二个不等式满足
即  任何一个最短路问题 可以 转化为一个差分约束问题
同理  一个差分约束问题 可以 转化为一个单源最短路问题

最长路
   i→j   求之前 d[j] < d[i]+c 
   c     求完后 d[j] ≥ d[i]+c  

应用二:
2 如何求最大值或者最小值(x[i] for i in range(1,n))
    结论1:如果求的是最小值,则应该求最长路,如果求的是最大值,则应该求最短路
    问题1:如何转化x[i] ≤ c 其中c是一个常数 这类的不等式
    方法:建立一个超级源点,0号点x[0],然后建立0→i 长度是c的边即可
         x[i] ≤ c
            <=>
         x[i] ≤ x[0] + c = 0 + c   

    以求x[i]的最大值为例:所有从x[i]出发,构成的不等式链     
    x[i] ≤ x[j] + c[j] 
         ≤ x[k] + c[k] + c[j]
         ≤ x[0] + c[1]+ c[2]+... + c[j] 
         =   0  + c[1]+ ... + c[j] 
    所计算出的上界,
    最终x[i]的最大值
    =所有上界的最小值
    举例 x[i] ≤ 5
         x[i] ≤ 2
         x[i] ≤ 3
         max(x[i]) = min(5,2,3) = 2
    0 → 1 → 3 → 5 → ... → i
      c1  c3  c5       ci-1
    x[1] ≤ x[0] + c[1] 
    x[3] ≤ x[1] + c[3] 
    x[5] ≤ x[3] + c[5]
    ...
    x[i] ≤ x[i-1] + c[i-1]
    则
    x[i] ≤ x[i-1] + c[i] 
         ≤ x[i-3] + c[i-3] + c[i]
         ...
         ≤ x[0] + c[1] + c[3] + c[i-3] + c[i-1]
    ⭐可以发现Σc[i]就是从0→i的一条路径的长度

    那么
        求x[i]最大值
            <=>
        求所有上界的最小值
            <=>
        求所有从0→i的路径和的最小值
            <=>
        最短路求dist[i]

    同理 求x[i]最小值
            <=>
        求所有下界的最大值
            <=>
        求所有从0→i的路径和的最大值
            <=>
        最长路求dist[i]
*/
/*
本题
1 A = B  <=> A≥B B≥A
2 A < B  <=> B≥A+1
3 A≥B    <=> A≥B
4 A > B  <=> A≥B+1
5 B≥A    <=> B≥A
x≥1  
    } x≥x0+1(超级源点x0=0)
x0=1

举例  x[i] ≥ 5
      x[i] ≥ 2
      x[i] ≥ 3
      min(x[i]) = 5

总共最小值 = min(x[i]最小值) for i in range(n)
           = 求x[i]所有下界的最大值
           = 求所有从0→i的路径和的最大值
           = 最长路求dist[i]
0 → 1 → 3 → 5 → ... → i
c1  c3  c5       ci-1
    x[1] ≥ x[0] + c[1] 
    x[3] ≥ x[1] + c[3] 
    x[5] ≥ x[3] + c[5]
    ...
    x[i] ≥ x[i-1] + c[i-1]
    则
    x[i] ≥ x[i-1] + c[i] 
         ≥ x[i-3] + c[i-3] + c[i]
         ...
         ≥ x[0] + c[1] + c[3] + c[i-3] + c[i-1]
 ⭐可以发现Σc[i]就是从0→i的一条路径的长度

    那么 求x[i]最小值
            <=>
        求所有下界的最大值
            <=>
        求所有从0→i的路径和的最大值
            <=>
        最长路求dist[i]
    即：
    if(d[j]<d[i]+w[i][j])
        d[j] = d[i] + w[i][j]
        建立边数
        最坏情况A = B  <=> A≥B B≥A 2条
             +超级源点和所有点xi建边
             =3*n
*/
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

typedef long long LL;

const int N = 100010, M = 300010;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
LL dist[N];
int cnt[N];//统计到当前点总共有多少条边了
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx ++;
}

bool spfa()
{
    deque<int> q;
    q.push_back(0);
    st[0] = true;
    //最长路 dist[j] < dist[t] + w[i] 初始化为-INF
    memset(dist,-0x3f,sizeof dist);
    dist[0] = 0;//错因:在memset前初始化0

    while(q.size())
    {
        int t = q.back();
        q.pop_back();
        st[t] = false;//不在栈中 状态=false
        for (int i = h[t]; i!=-1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] < dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n + 1) return false;//有负环 无解
                if (!st[j])
                {
                    q.push_back(j);
                    st[j] = true;
                }
            }
        }
    }
    return true;
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int x, a, b;
        cin >> x >> a >> b;
        if (x == 1) add(b, a, 0), add(a, b, 0);//A=B
        else if (x == 2) add(a, b, 1);//B≥A+1
        else if (x == 3) add(b, a, 0);//A≥B
        else if (x == 4) add(b, a, 1);//A≥B+1
        else add(a, b, 0);//B≥A
    }
    //每个同学都要分到糖果 x[i]≥1
    //超级源点0 x[i] ≥ x[0]+1 <=> x[i] ≥ 1 
    for (int i = 1; i <= n; i ++ ) add(0, i, 1);

    if (!spfa()) cout << "-1" << endl;
    else
    {
        LL res = 0;
        for (int i = 1; i <= n; i ++ ) res += dist[i];
        cout << res << endl;
    }
    return 0;
}
