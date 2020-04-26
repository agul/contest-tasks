#include "../algolib/cpplib/base/header.hpp"

class EPrekrasnieTroiki {
public:
	const ll kVals[4] = {0, 2, 3, 1};

	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			ll n;
			in >> n;
			--n;

			const ll triple_id = n / 3;
			const ll id_in_triple = n % 3;
			ll x = 1;
			ll cnt = 0;
			while (true) {
				if (cnt + x > triple_id) {
					break;
				}
				cnt += x;
				x *= 4;
			}

			std::vector<ll> ans(3, 0);
			ans[0] = triple_id - cnt + x;

			ll cur = ans[0];
			ll step = 1;
			while (cur > 0) {
				const ll digit = cur % 4;
				ans[1] += kVals[digit] * step;

				cur /= 4;
				step *= 4;
			}
			ans[2] = ans[0] ^ ans[1];
			out << ans[id_in_triple] << std::endl;
		}
	}

	static constexpr int MAXN = 1000;
	bool check(std::string input, std::string expected_output, std::string actual_output) {
		std::unordered_set<int> used;
		std::vector<int> ans;
		for (int i : range(1,MAXN)) {
			if (used.find(i) !=  used.cend()) {
				continue;
			}
			for (int j : range(i + 1, 10000)) {
				if (used.count(j)) {
					continue;
				}
				bool ok = false;
				for (int k : range(j + 1, 10000)) {
					if (!used.count(k) && (i ^ j ^ k) == 0) {
						// out << i << " " << j << " " << k << std::endl;
						used.emplace(i);
						used.emplace(j);
						used.emplace(k);
						ans.emplace_back(i);
						ans.emplace_back(j);
						ans.emplace_back(k);
						ok = true;
						break;
					}
				}
				if (ok) {
					break;
				}
			}
		}

		return true;
	}

	static constexpr size_t kGeneratedTestsCount = 1;
	static void generate_test(std::ostream& test) {
		test << MAXN << std::endl;
		for (int i : inclusiveRange(1,MAXN)) {
			test << i << std::endl;
		}
	}

private:
	size_t test_id_ = 0;
};
