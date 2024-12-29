#include<bits/stdc++.h>
using namespace std;
using ULL = unsigned long long;
using LL = long long;

int main() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937_64 mt(seed);
    // cout << mt() % (ULL)1e18 << '\n';
    int n = mt()%10000 + 1;
    cout << n << endl;
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= n; j ++) {
            int tmp = mt() % 4;
            int fu = mt() % 2;
            if(fu) cout << tmp << " ";
            else cout << -tmp << " ";
        }
        cout << endl;
    }
    return 0;
}