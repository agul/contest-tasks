#include "base/header.hpp"

class DABGraf {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<std::string> field(n);
        in >> field;

        for (int i : range(n)) {
            for (int j : range(i + 1, n)) {
                if (field[i][j] == field[j][i]) {
                    out << "YES" << std::endl;
                    for (int k : range(m / 2)) {
                        out << i + 1 << " " << j + 1 << " ";
                    }
                    out << i + 1 << " ";
                    if (m % 2 == 1) {
                        out << j + 1 << " ";
                    }
                    out << std::endl;
                    return;
                }
            }
        }

        if (m % 2 == 1) {
            out << "YES" << std::endl;
            for (int i : range(m + 1)) {
                out << 1 + (i % 2) << " ";
            }
            out << std::endl;
            return;
        }

        int abba = -1;
        for (int i : range(n)) {
            int a = -1;
            int b = -1;
            for (int j : range(n)) {
                if (a == -1 && field[i][j] == 'a') {
                    a = j;
                }
                if (b == -1 && field[i][j] == 'b') {
                    b = j;
                }
            }
            if (a == -1 || b == -1) {
                continue;
            }

            out << "YES" << std::endl;
            if (m % 4 == 2) {
                out << b + 1 << " ";
            }
            out << i + 1 << " ";
            for (int k : range(m / 4)) {
                out << a + 1 << " "  << i + 1 << " " << b + 1 << " " << i + 1 << " ";
            }
            if (m % 4 == 2) {
                out << a + 1 << " ";
            }
            out << std::endl;
            return;
        }
        out << "NO" << std::endl;
	}


	DABGraf() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
