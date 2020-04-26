#include "../algolib/cpplib/base/header.hpp"

bool sign(int x) {
	return x > 0;
}

class CChereduyushchayasyaPodposledovatelnost {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int n;
			in >> n;
			auto a = make_vector<ll>(n, 0);
			in >> a;
			std::vector<ll> b;
			for (ll x : a) {
				if (b.empty() || sign(x) != sign(b.back())) {
					b.emplace_back(x);
				} else {
					umax(b.back(), x);
				}
			}
			const ll ans = std::accumulate(all(b), 0LL);
			out << ans << std::endl;
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
