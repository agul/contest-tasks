#include "base/header.hpp"
#include "data_structures/fenwick_tree.hpp"

class DMultimnozhestvo {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, q;
		in >> n >> q;
		std::vector<int> a(n);
		in >> a;
		++n;
		FenwickTreeSum<int> tree(n);
		for (int x : a) {
			tree.inc(x, 1);
		}
		for (int _ : range(q)) {
			int x;
			in >> x;
			if (x > 0) {
				tree.inc(x, 1);
				continue;
			}
			x = -x;
			int L = 0;
			int R = n;
			while (R - L > 1) {
				int md = (L + R) / 2;
				if (tree.query(md) >= x) {
					R = md;
				} else {
					L = md;
				}
			}
			debug(R);
			tree.inc(R, -1);
		}

		const int total = tree.query(n - 1);
		debug(total);
		if (total == 0) {
			out << 0 << std::endl;
			return;
		}
		{
			int L = 0;
			int R = n;
			while (R - L > 1) {
				int md = (L + R) / 2;
				if (tree.query(md) > 0) {
					R = md;
				} else {
					L = md;
				}
			}
			out << R << std::endl;
		}
	}


	DMultimnozhestvo() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 100;
		const int kMaxq = 100;


	}

};
