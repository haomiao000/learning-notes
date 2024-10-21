#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+7;
queue<int>q;
vector<int>vec[N];
int in[N];
signed main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int x;
        while(cin >> x) {
            if(x == 0) break;
            vec[i].push_back(x);
            in[x] += 1;
        }
    }
    for(int i=1;i<=n;i++) {
        if(in[i]==0) q.push(i);
    }
    vector<int>ans;
    while(!q.empty()) {
        int tmp = q.front();
        q.pop();
        ans.push_back(tmp);
        int sz = vec[tmp].size();
        for(int i = 0; i < sz; i++) {
            in[vec[tmp][i]] -= 1;
            if(in[vec[tmp][i]] == 0) {
                q.push(vec[tmp][i]);
            }
        }
    }
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }
    return 0;
}