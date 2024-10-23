#include<bits/stdc++.h>
#define ll long long
#define lowbit(a) ((a)&-(a))
using namespace std;
const int N=1e6+7;
ll c[N];
void update(ll x , ll y , ll w){
	for(ll i=x;i<=w;i+=lowbit(i)){
		c[i]+=y;
	}
}
ll getsum(ll x){
	ll ans=0;
	for(ll i=x;i>0;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
int main()
{
    ll n , q;
    scanf("%lld%lld",&n,&q);
    for(ll i=1;i<=n;i++){
		ll cnt;
		scanf("%lld",&cnt);
		update(i , cnt , n);
	}
	while(q--){
	ll flag;
	scanf("%lld",&flag);
	if(flag==1){
		ll m ,q;
		scanf("%lld%lld",&m,&q);
		update(m , q , n);
	}
	else if(flag==2){
		ll l , r;
		scanf("%lld%lld",&l,&r);
		printf("%lld\n",getsum(r)-getsum(l-1));
	}
}
	
	return 0;
}