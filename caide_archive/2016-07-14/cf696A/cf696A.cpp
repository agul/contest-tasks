#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

struct Query {
	ll a, b;
	ll cost;
	ll lca;
	int type;
	
	Query() : a(0), b(0), cost(0), lca(0), type(0) {}

	friend istream& operator >>(istream& in, Query& rhs) {
		in >> rhs.type >> rhs.a >> rhs.b;
		if (rhs.type == 1) {
			in >> rhs.cost;
		}

		std::unordered_set<ll> used;
		
		for (ll tmp = rhs.a; tmp >= 1; tmp >>= 1) {
			used.emplace(tmp);
		}

		for (ll tmp = rhs.b; tmp >= 1; tmp >>= 1) {
			if (used.count(tmp)) {
				rhs.lca = tmp;
				break;
			}
		}

		return in;
	}

};

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<Query> q(n);
	in >> q;
	std::unordered_map<pll, ll> edges;
	for (const auto& it : q) {
		if (it.type == 1) {
			for (ll tmp = it.a; tmp > it.lca; tmp >>= 1) {
				const ll next = tmp >> 1;
				edges[{tmp, next}] += it.cost;
			}
			for (ll tmp = it.b; tmp > it.lca; tmp >>= 1) {
				const ll next = tmp >> 1;
				edges[{tmp, next}] += it.cost;
			}
			continue;
		}
		ll ans = 0;

		for (ll tmp = it.a; tmp > it.lca; tmp >>= 1) {
			const ll next = tmp >> 1;
			ans += edges[{tmp, next}];
		}
		for (ll tmp = it.b; tmp > it.lca; tmp >>= 1) {
			const ll next = tmp >> 1;
			ans += edges[{tmp, next}];
		}

		out << ans << endl;
	}
}
