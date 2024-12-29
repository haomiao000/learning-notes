#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N = 105;
const int M = 1e5 + 7;
int p[N];
int a[M];
void insert(int x)
{
	for (int i = 63; i >= 0; i--)
	{
		if (x & (1LL << i))
		{
			if (!p[i])
			{
				p[i] = x;
				return;
			}
			x ^= p[i];
		}
	}
}
int ans()
{
    int anss=0;
    for(int i=60;i>=0;i--)
    if((anss^p[i])>anss)anss^=p[i];
    return anss;
}   
signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
	{
		memset(p, 0, sizeof(p));
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
			insert(a[i]);
		}
		cout<<ans()<<endl;
	}
	return 0;
}