#include "base/header.hpp"

class FNeobichnayaMatritsa {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<std::string> a(n), b(n);
        in >> a >> b;

        auto matrix = make_vector<int>(n, n, 0);
        for (int i : range(n)) {
            for (int j : range(n)) {
                matrix[i][j] = (a[i][j] != b[i][j] ? 1 : 0);
            }
        }

        for (int i : range(n - 1)) {
            for (int j : range(n - 1)) {
                const int sum = (matrix[i][j] + matrix[i + 1][j] + matrix[i][j + 1] + matrix[i + 1][j + 1]);
                if (sum == 1 || sum == 3) {
                    out << "NO" << std::endl;
                    return;
                }
            }
        }

        out << "YES" << std::endl;
	}


	FNeobichnayaMatritsa() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {

	    int testsCount;
	    in >> testsCount;

	    for (int _ : range(testsCount)) {
            std::string pans;
            out >> pans;

            int n;
            in >> n;

            std::vector<std::string> a(n), b(n);
            in >> a >> b;

            auto matrix = make_vector<int>(n, n, 0);
            for (int i : range(n)) {
                for (int j : range(n)) {
                    matrix[i][j] = (a[i][j] == '1' ? 1 : 0);
                }
            }

            int jans = -1;
            for (int mask : range(1 << (2 * n))) {
                auto matrix_copy = matrix;
                for (int i : range(n)) {
                    if (mask & (1 << i)) {
                        for (int j : range(n)) {
                            matrix_copy[i][j] ^= 1;
                        }
                    }
                }
                for (int j : range(n)) {
                    if (mask & (1 << (n + j))) {
                        for (int i : range(n)) {
                            matrix_copy[i][j] ^= 1;
                        }
                    }
                }

                int cur_value = 0;
                for (int i : range(n)) {
                    for (int j : range(n)) {
                        cur_value |= matrix_copy[i][j];
                    }
                }

                if (cur_value == 0) {
                    jans = mask;
                    break;
                }
            }
            if (jans != -1 && pans != "YES") {
                debug("WTF should be YES", pans);
                return false;
            }
	        if (jans == -1 && pans != "NO") {
                debug("WTF should be NO", pans);
                return false;
            }
	    }

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
	    const int kMaxn = 5;

	    test << 1 << std::endl;

	    const int n = Random::get(1, kMaxn);
	    test << n << std::endl;
	    for (int i : range(n)) {
	        for (int j : range(n)) {
	            test << Random::get(0, 1);
	        }
            test << std::endl;
	    }

	    for (int i : range(n)) {
            test << std::string(n, '0') << std::endl;
	    }
	}

};
