#include<bits/stdc++.h>
#define endl '\n'
#define int long long
#define ff ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

using namespace std;

const int N=2e5+7 , M=18;
int n , m;
int a[N];
int f[N][M];
void init()
{
	for(int j=0;j<M;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			if(!j) f[i][j]=a[i];
			else f[i][j]=max(f[i][j-1] , f[i+(1<<j-1)][j-1]);
}
int query(int l , int r)
{
	int len=r-l+1;
	int k=log(len)/log(2);
	return max(f[l][k] , f[r-(1<<k)+1][k]);
}
signed main()
{
	int t;
	t=1;
//	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		init();
		cin>>m;
		while(m--)
		{
			int l , r;
			cin>>l>>r;
			cout<<query(l , r)<<endl;
		}
	}
	return 0;
}
