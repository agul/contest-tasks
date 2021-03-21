#include "base/header.hpp"

class FBSklad {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	const int kMaxSize = 1111;

	void solve(std::istream& in, std::ostream& out) {
#ifndef HOME
	    assign_files_input_txt();
#endif
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;
        int m;
        in >> m;

        std::vector<int> position(kMaxSize, 0);
        for (int size : range(1, kMaxSize)) {
            int& pos = position[size];
            pos = position[size - 1];
            while (pos < n && a[pos] < size) {
                ++pos;
            }
            if (pos >= n) {
                pos = INF;
            }
        }

        for (int i : range(m)) {
            int order;
            in >> order;
            for (int size : range(order, kMaxSize)) {
                int& pos = position[size];
                if (pos == INF || a[pos] >= size) {
                    break;
                }
                umax(pos, position[size - 1]);
                while (pos < n && a[pos] < size) {
                    ++pos;
                }
                if (pos >= n) {
                    pos = INF;
                }
            }
            int& pos = position[order];
            debug(i, order, pos, a);
            if (pos == INF) {
                continue;
            }
            a[pos] -= order;

        }
        out << std::accumulate(all(a), 0) << std::endl;
	}


	FBSklad() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
