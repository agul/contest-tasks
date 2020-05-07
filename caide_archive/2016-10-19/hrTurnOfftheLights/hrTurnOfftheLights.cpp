#include "base/header.hpp"
#include "maths/maths.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 20;
const int MAXM = 10;
const int ITER = 10;

/*
void log_input(std::ostream& out, const int n, const int k, const std::vector<ll>& a) {
	out << n << " " << k << endl;
	for (const auto& it : a) {
		out << it << " ";
	}
	out << endl;
}

void log_output(std::ostream& out, const int n, const ll ans, const int best_mask) {
	out << ans << endl;
	for (int i : range(n)) {
		if (best_mask & (1 << i)) {
			out << i + 1 << " ";
		}
	}
	out << endl;
}

void gen(int& n, int& k, std::vector<ll>& a) {
	n = Random::get(3, MAXN);
	k = Random::get(1, n / 2);
	a.resize(n);
	for (auto& it : a) {
		it = Random::get(1, MAXM);
	}
}

void read(std::istream& in, int& n, int& k, std::vector<ll>& a) {
	in >> n >> k;
	a.resize(n);
	in >> a;
}

std::pair<ll, int> process(const int n, const int k, const std::vector<ll>& a) {
	ll ans = LINF;
	int best_mask = -1;
	for (int mask : range(1 << n)) {
		ll cur = 0;
		vector<bool> lamps(n, true);
		for (int i : range(n)) {
			if ((mask & (1 << i)) == 0) {
				continue;
			}
			for (int j : inclusiveRange(std::max(0, i - k), std::min(n - 1, i + k))) {
				lamps[j] = !lamps[j];
			}
			cur += a[i];
		}
		if (std::count(all(lamps), true) != 0) {
			continue;
		}
		if (umin(ans, cur)) {
			best_mask = mask;
		}
	}
	return{ ans, best_mask };
}

void solve(std::istream& in, std::ostream& out) {
	for (int iteration : range(ITER)) {
		int n, k;
		vector<ll> a;

		gen(n, k, a);
		// read(in, n, k, a);
		log_input(out, n, k, a);

		auto result = process(n, k, a);

		const ll ans = result.first;
		const int best_mask = result.second;

		log_output(out, n, ans, best_mask);

		out << endl;
	}
}

*/

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	in >> n >> k;
	vector<ll> a(n);
	in >> a;
	const int delta = k * 2 + 1;
	ll ans = LINF;
	for (int start : inclusiveRange(std::min(n - 1, k))) {
		ll cur = 0;
		int mx = 0;
		for (int pos = start; pos < n; pos += delta) {
			cur += a[pos];
			mx = pos + k;
		}
		if (mx >= n - 1) {
			umin(ans, cur);
		}
	}
	out << ans << endl;
}