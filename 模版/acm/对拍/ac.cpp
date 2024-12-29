//#include <bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <deque>
#include <queue>
#include <cmath>
#include <stack>
#include <map>
#include <set>
#include <random>
#include <time.h>
#include <unordered_map>
#include <unordered_set>
//#include <cassert>

#define bug(x) cout << #x << " = " << x << '\n';

using namespace std;
#define ll long long
#define dd double
#define endl '\n'
#define pll pair<ll,ll>
#define unmap unordered_map

/*
 算法:
    贪心 模拟 二分 倍增
    分块 莫队 分治
    dp (背包 树形 块压)
    前缀和 差分 并查集
    lct 最短路径 cdq

    字符串哈希 字典树

    线性基 分层图
    AC自动机 二分图

数据结构:
    优先队列 单调队列 堆
    双端队列(滑动窗口)
    线段树 树链剖分

数论:
    容斥定理 质数塞 鸽巢原理
    几何点积叉积
    exgcd

待学习:
    模拟退火 网络流 马拉车 后缀数组 后缀自动机 莫反
    杜教筛

maybe:
    kmp

减少允许时间的方法：
    降低复杂度
    O2，O3
    数组模拟 STL
    long long -> (unsigned) int
    减少数组大小
    inline
*/

inline ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

inline bool read(ll& x) {
    x = 0;
    char c = getchar();
    if (c == EOF)return false;
    else if (c == '}')return 0;
    while (c > '9' || c < '0')c = getchar();
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return true;
}

template<class T>void unwrite(T x) {
    if (x > 9) unwrite(x / 10);
    putchar(x % 10 + '0');
}

template<class T>inline void write(T x) {
    x < 0 ? putchar('-'), unwrite(0 - x) : unwrite(x);
}

template<class T>inline void write(T x, char&& c) {
    x < 0 ? putchar('-'), unwrite(0 - x) : unwrite(x);
    putchar(c);
}

inline ll max(ll a, ll b) {
    return a > b ? a : b;
}

inline ll min(ll a, ll b) {
    return a < b ? a : b;
}


ll pow(ll di, ll zhi, ll mod) {
    ll ans = 1;

    for (di %= mod; zhi != 0; zhi >>= 1) {
        if (zhi & 1)ans = ans * di % mod;
        di = di * di % mod;
    }
    return ans;
}

ll gcd(ll a, ll b) {
    if (a < b)swap(a, b);

    for (ll c = 0; b != 0; b = c % b)c = a, a = b;

    return a;
}

inline ll lcm(ll a, ll b) {
    return a && b ? a / gcd(a, b) * b : a * b;
}

// a * x + b * y = gcd(a, b)
ll Exgcd(ll a, ll b, ll& x, ll& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = Exgcd(b, a % b, x, y), t = x;
    x = y;
    y = t - (a / b) * y;
    return d;
}

// 数论分块 O(n ** 0.5)
// sum(F[i]*(n/i)) for i in range(1, n)
ll Math_Block(ll n) {
    // 储存结果
    long long res = 0;

    // 块左端点与右端点
    ll l = 1, r = 0;
    while (l <= n) {
        // 计算当前块的右端点
        r = n / (n / l);

        // (r - l + 1) -> F[r] - F[l - 1] 对于前缀和适用的函数适用
        res += (r - l + 1) * (n / l);
        l = r + 1;  // 左端点移到下一块
    }
    return res;
}

// 欧拉函数 负数无定义 O(n ** 0.5)
// 表示[0, n] 中有多少个数与n互质 用欧拉塞可以求多个
ll Oula(ll n) {
    ll ans = n;
    for (ll i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            ans = ans / i * (i - 1);

            do n /= i; while (n % i == 0);
        }

    return n > 1 ? ans / n * (n - 1) : ans;
}

