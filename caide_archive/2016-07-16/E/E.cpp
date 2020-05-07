#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/mod_int.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

using Num = ModInt<int>;

Num d[5010][5010];

void solve(std::istream& in, std::ostream& out) {
	fill(d, 0);
	d[1][1] = 1;
	d[0][0] = 1;
	for (int k = 1; k < 5000; k++)
	{
		for (int l = 1; l <= k; l++)
		{
			d[k + 1][l] += d[k][l] * k;
			d[k + 1][l + 1] += d[k][l];
		}
	}
	vector<Num>K_fact(5010);
	vector<Num>Inv_K_fact(5010);
	K_fact[0] = 1;
	Inv_K_fact[0] = K_fact[0].inverse();
	for (int i = 1; i <= 5000; i++) {
		K_fact[i] = K_fact[i - 1] * i;
		Inv_K_fact[i] = K_fact[i].inverse();
	}
	int n, l, r;
	while (in >> n >> l >> r)
	{
		if (n == 0) {
			break;
		}
		Num ans = 0;
		for (int i = 1; i <= n; i++)
		{
			ans += d[i - 1][l - 1] * d[n - i][r - 1] * K_fact[n - 1] *Inv_K_fact[i - 1] *Inv_K_fact[n - 1 - i + 1];
		}
		out << ans << endl;
	}
	
}
