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
signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	Bubble_sort();
	Selection_sort();
   	Insertion_sort();
	Quick_sort();
	merge_sort();

	return 0;
}