// 利用欧拉定理扩展快速幂
ll pow(ll di, string zhi, ll mod) {
    // zhi <  Oula(mod): ans = a ** b % mod
    // zhi >= Oula(mod): ans = a ** (b % Oula(mod) + Oula(mod)) % mod

    ll oula = Oula(mod), flag = 0;

    for (auto& x : zhi) {
        flag = flag * 10 + x - '0';
        if (flag >= oula)break;
    }

    if (flag >= oula) {
        flag = 0;
        for (auto& x : zhi)flag = (flag * 10 + x - '0') % oula;

        return pow(di, flag + oula, mod);
    }
    else return pow(di, flag, mod);
}

struct ooo {
    bool operator()(pll a, pll b) {
        return a.first < b.first;
    }
};
//priority_queue<pll, vector<pll>, ooo> da;

struct oooo {
    bool operator()(pll a, pll b) {
        return a.second == b.second ? a.first > b.first:a.second > b.second;
    }
};
//priority_queue<pll, vector<pll>, oooo> xiao;    //按第二个排序

struct ooooo {
    bool operator()(pll a, pll b) {
        return a.second == b.second ? a.first < b.first : a.second < b.second;
    }
};
//priority_queue<pll, vector<pll>, ooooo> da;    //按第二个排序

//priority_queue<ll, vector<ll>, greater<ll>> xiao;
//priority_queue<ll> da;

// -----------------------------------------------------------------------------------------
// 常数区
// 998244353 1000000007
// 6048819564847853 9587869125711931 9587869125711953
const ll mod = 998244353, N = 2e6 + 8, inf = 3e18;

//求逆元
inline ll ni(ll a) {
    return pow(a, mod - 2, mod);
}

// 扩展欧几里得算法 求直线下点数
struct __data {
    __data() { f = g = h = 0; }

    ll f, g, h;
    // f:   sum( (a*i+b)//c     for i in range(0, n))
    // g:   sum( (a*i+b)//c*i   for i in range(0, n))
    // h:   sum(((a*i+b)//c)**2 for i in range(0, n))
};

// bsgs O(sqrt(q)*log(q)) 质数p
// (a**x - b)%p == 0
ll BSGS(ll a, ll b, ll p) {
    map<ll, ll> hash; hash.clear();//建立一个Hash表
    b %= p;
    ll t = sqrt(p) + 1;
    for (ll i = 0; i < t; ++i)hash[b * pow(a, i, p) % p] = i;//将每个j对应的值插入Hash表
    a = pow(a, t, p);
    if (!a) return b == 0 ? 1 : -1;//特判
    for (ll i = 1; i <= t; ++i) {//在Hash表中查找是否有i对应的j值
        ll val = pow(a, i, p);
        ll j = hash.find(val) == hash.end() ? -1 : hash[val];
        if (j >= 0 && i * t - j >= 0) return i * t - j;
    }
    return -1;//无解返回-1
}

// 最后一项可以不是质数
ll ex_BSGS(ll A, ll B, ll C) {
    map<ll, ll>mp;
    if (B == 1)return 0;

    ll k = 0, tmp = 1, d = 0;
    while (1) {
        d = gcd(A, C);
        if (d == 1)break;
        if (B % d)return -1;
        B /= d, C /= d;
        tmp = tmp * (A / d) % C;
        ++k;
        if (tmp == B)return k;
    }

    mp.clear();
    ll mul = B;
    mp[B] = 0;
    ll m = ceil(sqrt(1.0 * C + 0.00001));

    for (ll j = 1; j <= m; ++j) {
        mul = mul * A % C;
        mp[mul] = j;
    }

    int am = pow(A, m, C);
    mul = tmp;
    for (ll j = 1; j <= m; ++j) {
        mul = mul * am % C;
        if (mp.count(mul))return j * m - mp[mul] + k;
    }

    return -1;
}

