#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/mod_int.hpp"

class CSchastlivayaPodposledovatelnost {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Int = ModInt<int>;

	void solve(std::istream& in, std::ostream& out) {
        std::unordered_map<int, int> cnt;
        for (int x : happy) {
            cnt[x] = 0;
        }

        int n, k;
        in >> n >> k;
        int count_single_numbers = 0;
        for (int i : range(n)) {
            int x;
            in >> x;
            if (!cnt.count(x)) {
                ++count_single_numbers;
            } else {
                ++cnt[x];
            }
        }

        auto fact = calc_factorial<Int>(n);
        auto binom = [&fact](const int n, const int k) {
            return fact[n] * fact[k].inverse() * fact[n - k].inverse();
        };

        auto dp = make_vector<Int>(k + 1, 0);
        for (int i : inclusiveRange(std::min(count_single_numbers, k))) {
            dp[i] = binom(count_single_numbers, i);
        }
        for (const auto& it : cnt) {
            for (int i : downrange(k)) {
                dp[i + 1] += dp[i] * it.second;
            }
        }

        out << dp[k] << std::endl;
	}

	const int kMaxn = 1'000'000'000;
	std::vector<ll> happy;

	void generate_happy_numbers(const ll prefix) {
	    if (prefix > kMaxn) {
	        return;
	    }
        happy.emplace_back(prefix);
        generate_happy_numbers(prefix * 10 + 4);
        generate_happy_numbers(prefix * 10 + 7);
	}

	CSchastlivayaPodposledovatelnost() {
	    generate_happy_numbers(4);
	    generate_happy_numbers(7);
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
