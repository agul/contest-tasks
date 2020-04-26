#include "base/header.hpp"

class ValueDivision {
public:
	std::vector <int> getArray(std::vector <int> a) {
		int n = a.size();
		std::map<int, std::set<int>> occurrences;
		for (int i = 0; i < n; ++i) {
			occurrences[a[i]].emplace(i);
		}
		while (!occurrences.empty()) {
			auto it = occurrences.rbegin();
			const int value = it->first;
			if (value == 1) {
				break;
			}
			const int remainder = *(it->second.rbegin());
			for (int x : it->second) {
				if (x == remainder) {
					break;
				}
				--a[x];
				occurrences[value - 1].emplace(x);
			}
			occurrences.erase(value);
		}
		return a;
	}
};

class SRM784_easy {
public:
	void solve(std::istream& in, std::ostream& out) {

		const int MAXN = 1000;
		const int MAXM = 1000000000;
		std::vector<int> test(MAXN);
		for (int i : range(MAXN)) {
			test[i] = MAXM;
		}

		bool first = true;
		for (int i : test) {
			if (!first) {
				out << ",";
			}
			first = false;
			out << i;
		}
		out << std::endl;
		return;




		int n;
		in >> n;
		auto a = make_vector<int>(n, 0);
		in >> a;

		ValueDivision solution;
		auto ans = solution.getArray(a);

		for (int x : ans) {
			out << x << " ";
		}
		out << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1;
	static void generate_test(std::ostream& test) {
		int n = 1000;
		test << n << std::endl;
		for (int i : range(n)) {
			test << 1000000000 << " ";
		}
		test << std::endl;
	}

private:
	size_t test_id_ = 0;
};
