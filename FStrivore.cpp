#include "base/header.hpp"
#include "maths/bits.hpp"
#include "maths/mod_int.hpp"
#include "maths/maths.hpp"

class FStrivore {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Int = ModInt<int>;

	std::unordered_set<std::string> words;

	int maxlen = 0;

	void go(const std::string& s) {
		if (s.length() == maxlen) {
			words.emplace(s);
			return;
		}
		for (int i : range(s.size() + 1)) {
			for (char ch : inclusiveRange('a', 'z')) {
				std::string t = s.substr(0, i) + ch + s.substr(i);
				go(t);
			}
		}
	}

	void solve(std::istream& in, std::ostream& out) {
		int n;
		std::string s;

//		in >> n >> s;
//		s = "a";
//		for (int i : range(1, 6)) {
//			maxlen = s.length() + i;
//			words.clear();
//			go(s);
//			debug(i, words.size());
//		}
//		return;

//		std::vector<int> a = {1, 1, 0};
//		reverse(a);
//		for (int len : range(1, 20)) {
//			int cnt = 0;
//			for (int mask : range(0, 1 << 20)) {
//				if (bit_width(mask) != len) {
//					continue;
//				}
//				int cur = 0;
//				int value = mask;
//				while (cur < a.size() && value > 0) {
//					if (value % 2 == a[cur]) {
//						++cur;
//					}
//					value /= 2;
//				}
//				if (cur == a.size()) {
//					++cnt;
//				}
//			}
//			debug(len, cnt);
//		}

		in >> n >> s;
		int k = s.length();

		auto factorials = calc_factorial<Int>(k + n + 5);

		auto binom = [&factorials](const int n, const int k) {
			return factorials[n] * (factorials[n - k] * factorials[k]).inverse();
		};

		Int ans = 0;

		const Int a = 26;
		const Int b = 25;

		for (int x : inclusiveRange(n)) {
			ans += binom(k - 1 + x, k - 1) * binpow(a, n - x) * binpow(b, x);
		}
		out << ans << std::endl;
	}


	FStrivore() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