//ll i2 = ni(2), i6 = ni(6);
//
//__data Euclid(ll n, ll a, ll b, ll c) {
//    ll ac = a / c, bc = b / c, m = (a * n + b) / c, n1 = n + 1, n21 = n * 2 + 1;
//    __data d;
//
//    if (a == 0) {  // 迭代到最底层
//        d.f = bc * n1 % mod;
//        d.g = bc * n % mod * n1 % mod * i2 % mod;
//        d.h = bc * bc % mod * n1 % mod;
//        return d;
//    }
//    if (a >= c || b >= c) {  // 取模
//        d.f = n * n1 % mod * i2 % mod * ac % mod + bc * n1 % mod;
//        d.g = ac * n % mod * n1 % mod * n21 % mod * i6 % mod + bc * n % mod * n1 % mod * i2 % mod;
//        d.h = ac * ac % mod * n % mod * n1 % mod * n21 % mod * i6 % mod +
//            bc * bc % mod * n1 % mod + ac * bc % mod * n % mod * n1 % mod;
//        d.f %= mod, d.g %= mod, d.h %= mod;
//
//        __data e = Euclid(n, a % c, b % c, c);  // 迭代
//
//        d.h += e.h + 2 * bc % mod * e.f % mod + 2 * ac % mod * e.g % mod;
//        d.g += e.g, d.f += e.f;
//        d.f %= mod, d.g %= mod, d.h %= mod;
//        return d;
//    }
//    __data e = Euclid(m - 1, c, c - b - 1, a);
//    d.f = n * m % mod - e.f, d.f = (d.f % mod + mod) % mod;
//    d.g = m * n % mod * n1 % mod - e.h - e.f, d.g = (d.g * i2 % mod + mod) % mod;
//    d.h = n * m % mod * (m + 1) % mod - 2 * e.g - 2 * e.f - d.f;
//    d.h = (d.h % mod + mod) % mod;
//    return d;
//}

//const ll prime_num = 5e6;
//int prime[prime_num]{ 1, 2 };
//int visit[prime_num];
//void Prime() {
//    for (ll i = 3; i < prime_num; ++++i) {
//        //cout << " i = " << i << endl;
//        //纪录素数， 这个prime[0] 相当于 cnt，用来计数
//        if (!visit[i]) prime[++prime[0]] = i;
//
//        for (int j = 2; j <= prime[0] && i * prime[j] < prime_num; j++) {
//            visit[i * prime[j]] = 1;
//            if (i % prime[j] == 0) break;
//        }
//    }
//
//    //for (ll i = 0; i < prime[0]; ++i)cout << prime[i] << endl;
//    //bug(prime[0]);
//}

/*

*/

#define lson  k << 1
#define rson  k << 1 | 1

ll n, m, h, x, y, z, a, b, c, d, e, u, v, w, i, j, k, l, r, nn, mm, ans, p, q, len, llen, T, he;
ll wcnm = 1, id = 0;

string s, t;
//priority_queue<pll, vector<pll>, oooo> xiao;    //按第二个排序
//priority_queue<pll, vector<pll>, ooooo> da;     //按第二个排序
#include <fstream>
string get_num(ll num) {
    vector<char>A;
    while (num) {
        A.push_back(num % 10 + '0');
        num /= 10;
    }
    string ans = "";
    while (A.size())ans += A.back(), A.pop_back();
    return ans;
}

ll A[1003][1003];

ll solve(ifstream& infile, ofstream& outfile) {
    //auto&  = infile; auto& cout = outfile;
    ifstream fin("in.txt");  // 创建文件输入流
    ofstream fout("ac.txt"); // 创建文件输出流
    fin >> n;

    for (i = 1; i <= n; ++i)for (j = 1; j <= n; ++j)fin >> A[i][j];

    for (i = 1; i <= n; ++i)for (j = 1; j <= n; ++j)if (A[i][j] * A[i][j - 1] > 0 || A[i][j] * A[i - 1][j] > 0)ans = 1;

    if (ans==0)fout << "YES\n";
    else fout << "NO\n";
    fout.close();
    return 0;
}

int main() {
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // srand(time(0));
    // mt19937_64 rgn(time(0));
    
    // 以读模式打开文件
    for (ll num = 1; num <= 1; ++num) {
        //bug(num);
        ifstream infile;
        ofstream outfile;
        //infile.open(filename + get_num(num) + ".in");
        //outfile.open(filename + get_num(num) + ".out");

        solve(infile, outfile);
        //outfile << ans << endl;
        //cout << ans << endl;
    }
}


inline void out2(double ans) {
    printf("%.2lf", ans);
}

/*


*/