#include "base/header.hpp"

class EYeshcheOdnaZadachaOFerzyakh {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<pii> points(m);
        in >> points;

        std::vector<std::vector<pii>> rows(n), cols(n), left_diag(2 * n), right_diag(2 * n);
        auto left_diagonal_id = [&n](const int row, const int col) {
            return row + col - 2;
        };
        auto right_diagonal_id = [&n](const int row, const int col) {
            return n - row + col - 1;
        };

        std::vector<int> cnt(m, 0);

        for (int i : range(m)) {
            const int x = points[i].first;
            const int y = points[i].second;
            rows[x - 1].emplace_back(y, i);
            cols[y - 1].emplace_back(x, i);
            right_diag[right_diagonal_id(x, y)].emplace_back(x, i);
            left_diag[left_diagonal_id(x, y)].emplace_back(x, i);
        }

        auto process = [&cnt](std::vector<std::vector<pii>>& rows) {
            for (auto& row : rows) {
                sort(row);
                if (row.empty()) {
                    continue;
                }
                for (int i : range(row.size() - 1)) {
                    debug(row[i]);
                    ++cnt[row[i].second];
                    ++cnt[row[i + 1].second];
                }
            }
        };

        process(rows);
        process(cols);
        process(left_diag);
        process(right_diag);

        std::vector<int> ans(9, 0);
        for (int x : cnt) {
            ++ans[x];
        }
        for (int x : ans) {
            out << x << " ";
        }
        out << std::endl;
	}


	EYeshcheOdnaZadachaOFerzyakh() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
