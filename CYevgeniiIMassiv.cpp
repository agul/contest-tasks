#include "../algolib/cpplib/base/header.hpp"

class CYevgeniiIMassiv {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		ll n;
		in >> n;
		auto a = make_vector<ll>(n, 0);
		in >> a;
		std::vector<ll> pref(n + 1, 0);
		for (int i : range(n)) {
			pref[i + 1] = pref[i] + a[i];
		}

		SafeUnorderedMap<ll, std::vector<int>> sums;
		for (ll i : downrange(n + 1)) {
			sums[pref[i]].emplace_back(i - 1);
		}

		std::vector<ll> right(n);
		for (int i : range(n)) {
			right[i] = n - 1;
		}

		for (ll i : range(n)) {
			ll cur_sum = pref[i];
			auto& cur_vec = sums[cur_sum];
			cur_vec.pop_back();
			if (!cur_vec.empty()) {
				ll pos = cur_vec.back();
				umin(right[i], pos - 1);
			}
		}


		for (int i : downrange(n - 1)) {
			umin(right[i], right[i + 1]);
		}

		ll ans = 0;
		for (int i : range(n)) {
			ans += std::max(0LL, right[i] - i + 1);
		}
		// out << std::endl;
		out << ans << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1;
	static void generate_test(std::ostream& test) {
		test << 200000 << std::endl;
		for (int i : range(100000)) {
			test << 126271 << " ";
		}
		for (int i : range(100000)) {
			test << -126271 << " ";
		}
		test << std::endl;
	}

private:
	size_t test_id_ = 0;
};
