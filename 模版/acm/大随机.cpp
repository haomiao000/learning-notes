#include<bits/stdc++.h>
using namespace std;
using ULL = unsigned long long;
using LL = long long;

int main() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937_64 mt(seed);
    for (int i = 1; i <= 10; i++) {
            cout << mt() % (ULL)1e18 << '\n';
    }
    return 0;
}