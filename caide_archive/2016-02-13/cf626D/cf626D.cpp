#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 55;

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	vector<ll> diff_1(MAXN, 0);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (i == j || a[i] < a[j]) {
				continue;
			}
			diff_1[a[i] - a[j]]++;
		}
	}
	vector<ll> diff_2(MAXN, 0);
	for (int i = 0; i < MAXN; ++i) {
		for (int j = 0; j < MAXN - i; ++j) {
			diff_2[i + j] += diff_1[i] * diff_1[j];
		}
	}
	double total_sum = 0;
	for (int i = 0; i < MAXN; ++i) {
		for (int j = 0; j < i; ++j) {
			total_sum += diff_1[i] * diff_2[j];
		}
	}
	double x = n * (n - 1);
	total_sum /= x * x * x;
	total_sum *= 8;
	out << fixed << setprecision(16) << total_sum << endl;
}
