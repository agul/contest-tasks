#include "base/header.hpp"
#include "graph/dsu.hpp"
#include "collections/queue/queue.hpp"

class CSolnechniiOgorod {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<std::string> field(n);
        in >> field;

        for (int j = 1; j < m; j += 3) {
            for (int i : range(n)) {
                field[i][j] = 'X';
            }
        }

        for (int j = 2; j + 1 < m; j += 3) {
            int connection = -1;
            int index = 0;
            for (int i : range(n)) {
                if (field[i][j] == 'X') {
                    index = i;
                    if (field[i][j + 1] == 'X') {
                        connection = i;
                    }
                }
                if (field[i][j + 1] == 'X') {
                    index = i;
                }
            }
            if (connection == -1) {
                field[index][j] = 'X';
                field[index][j + 1] = 'X';
            }
        }

        if (m % 3 == 1) {
            if (m == 1) {
                for (int i : range(n)) {
                    field[i][0] = 'X';
                }
            } else {
                for (int i : range(n)) {
                    if (field[i][m - 1] == 'X') {
                        field[i][m - 2] = 'X';
                    }
                }
            }
        }

        for (const auto& row : field) {
#ifdef HOME
            out << row << std::endl;
#else
            printf("%s\n", row.data());
#endif
        }
	}


	CSolnechniiOgorod() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
