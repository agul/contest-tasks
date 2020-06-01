#include "base/header.hpp"

class SwapTheString {
public:
	long long findNumberOfSwaps(std::string P, int A0, int X, int Y, int N, int K) {
		std::vector<ll> a(N);
		a[0] = A0;
		for (int i = 1; i < N; ++i) {
			a[i] = (a[i-1] * X + Y) % 1812447359;
		}

		std::vector<int> s(N);
		for (int i = 0; i < P.size(); ++i) {
			s[i] = P[i] - 'a';
		}
		for (int i = P.size(); i < N; ++i) {
			s[i] += a[i] % 26;
		}

		ll ans = 0;
		for (int i = 0; i < K; ++i) {
			std::vector<int> cnt(26, 0);
			for (int j = i; j < N; j += K) {
				const int cur_value = s[j];
				for (int k = 0; k < cur_value; ++k) {
					ans += cnt[k];
				}
				++cnt[cur_value];
			}
		}
		return ans;
	}
};

class SRM786_easy {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		std::string P;
		int A0, X, Y, N, K;
		in >> P >> A0 >> X >> Y >> N >> K;
		SwapTheString solution;
		out << solution.findNumberOfSwaps(P.substr(1), A0, X, Y, N, K) << std::endl;
	}


	SRM786_easy() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
