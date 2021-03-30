#include "base/header.hpp"
#include "data_structures/fenwick_tree/fenwick_tree_2d.hpp"

class TestFenwickTree2D {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        const int kMaxn = 100;
        const int kMaxValue = 10;

        auto a = make_vector<int>(kMaxn, kMaxn, 0);
        for (auto& row : a) {
            for (auto& col : row) {
                col = Random::get(1, kMaxValue);
            }
        }

        FenwickTreeSum2D<int> tree(kMaxn, kMaxn);
        for (int i : range(kMaxn)) {
            for (int j : range(kMaxn)) {
                tree.inc(i, j, a[i][j]);
            }
        }

        auto pref = make_vector<int>(kMaxn + 1, kMaxn + 1, 0);
        for (int i : range(kMaxn)) {
            for (int j : range(kMaxn)) {
                pref[i + 1][j + 1] = -pref[i][j] + pref[i + 1][j] + pref[i][j + 1] + a[i][j];
            }
        }

        debug(a, pref[1][2]);
        for (int x1 : range(kMaxn)) {
            for (int y1 : range(kMaxn)) {
                for (int x2 : range(x1, kMaxn)) {
                    for (int y2 : range(y1, kMaxn)) {
                        const int jans = pref[x2 + 1][y2 + 1] + pref[x1][y1] - pref[x2 + 1][y1] - pref[x1][y2 + 1];
                        const int pans = tree.query(x1, y1, x2, y2);
                        if (jans != pans) {
                            debug(x1, y1, x2, y2, pans, jans);
                            out << "WA" << std::endl;
                            return;
                        }
                    }
                }
            }
        }
        out << "OK" << std::endl;
	}


	TestFenwickTree2D() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
