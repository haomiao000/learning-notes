#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-7;
int n;
double L, R;
double a[15];
double F(double x) {
    double sum = 0;
    for (int i = n; i >= 0; i--)
        sum = sum * x + a[i];
    return sum;
}
int main(){
    cin >> n >> L >> R;
    for (int i = n; i >= 0; i--)
        cin >> a[i];
    while (fabs(L - R) >= eps)
    {
        double mid = (L + R) / 2;
        if (F(mid + eps) > F(mid - eps))
            L = mid;
        else
            R = mid;
    }
    printf("%.5lf", R);
    return 0;
}