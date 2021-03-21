#include "base/header.hpp"
#include "maths/prime.hpp"

class E1BeskvadratnoeRazbienieProstayaVersiya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;
        std::vector<int> a(n);
        in >> a;

        std::set<int> prime_divs;
        int ans = 1;
        for (int x : a) {
            auto divs = get_prime_divisors_vector(x);
            int value = 1;
            for (const auto& it : divs) {
                if (it.second % 2 == 1) {
                    value *= it.first;
                }
            }
            const int prev_size = prime_divs.size();
            prime_divs.emplace(value);
            if (prime_divs.size() == prev_size) {
                ++ans;
                prime_divs = {value};
            }
        }
        out << ans << std::endl;
	}


	E1BeskvadratnoeRazbienieProstayaVersiya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
