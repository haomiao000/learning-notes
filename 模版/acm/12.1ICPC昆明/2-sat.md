	##  2-sat

	每个人两个条件，需要至少满足一个

	假如一个人的条件是 a和b，建边 !a->b和!b->a，即若a假则b必真，若b假则a必真

	![image-20231121090155002](C:\Users\yqlm\AppData\Roaming\Typora\typora-user-images\image-20231121090155002.png)

	建边规则：

	* 若 x满足A，则y满足B

	* * 建边xA->yB,!yB->!yA

	* x满足A和y满足B至少满足一个
	* * 建边 !xA->yB,!yB->xA

	* xA一定满足
	* * 建边!xA->xA

	# P4782 【模板】2-SAT

	## 题目描述

	有 $n$ 个布尔变量 $x_1$$\sim$$x_n$，另有 $m$ 个需要满足的条件，每个条件的形式都是 「$x_i$ 为 `true` / `false` 或 $x_j$ 为 `true` / `false`」。比如 「$x_1$ 为真或 $x_3$ 为假」、「$x_7$ 为假或 $x_2$ 为假」。

	2-SAT 问题的目标是给每个变量赋值使得所有条件得到满足。

	## 输入格式

	第一行两个整数 $n$ 和 $m$，意义如题面所述。

	接下来 $m$ 行每行 $4$ 个整数 $i$, $a$, $j$, $b$，表示 「$x_i$ 为 $a$ 或 $x_j$ 为 $b$」($a, b\in \{0,1\}$)

	## 输出格式

	如无解，输出 `IMPOSSIBLE`；否则输出 `POSSIBLE`。

	下一行 $n$ 个整数 $x_1\sim x_n$（$x_i\in\{0,1\}$），表示构造出的解。

	## 样例 #1

	### 样例输入 #1

	```
	3 1
	1 1 3 0
	```

	### 样例输出 #1

	```
	POSSIBLE
	0 0 0
	```

	## 提示

	$1\leq n, m\leq 10^6$ , 前 $3$ 个点卡小错误，后面 $5$ 个点卡效率。

	由于数据随机生成，可能会含有（ 10 0 10 0）之类的坑，但按照最常规写法的写的标程没有出错，各个数据点卡什么的提示在标程里。

	~~~ c++
	#include<bits/stdc++.h>
	using namespace std;
	#define int long long
	//author:lijingyanglipu
	// 2-sat所有数组需要开2倍空间 
	int T;
	vector<int>p[2000005];
	int tim=0;
	int low[2000005],dfn[2000005];
	int s=0;
	int n,m;
	int sta[2000005];
	bool vis[2000005];
	int lipu[2000005];
	int top;
	void ljylp(int k){
		low[k]=dfn[k]=++tim;
		sta[++top]=k;
		vis[k]=1;
		for(int i=0;i<p[k].size();i++){
			if(!dfn[p[k][i]]){
				ljylp(p[k][i]);
				low[k]=min(low[k],low[p[k][i]]);
			} 
			else if(vis[p[k][i]]){
				low[k]=min(low[k],dfn[p[k][i]]);
			}
		}
		if(low[k]==dfn[k]){
			//cout<<s<<" "<<k<<endl;
			++s;
			while(sta[top]!=k){
				lipu[sta[top]]=s;
				vis[sta[top]]=0;
				top--;
			}
			lipu[k]=s;
			top--;
			vis[k]=0;
		}
	} 	
	void lijingyanglipu(){//多组数据需清空 
			tim=0;
			s=0;
			top=0;
		for(int i=1;i<=2*n;i++){
			p[i].clear();
			dfn[i]=low[i]=0;
			vis[i]=0;
		}
	}
	int lljy(int k,int w){//取当前的节点，比如x的否定返回x+n,x的肯定返回x 
		if(w)return k;
		return k+n;
	}
	int ljy(int k,int w){//取非，比如x的否定的非返回x,x的肯定的非返回x+n 
		if(w)return k+n;
		return k;
	}
	void solve(){
	cin>>n>>m;
	int t1,t2,t3,t4;
	for(int i=1;i<=m;i++){
		scanf("%lld %lld %lld %lld",&t1,&t2,&t3,&t4);
		p[ljy(t1,t2)].push_back(lljy(t3,t4));
		p[ljy(t3,t4)].push_back(lljy(t1,t2));
	}
	for(int i=1;i<=2*n;i++){
		if(!dfn[i])ljylp(i);
	}
	for(int i=1;i<=n;i++){
		//cout<<lipu[i]<<" "<<lipu[i+n]<<endl;
		if(lipu[i]==lipu[i+n]){
			printf("IMPOSSIBLE");
			return;
		}
	}
	printf("POSSIBLE\n");
	for(int i=1;i<=n;i++){
		if(lipu[i]<lipu[i+n])printf("1 ");
		else printf("0 ");
	}
	}
	signed main(){
	T=1;
	//ios::sync_with_stdio(0);
	//cin.tie(0);cout.tie(0);
	//cin>>T;
	while(T--){
	solve();

	}
	return 0;
	}

	~~~

	建边：

	~~~ c++
	vector<int>p[2000005];
	int n,m;
		int lljy(int k,int w){//取当前的节点，比如x的否定返回x+n,x的肯定返回x 
		if(w)return k;
		return k+n;
	}
	int ljy(int k,int w){//取非，比如x的否定的非返回x,x的肯定的非返回x+n 
		if(w)return k+n;
		return k;
	}
		void make_least(int t1,int t2,int t3,int t4){//至少一个 
			p[ljy(t1,t2)].push_back(lljy(t3,t4));
			p[ljy(t3,t4)].push_back(lljy(t1,t2));
		}
	void make_x_y(int t1,int t2,int t3,int t4){//若x则y 
			p[lljy(t1,t2)].push_back(lljy(t3,t4));
			p[ljy(t3,t4)].push_back(ljy(t1,t2)); 
	} 
	void make_yiding(int t1,int t2){//一定满足 
			p[ljy(t1,t2)].push_back(lljy(t1,t2));
	}
	void make_only(int t1,int t2,int t3,int t4){//有且只有一个满足 
		make_x_y(t1,t2,t3,!t4);
		make_x_y(t3,t4,t1,!t2);
		make_x_y(t1,!t2,t3,t4);
		make_x_y(t3,!t4,t1,t2);
	}
	~~~

