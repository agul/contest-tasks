#include "base/header.hpp"
#include "maths/bits.hpp"
#include "maths/maths.hpp"
#include "collections/queue/queue.hpp"

class DANDORISummaKvadratov {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		Queue<int> q(n);

		for (int bit : range(21)) {
			sort(a);
			q.clear();
			for (int i : range(n)) {
				const int x = a[i];
				if (test_bit(x, bit)) {
					q.push(i);
				}
			}
			for (int i : downrange(n)) {
				if (q.empty()) {
					break;
				}
				const int x = a[i];
				if (!test_bit(x, bit)) {
					const int index = q.pop_front();
					if (index >= i) {
						break;
					}
					a[index] -= (1 << bit);
					a[i] += (1 << bit);
				}
			}
			debug(a);
		}
		ll ans = 0;
		for (const ll x : a) {
			ans += sqr(x);
		}
		out << ans << std::endl;
	}


	DANDORISummaKvadratov() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
