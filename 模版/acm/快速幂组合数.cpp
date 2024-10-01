const int mod = 998244353;
int powmod(int a, int b)
{
	int ans = 1;
	while (b > 0)
	{
		if (b & 1)ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}
int n, m;
int C(int n, int m)
{
	if (m > n) return 0;
	int ans = 1;
	for (int i = 1; i <= m; i++)
	{
		int a = (n + i - m) % mod;
		int b = i % mod;
		ans = ans * (a * powmod(b, mod - 2) % mod) % mod;
	}
	return ans;
}
int Lucas(int n, int m)
{
	if (m == 0) return 1;
	return C(n % mod, m % mod) * Lucas(n / mod, m / mod) % mod;
}