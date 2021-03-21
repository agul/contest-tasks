#include "base/header.hpp"
#include "maths/mod_int.hpp"
#include "maths/maths.hpp"

class EMaikIGeometricheskayaZadacha {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Int = ModInt<int>;

	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;
        std::vector<pii> points;
        for (int i : range(n)) {
            int x, y;
            in >> x >> y;
            points.emplace_back(pii{x, 1});
            points.emplace_back(pii{y, -1});
        }
        sort(points, [](const pii& lhs, const pii& rhs) {
            return pii{lhs.first, -lhs.second} < pii{rhs.first, -rhs.second};
        });

        const std::vector<Int> factorials = calc_factorial<Int>(n + 1);
        auto binom = [&factorials](const int n, const int k) {
            debug(n, k);
            if (k > n) {
                return Int::from_integer(0);
            }
            return factorials[n] * factorials[k].inverse() * factorials[n - k].inverse();
        };

        Int ans = 0;
        int balance = 0;
        int prev = points.front().first;
        int index = 0;
        while (index < points.size()) {
            const int cur_value = points[index].first;
            if (prev != cur_value) {
                const int cnt = cur_value - prev - 1;
                ans += binom(balance, k) * cnt;
            }
            while (index < points.size() && points[index].first == cur_value && points[index].second == 1) {
                balance += points[index].second;
                ++index;
            }
            ans += binom(balance, k);
            while (index < points.size() && points[index].first == cur_value && points[index].second == -1) {
                balance += points[index].second;
                ++index;
            }
            debug(ans);
            prev = cur_value;
        }
        out << ans << std::endl;
	}


	EMaikIGeometricheskayaZadacha() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
