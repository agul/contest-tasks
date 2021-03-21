#include "base/header.hpp"

class CPokraskaZabora {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<int> a(n), b(n), c(m);
        in >> a >> b >> c;

        std::vector<std::vector<int>> work(n + 1);
        for (int i : range(n)) {
            if (a[i] == b[i]) {
                work[b[i]].emplace_back(i);
            }
        }

        for (int i : range(n)) {
            if (a[i] != b[i]) {
                work[b[i]].emplace_back(i);
            }
        }

        int done_work = -1;
        std::vector<int> ans(m, -1);
        for (int i : downrange(m)) {
            const int color = c[i];
            if (work[color].empty()) {
                if (done_work == -1) {
                    out << "NO" << std::endl;
                    return;
                }
                ans[i] = done_work;
                continue;
            }
            const int position = work[color].back();
            ans[i] = position;
            a[position] = color;
            work[color].pop_back();
            if (done_work == -1) {
                done_work = ans[i];
            }
        }

        for (int i : range(n)) {
            if (a[i] != b[i]) {
                out << "NO" << std::endl;
                return;
            }
        }

        out << "YES" << std::endl;
        for (int i : range(m)) {
            out << ans[i] + 1 << " ";
        }
        out << std::endl;
	}


	CPokraskaZabora() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
