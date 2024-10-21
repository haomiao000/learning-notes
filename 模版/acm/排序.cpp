#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N = 2e5 + 7;
int a[N], n;
void Print(int a[])
{
	for (int i = 1; i <= n; i++) cout << a[i] << " ";
	cout << endl;
}
void Bubble_sort()
{
	int b[N];
	std::copy(std::begin(a), std::end(a),  std::begin(b));
	for (int i = 1; i < n; i++)
		for (int j = 1; j <= n - i; j++)
			if (b[j] > b[j + 1])
				swap(b[j], b[j + 1]);
	Print(b);
}
void Selection_sort()
{
	int b[N];
	std::copy(std::begin(a), std::end(a),  std::begin(b));
	for (int i = 1; i < n; i++)
	{
		int pos = i;
		for (int j = i + 1; j <= n; j++)
			if (b[j] < b[pos]) pos = j;
		swap(b[i], b[pos]);
	}
	Print(b);
}
void Insertion_sort()
{
	int b[N];
	std::copy(std::begin(a), std::end(a),  std::begin(b));
	for (int i = 1; i <= n; i++)
	{
		int cnt = b[i], j = i - 1;
		while (j >= 0 && b[j] > cnt)
		{
			b[j + 1] = b[j];
			j--;
		}
		b[j + 1] = cnt;
	}
	
	Print(b);
}
//https://pdai.tech/md/algorithm/alg-sort-x-fast.html
void Quick_sort()
{
	int b[N];
	std::copy(std::begin(a), std::end(a),  std::begin(b));
	auto work = [&](auto self, int l, int r)->void
	{
		if (l >= r) return;
		int it1 = l, it2 = r, change_pos = l;
		int cnt = b[it1++];
		while (it1 <= it2)
		{
			while (it1 <= it2)
			{
				if (b[it2] >= cnt) it2--;
				else
				{
					b[change_pos] = b[it2];
					change_pos = it2;
					it2--;
					break;
				}
			}
			while (it1 <= it2)
			{
				if (b[it1] <= cnt) it1++;
				else
				{
					b[change_pos] = b[it1];
					change_pos = it1;
					it1++;
					break;
				}
			}
		}
		b[change_pos] = cnt;
		self(self, l, change_pos - 1);
		self(self, change_pos + 1, r);
	};
	work(work, 1, n);
	Print(b);
}
int b[N-5], t[N-5];
void merge_sort()
{
	std::copy(std::begin(a), std::end(a),  std::begin(b));
	auto MC = [&](auto self, int ll, int rr)->void
	{
		if (rr - ll <= 1) return;
		int mid = (rr + ll) >> 1;
		self(self , ll, mid);
		self(self , mid, rr);
		int p = ll, q = mid, s = ll;
		while (s < rr)
		{
			if (p >= mid || (q < rr && b[p] > b[q])) t[s++] = b[q++];
			else t[s++] = b[p++];
		}
		for (int i = ll; i < rr; i++) b[i] = t[i];
	};
	MC(MC , 1 , n+1);
	Print(b);
}

//(1) 将待排序序列构造成一个大顶堆。

//(2) 这个时候，整个序列的最大值就是堆顶的根节点。

//(3) 将其与末尾元素进行交换， 此时末尾就为最大值。

//(4) 然后将剩余 n-1 个元素重新构造成一个堆， 这样会得到 n 个元素的次小值。 如此反复执行， 便能得到一个有序序列了。
//https://www.acwing.com/blog/content/1644/
void Heap_Sort() {
    std::copy(std::begin(a), std::end(a),  std::begin(b));
	int size_ = n;
	auto down = [&] (auto self , int u) -> void {
		int t = u;  // t记录最小值
		if (2 * u <= size_ && b[2 * u] < b[t]) t = 2 * u; // 左儿子存在，且值比父亲小
		if (2 * u + 1 <= size_ && b[2 * u + 1] < b[t]) t = 2 * u + 1; // // 右儿子存在，且值比父亲小
		if (t != u) {
			swap(b[t], b[u]);
			self(self , t);
		}
		return;
	};
	// auto up = [&] (auto self , int u) -> void {
	// 	if (u / 2 > 0 && b[u / 2] > h[u]) {
	// 		swap(b[u / 2], b[u]);
	// 		self(self , u / 2);
	// 	}
	// 	return;
	// };
	for (int i = n / 2; i > 0; i --) down(down , i); 
	while(n --) {
        cout << b[1] << " ";
        b[1] = b[size_];
        size_ --;
        down(down , 1); 
    }
}
signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	// Bubble_sort();
	// Selection_sort();
   	// Insertion_sort();
	// Quick_sort();
	// merge_sort();
	// Heap_Sort();
	return 0;
}

/*
堆 从根到叶子维护会遇到问题:
7 12 
12 6
12 4
4 11
4 2
6 8
6 1
7 3
*/