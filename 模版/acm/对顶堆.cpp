#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int main()
{
    int t,n,m;
    cin>>t;
    while(t--)
    {
        priority_queue<int> q;//q为大根堆
        priority_queue<int,vector<int>,greater<int>> p;//p为小根堆
        cin>>n>>m;
        cout<<n<<' '<<(m+1)/2<<endl;
        int cnt=0;
        for(int i=1;i<=m;i++)
        {
            cin>>n;
            p.push(n);
            if(q.size()&&q.top()>p.top())
            {
               int a=p.top(),b=q.top();
               p.pop(),q.pop();
               p.push(b),q.push(a);
            }
            if(p.size()>q.size()+1)
            {
                q.push(p.top());
                p.pop();
            }
             if(i&1)//奇数
                printf("%d%c",p.top(),++cnt%10==0 ? '\n':' ');//每10个数换一行
        }
        if(cnt%10) cout<<endl;
    }
    return 0;
}
