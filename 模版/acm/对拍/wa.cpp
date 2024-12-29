#include <bits/stdc++.h>
#define cin fin
#define cout fout
#define int long long
using namespace std;
const int N = 505;
const int MINN = 0xc0c0c0c0c0c0c0c0;
const int MAXN = 0x3f3f3f3f3f3f3f3f;
#define file_in_out ifstream fin("in.txt");ofstream fout("wa.txt");
    
struct P {
    int num;
    int x, y;
    P(int a, int b, int c) {
        num = a, x = b, y = c;
    }
    bool operator<(const P b) const {
        return num < b.num;
    }
};

signed main() {
    file_in_out
    int n;
    cin >> n;

    int mp[N][N] = {0};
    int maxn_fu = MINN;
    int minn_zz = MAXN;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> mp[i][j];
            if (i == 1 || i == n || j == 1 || j == n) {
                if (mp[i][j] <= 0) {
                    maxn_fu = max(maxn_fu, mp[i][j]);
                }
                if (mp[i][j] >= 0) {
                    minn_zz = min(minn_zz, mp[i][j]);
                }
            }
        }
    }

    int aim_num = 0;
    if (minn_zz == MAXN && maxn_fu != MINN) {
        aim_num = maxn_fu;
    } else if (minn_zz != MAXN && maxn_fu == MINN) {
        aim_num = minn_zz;
    } else {
        aim_num = 0;
    }
    if(aim_num != 0 && n != 1) {
        cout << "NO" << endl;
        return 0;
    }
    vector<P> vec;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            vec.push_back(P(mp[i][j], i, j));
        }
    }

    int flag = 0;
    if (aim_num > 0) {
        sort(vec.begin(), vec.end());
        for (auto it : vec) {
            if (mp[it.x][it.y] == aim_num) continue;
            if (mp[it.x][it.y] > aim_num) {
                if (aim_num < mp[it.x - 1][it.y] || aim_num < mp[it.x + 1][it.y] ||
                    aim_num < mp[it.x][it.y - 1] || aim_num < mp[it.x][it.y + 1]) {
                    flag = 1;
                    break;
                } else
                    mp[it.x][it.y] = aim_num;
            }
        }
    } else if (aim_num < 0) {
        sort(vec.begin(), vec.end());
        reverse(vec.begin(), vec.end());
        for (auto it : vec) {
            if (mp[it.x][it.y] == aim_num) continue;
            if (mp[it.x][it.y] < aim_num) {
                if (aim_num > mp[it.x - 1][it.y] || aim_num > mp[it.x + 1][it.y] ||
                    aim_num > mp[it.x][it.y - 1] || aim_num > mp[it.x][it.y + 1]) {
                    flag = 1;
                    break;
                } else
                    mp[it.x][it.y] = aim_num;
            }
        }
    } else {
        sort(vec.begin(), vec.end());
        int pos = vec.size();
        for (int i = vec.size() - 1; i >= 0; i--) {
            if (mp[vec[i].x][vec[i].y] == aim_num) {
                pos = i;
                continue;
            }
            if (mp[vec[i].x][vec[i].y] <= 0) break;
            pos = i;
            if (mp[vec[i].x][vec[i].y] > aim_num) {
                if (aim_num < mp[vec[i].x - 1][vec[i].y] || aim_num < mp[vec[i].x + 1][vec[i].y] ||
                    aim_num < mp[vec[i].x][vec[i].y - 1] || aim_num < mp[vec[i].x][vec[i].y + 1]) {
                    flag = 1;
                    break;
                } else
                    mp[vec[i].x][vec[i].y] = aim_num;
            }
        }
        for (int i = pos - 1; i >= 0; i--) {
            if (mp[vec[i].x][vec[i].y] == aim_num) {
                continue;
            }
            if (mp[vec[i].x][vec[i].y] < aim_num) {
                if (aim_num > mp[vec[i].x - 1][vec[i].y] || aim_num > mp[vec[i].x + 1][vec[i].y] ||
                    aim_num > mp[vec[i].x][vec[i].y - 1] || aim_num > mp[vec[i].x][vec[i].y + 1]) {
                    flag = 1;
                    break;
                } else
                    mp[vec[i].x][vec[i].y] = aim_num;
            }
        }
    }

    if (flag)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
    fout.close();
    return 0;
}