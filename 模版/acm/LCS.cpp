#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1005;
int dp[N][N];
char s1[N];
char s2[N];
int vis[N][N];
int cnt = 0;
void LCS(int x, int y)
{
	if (x == 0 || y == 0)
	{
		return;
	}
	if (vis[x][y] == 1)
	{
		LCS(x - 1, y - 1);
		printf("%c", s1[x - 1]);
	}
	else if (vis[x][y] == 2)
	{
		LCS(x - 1, y);
	}
	else if (vis[x][y] == 3)
	{
		LCS(x, y - 1);
	}
}
int main()
{
	while (scanf("%s%s", s1, s2) != EOF)
	{
		cnt = 0;
		memset(vis, 0, sizeof(vis));
		memset(dp, 0, sizeof(dp));
		int lens1 = strlen(s1);
		int lens2 = strlen(s2);
		for (int i = 1; i <= lens1; i++)
		{
			for (int j = 1; j <= lens2; j++)
			{
				if (s1[i - 1] == s2[j - 1])
				{
					dp[i][j] = dp[i - 1][j - 1] + 1;
					vis[i][j] = 1;
				}
				else
				{
					if (dp[i - 1][j] > dp[i][j - 1])
					{
						dp[i][j] = dp[i - 1][j];
						vis[i][j] = 2;
					}
					else
					{
						dp[i][j] = dp[i][j - 1];
						vis[i][j] = 3;
					}
				}
			}
		}
		LCS(lens1, lens2);
		printf("\n");
	}
	return 0;
}