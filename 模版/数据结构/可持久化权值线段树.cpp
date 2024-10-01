#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=2e6+7;
struct SegmentTree
{
	int lson , rson;
	int cnt;
};SegmentTree trie[N*4+N*10];
int root[N] , n , m , a[N] , b[N] , c[N] , total=0 , after_n=0;
void discreate()
{
	sort(a+1 , a+n+1);
	for(int i=1;i<=n;i++)
	{
		if(i==1||a[i]!=a[i-1]) b[++after_n]=a[i];
	}
}
int query(int x) {return lower_bound(b+1 , b+after_n+1 , x)-b;}
int build(int l , int r)
{
	int p=++total;
	if(l==r) return p;
	int mid=(l+r)>>1;
	trie[p].lson=build(l , mid);
	trie[p].rson=build(mid+1 , r);
	trie[p].cnt=trie[trie[p].lson].cnt+trie[trie[p].rson].cnt;
	return p;
}
int add(int now , int l , int r , int pos)
{
	int p=++total;
	if(l==r) 
	{
		trie[p].cnt=trie[now].cnt+1;
		return p;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
	{
		trie[p].rson=trie[now].rson;
		trie[p].lson=add(trie[now].lson , l , mid , pos);
	}else
	{
		trie[p].lson=trie[now].lson;
		trie[p].rson=add(trie[now].rson , mid+1 , r , pos);
	}
	trie[p].cnt=trie[trie[p].lson].cnt+trie[trie[p].rson].cnt;
	return p;
}
int ans=0;
void ask(int p , int q , int l , int r , int k)
{
	if(l==r)
	{
		ans=b[l];
		return;
	}
	int mid=(l+r)>>1;
	int lcnt=trie[trie[p].lson].cnt-trie[trie[q].lson].cnt;
	if(lcnt>=k) 
	    ask(trie[p].lson , trie[q].lson , l , mid , k);
	else
	    ask(trie[p].rson , trie[q].rson , mid+1 , r , k-lcnt);
}
signed main()
{
    cin>>n>>m;
	for(int i=1;i<=n;i++) 
	{
		cin>>a[i];
		c[i]=a[i];
	}
	discreate();
	root[0]=build(1 , after_n);
	for(int i=1;i<=n;i++) root[i]=add(root[i-1] , 1 , after_n , query(c[i]));
	for(int i=1;i<=m;i++)
	{
 		int l , r , k;
		cin>>l>>r>>k;
		ans=0;
		ask(root[r] , root[l-1] , 1 , after_n , k);
		cout<<ans<<endl;
	}		
	return 0;
}