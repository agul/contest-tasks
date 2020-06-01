#include "base/header.hpp"

class HDvoichnayaMediana {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	ll go(ll left, ll right, ll pos, const std::vector<ll>& a) {
		if (left + 1 == right) {
			return left;
		}
		ll med = (left + right) / 2;

		auto count = [&a](const ll left, const ll right) {
			ll ans = right - left;
			for (ll x : a) {
				if (x >= left && x < right) {
					--ans;
				}
			}
			return ans;
		};

		ll cnt_l = count(left, med);
		ll cnt_r = count(med, right);

		if (pos > cnt_l) {
			return go(med, right, pos - cnt_l, a);
		} else {
			return go(left, med, pos, a);
		}

	}

	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		std::vector<std::string> a(n);
		in >> a;
		std::vector<ll> vals;
		for (const auto& row : a) {
			ll val = 0;
			for (char ch : row) {
				val = val * 2 + (ch - '0');
			}
			vals.emplace_back(val);
		}
		ll total = (1LL << m);
		ll left = total - n;

		debug(vals);
		ll ans = go(0, total, (left - 1) / 2 + 1, vals);
		debug(ans);

		std::string binans = "";
		while (ans > 0) {
			binans += (ans % 2) + '0';
			ans /= 2;
		}
		reverse(binans);

		binans = std::string(m - binans.length(), '0') + binans;

		out << binans << std::endl;
	}


	HDvoichnayaMediana() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
