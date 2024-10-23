#include<bits/stdc++.h>
#define endl '\n'
#define int long long
#define ff ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

using namespace std;

const int N=1e5+7;
int n , m;
int a[N];
struct SegmentTree
{
	int l , r , lazy , num;
};SegmentTree trie[N<<2];
void update(int p)
{
	trie[p].num=trie[p<<1].num+trie[p<<1|1].num;
}
void spread(int p)
{
	if(trie[p].lazy)
	{
		trie[p<<1].num+=(trie[p<<1].r-trie[p<<1].l+1)*trie[p].lazy;
		trie[p<<1|1].num+=(trie[p<<1|1].r-trie[p<<1|1].l+1)*trie[p].lazy;
		trie[p<<1].lazy+=trie[p].lazy;
		trie[p<<1|1].lazy+=trie[p].lazy;
		trie[p].lazy=0;
	}
}
void build(int p , int l , int r)
{
	trie[p].l=l , trie[p].r=r;
	if(l==r) 
	{
		trie[p].num=a[l];
		trie[p].lazy=0;
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1 , l , mid);
	build(p<<1|1 , mid+1 , r);
	update(p);
}
void modify(int p , int L , int R , int d)
{
	if(L<=trie[p].l&&trie[p].r<=R)
	{
		trie[p].num+=(trie[p].r-trie[p].l+1)*d;
		trie[p].lazy+=d;
		return;
	}
	spread(p);
	int mid=(trie[p].l+trie[p].r)>>1;
	if(L<=mid) modify(p<<1 , L , R , d);
	if(R>mid) modify(p<<1|1 , L , R , d);
	update(p);
}
int sum=0;
void ask(int p , int l , int r)
{
	if(l<=trie[p].l&&trie[p].r<=r)
	{
		sum+=trie[p].num;
		return;
	}
	spread(p);
	int mid=(trie[p].l+trie[p].r)>>1;
	if(l<=mid) ask(p<<1 , l , r);
	if(r>mid)ask(p<<1|1 , l , r);
	update(p);
}
signed main()
{
	int t;
	t=1;
//	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
		build(1 , 1 , n);
		for(int i=1;i<=m;i++) 
		{
			int op;
			cin>>op;
			if(op==1) 
			{
				int l , r , d;
				cin>>l>>r>>d;
				modify(1 , l , r , d);
			}
			else
			{
				int l , r ;
				cin>>l>>r;
				sum=0;
				ask(1 , l , r);
				cout<<sum<<endl;
			}
		}

	}
	return 0;
}

