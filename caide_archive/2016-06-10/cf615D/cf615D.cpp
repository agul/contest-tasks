#include "Head.h"
#include "IO.h"
#include "Maths.h"

int __;
IO io;
const ll MOD = 1000000007;
const int MAXN = 222222;

int n;
ll a[MAXN], x;
unordered_map<ll, ll> cnt;

ll getPower(ll x) {
	return (x - 1) * x * (x + 1) / 6;
}

ll root() {
	ll tot = 1;
	for (int i = 0; i < n; i += 2) {
		mulMod(tot, a[i]);
	}
	return tot;
}

vector<int> testVec;

int f(const std::vector<int>& a, const std::function<int(const int&, const int& b)>& g) {
	return std::accumulate(a.begin(), a.end(), 0, g);
}

void solve(istream& ins, ostream& out) {
	std::vector<int> a;
	for (int i = 0; i < 10; ++i) {
		a.emplace_back(rand() % 5);
	}
	for (const auto& it : a) {
		std::cout << it << " ";
	}
	std::cout << std::endl;
	int y = 0;
	std::cout << f(a, [=](const int& x, const int& p) ->int {
		if (x & 1) {
			return true;
		}
		return -1;
	}) << " " << std::endl;
	std::cout << y << " " << std::endl;

}
