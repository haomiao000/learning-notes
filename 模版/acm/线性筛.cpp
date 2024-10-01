#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define N 1001000
#define LL long long
using namespace std;
int v[N];
int prime[N];

int num[N], prim[N];
int pn = 0;
void table()
{
	memset(num, -1, sizeof(num));
	for (int i = 2; i < N; i++)
	{
		if (num[i]) prim[pn++] = i;
		for (int j = 0; j < pn && i * prim[j] < N; j++)
		{
			num[i * prim[j]] = 0;
			if (i % prim[j] == 0) break;
		}
	}
}
int ask[N];
signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	table();
	cout << 1 << endl;
	for (int i = 0; i < pn; i++)
	{
		if (i <= 1e3)
		{
			ask[prim[i]*prim[i]]--;
		}
		ask[prim[i]]++;
	}
	for (int i = 2; i <= 1e6; i++)
	{
		ask[i] += ask[i - 1];
	}
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		cout << ask[n] << endl;
	}


	return 0;
}