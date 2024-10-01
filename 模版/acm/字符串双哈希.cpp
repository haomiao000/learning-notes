#include<bits/stdc++.h>
#define int unsigned long long
#define endl '\n'

using namespace std;
typedef unsigned long long ull;
const int N = 10010;
const int base1 = 257, base2 = 131;
const ull mod1 = 1e9 + 7, mod2 = 998244353;
char s[N];
int Change1[N];
int Change2[N];
int Hash(char s[], int mod, int base)
{
	int slen = strlen(s);
	int ans = 0;
	for (int i = 0; i < slen; i++)
	{
		ans = (ans * base + s[i]) % mod;
	}
	return ans;
}
signed main()
{
	int t;
	map<ull, ull>mp1;
	map<ull, ull>mp2;
	scanf("%d", &t);
	int cnt = 0;
	int dnt = 0;
	for (int i = 1; i <= t; i++)
	{
		scanf("%s", s);
		mp1[Hash(s, mod1, base1)]++;
		if (mp1[Hash(s, mod1, base1)] == 1) cnt++;
		mp2[Hash(s, mod2, base2)]++;
		if (mp2[Hash(s, mod2, base2)] == 1) dnt++;
	}
	if (cnt == dnt) printf("%d\n", cnt);
	else if (cnt != dnt) printf("%d\n", min(cnt, dnt));
	return 0;
}