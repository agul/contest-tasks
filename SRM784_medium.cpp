#include "base/header.hpp"

void compress(std::vector<int>& a) {
	auto b = a;
	b.emplace_back(0);
	sort(b);
	unique(b);

	std::unordered_map<int, int> vals;
	for (int i : range(b.size())) {
		vals[b[i]] = i;
	}

	for (int& x : a) {
		x = vals[x];
	}

}


class SpeedingUpBozosort {
public:
	double expectedComparisons(std::vector <int> a, int numSwaps) {
		int n = a.size();
		std::set<int> distinct;
		const int MAXN = 8;
		for (int a : range(MAXN)) {
			for (int b : range(MAXN)) {
				if (b == 0 && a > 0) {
					continue;
				}
				for (int c : range(MAXN)) {
					if (c == 0 && b > 0) {
						continue;
					}
					for (int d : range(MAXN)) {
						if (d == 0 && c > 0) {
							continue;
						}
						for (int e : range(MAXN)) {
							if (e == 0 && d > 0) {
								continue;
							}
							for (int f : range(MAXN)) {
								if (f == 0 && e > 0) {
									continue;
								}
								std::vector<int> num{a, b, c, d, e, f};
								compress(num);

								int val = 0;
								for (int x : num) {
									val = val * 10 + x;
								}
								distinct.emplace(val);
							}
						}

					}
				}
			}
		}
		return distinct.size();
	}
};

class SRM784_medium {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		auto a = make_vector<int>(n, 0);
		in >> a;

		SpeedingUpBozosort solution;
		auto ans = solution.expectedComparisons(a, k);
		out << ans << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
