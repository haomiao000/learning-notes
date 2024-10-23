#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N=5e5+7;
struct SegemntTree
{
	int p , l , r;
	int num;
};SegemntTree trie[N<<2];
int a[N];
int n , m;
void build(int p , int l , int r)
{
	trie[p].l=l , trie[p].r=r;
	if(trie[p].l==trie[p].r)
	{
		trie[p].num=a[l];
		return;
	}
	int mid=(trie[p].l+trie[p].r)>>1;
	build(p<<1 , l , mid);
	build(p<<1|1 , mid+1 , r);
	trie[p].num=trie[p<<1].num+trie[p<<1|1].num;
}
//p<<1|1等价于p*2+1
void change(int p , int pos , int k)
{
	if(trie[p].l==trie[p].r)
	{
		trie[p].num+=k;
		return;
	}
	int mid=(trie[p].l+trie[p].r)>>1;
	if(pos<=mid) change(p<<1 , pos , k);
	else change(p<<1|1 , pos , k);
	trie[p].num=trie[p<<1].num+trie[p<<1|1].num;	
}
int sum=0;
void ask(int p , int L , int R)
{
	if(trie[p].l>=L&&trie[p].r<=R)
	{
		sum+=trie[p].num;
		return;
	}
	int mid=(trie[p].l+trie[p].r)>>1;
	if(L<=mid) ask(p<<1 , L , R);
	if(R>mid) ask(p<<1|1 , L , R);
}
signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	build(1 , 1 , n);
	for(int i=1;i<=m;i++)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int x , k;
			cin>>x>>k;
			change(1 , x , k);
		}
		else 
		{
			sum=0;
			int x , y;
			cin>>x>>y;
			ask(1 , x , y);
			cout<<sum<<endl;
		}
	}
	return 0;
}