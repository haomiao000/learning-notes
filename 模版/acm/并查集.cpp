#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7;
int fa[N];
int n;
void MemSet(int fa[])
{
	for(int i=1;i<=n;i++) fa[i]=i;
}
int get(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=get(fa[x]);
}
void Merge(int x , int y)
{
	fa[get(x)]=get(y);
}
signed main()
{
	
	
	return 0;
}