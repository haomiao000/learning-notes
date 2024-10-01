#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int maxn=1e6+5;
char s[maxn];
unsigned long long hs[maxn],p[maxn];
int main(){
    scanf("%s",s+1);
    int len=strlen(s+1);
    hs[0]=0;
    p[0]=1;
    for(int i=1;i<=len;i++){
        hs[i]=hs[i-1]*131+(s[i]);
        p[i]=p[i-1]*131;
    }
    int n;
    cin>>n;
    while(n--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        if(hs[b]-hs[a-1]*p[b-a+1]==hs[d]-hs[c-1]*p[d-c+1]){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
     return 0;
}