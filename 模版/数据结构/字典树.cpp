#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=5e6+7;
struct Dic_Tree
{
	int son[26];
	int tag;
	int num;
};Dic_Tree trie[N];
int total=0;
void build(string s)
{
	int p=0;
	int slen=s.length();
	for(int i=0;i<slen;i++)
	{
		if(trie[p].son[s[i]-'a'])
		{
			p=trie[p].son[s[i]-'a'];
		}else
		{
			trie[p].son[s[i]-'a']=++total;
			p=trie[p].son[s[i]-'a'];
		}
		if(i==slen-1)
		{
			trie[p].tag=1;
		}
	}
}
int ask(string s)
{
	int p=0;
	int slen=s.length();
	for(int i=0;i<slen;i++)
	{
		if(trie[p].son[s[i]-'a'])
		{
			p=trie[p].son[s[i]-'a'];
			if(i==slen-1&&trie[p].tag==0) return 0;
			else if(i==slen-1&&trie[p].tag==1)
			{
				trie[p].num++;
				if(trie[p].num==1) return 1;
				else if(trie[p].num>1) return 2;
			}
		}else return 0;
	}
}
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) 
	{
		string s;
		cin>>s;
		build(s);
	}
	int m;
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		string ss;
		cin>>ss;
		if(ask(ss)==1) cout<<"OK"<<endl;
		else if(ask(ss)==2) cout<<"REPEAT"<<endl;
		else cout<<"WRONG"<<endl;
	}
	return 0;
}