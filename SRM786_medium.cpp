#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/mod_int.hpp"

using Int = ModInt<int, 1000000007>;

class ModCounters {
public:
	int findExpectedSum(std::vector <int> P, int A0, int X, int Y, int N, int K) {
		std::vector<ll> a(N);
		a[0] = A0;
		for (int i = 1; i < N; ++i) {
			a[i] = (a[i-1] * X + Y) % 1812447359;
		}
		std::vector<int> s(N);
		for (int i = 0; i < P.size(); ++i) {
			s[i] = P[i];
		}
		for (int i = P.size(); i < N; ++i) {
			s[i] = a[i] % 512;
		}

		if (N == 1) {
			s[0] = (s[0] + K) % 512;
			return s[0];
		}

		if (N == 2) {
			
		}

		Int ans = 0;

		Int n = N;
		Int k = K;
		Int denominator = sqr(n - 2).inverse();
		Int A = binpow((n - 1) * n.inverse(), K);
		Int B = binpow(n.inverse(), K);

		debug(denominator, A, B);

		for (int i = 0; i < N; ++i) {
			ans += (Int(s[i]) * (n - 2) * (-B - A + n * A) - k * (n - 2) * B + (n - 1) * (A - B)) * denominator;
		}
		return ans.as<ll>();
	}
};

class SRM786_medium {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, A0, X, Y, N, K;
		in >> n;
		std::vector<int> P(n);
		in >> P >> A0 >> X >> Y >> N >> K;

		ModCounters solution;
		out << solution.findExpectedSum(P, A0, X, Y, N, K) << std::endl;
	}


	SRM786_medium() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
