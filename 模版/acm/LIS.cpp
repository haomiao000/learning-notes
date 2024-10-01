#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1005;
char a[N],b[N];
int dp[N][N];
int main()
{
    int n;
 
    while(scanf("%d",&n)!=EOF)
    {   
    memset(a , 0 , sizeof(a));
    memset(b , 0 , sizeof(b));
    
	for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
			b[i]=a[i];
		}
        memset(dp,0,sizeof(dp));

        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(a[i-1]<b[j-1])
                {
                    dp[i][j]=dp[i-1][j-1]+1;
                }
                else
                {
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        printf("%d\n",dp[n][n]);
    }
    return 0;
}