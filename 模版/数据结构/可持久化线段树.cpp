#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=2e6+7;
struct SegmentTree
{
	int lson , rson;
	int cnt;
};SegmentTree trie[N*14];
int n , m , a[N] , total=0 , root[N];
int build(int l , int r)
{
	int p=++total;
	if(l==r)
	{
		trie[p].cnt=a[l];
		return p;
	}
	int mid=(l+r)>>1;
	trie[p].lson=build(l , mid);
	trie[p].rson=build(mid+1 , r);
	return p;
}
int change(int now , int l , int r , int pos , int x)
{
	int p=++total;
	if(l==r)
	{
		trie[p].cnt=x;
		return p;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
	{
		trie[p].rson=trie[now].rson;
		trie[p].lson=change(trie[now].lson , l , mid , pos , x);
	}else
	{
		trie[p].lson=trie[now].lson;
		trie[p].rson=change(trie[now].rson , mid+1 , r , pos , x);
	}
	return p;
}
int ans;
void ask(int now , int l , int r , int pos)
{
	if(l==r)
	{
		ans=trie[now].cnt;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) ask(trie[now].lson , l , mid , pos);
	else ask(trie[now].rson , mid+1 , r , pos);
}
signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    root[0]=build(1 , n);
    for(int i=1;i<=m;i++)
    {
		int vi , flag , pos , val;
		cin>>vi>>flag>>pos;
		if(flag==1) 
		{
			cin>>val;
			root[i]=change(root[vi] , 1 , n , pos , val);
		}else
		{
			root[i]=root[vi];
			ask(root[vi] , 1 , n , pos);
			cout<<ans<<endl;
		}
	}	
	return 0;
}
