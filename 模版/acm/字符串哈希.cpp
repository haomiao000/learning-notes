#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
const ull mod=1e9+7;
const int N=1e4+5;
ull base=257;
char s[N];
ull Change[N];

int Hash(char s[]){
	int slen=strlen(s);
	ull ans=0;
	for(int i=1;i<=slen;i++){
		ans=(ans*base+s[i])%mod;
	}
	return ans;
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		scanf("%s",s);
		Change[i]=Hash(s);
	}
	sort(Change+1 , Change+t+1);
	int cnt=1;
	for(int i=1;i<t;i++){
		if(Change[i]!=Change[i+1]){
			cnt++;
		}
	}
	printf("%d\n",cnt);
	
	return 0;
}