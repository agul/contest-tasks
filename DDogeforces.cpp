#include "base/header.hpp"
#include "graph/dsu.hpp"

class DDogeforces {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	struct Boss {
	    int salary;
	    int left;
	    int right;

	    std::tuple<int, int, int> as_tuple() const {
	        return std::make_tuple(salary, left, right);
	    }

	    bool operator<(const Boss& rhs) const {
	        return as_tuple() < rhs.as_tuple();
	    }
	};

	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        auto a = make_vector<int>(n, n, 0);
        in >> a;

        std::vector<int> salaries(n * 3);

        DSU dsu(n * 3);
        std::vector<Boss> b;
        std::vector<int> parent(n * 3, -1);

        for (int i : range(n)) {
            salaries[i] = a[i][i];
            for (int j : range(i + 1, n)) {
                b.emplace_back(Boss{a[i][j], i, j});
            }
        }
        sort(b);

        int boss_index = n;
        for (const auto& boss : b) {
            const int left_set = dsu.find_set(boss.left);
            const int right_set = dsu.find_set(boss.right);
            if (left_set != right_set) {
                if (salaries[left_set] == boss.salary) {
                    dsu.unite(right_set, left_set);
                    parent[right_set] = left_set;
                } else
                if (salaries[right_set] == boss.salary) {
                    dsu.unite(left_set, right_set);
                    parent[left_set] = right_set;
                } else {
                    salaries[boss_index] = boss.salary;
                    dsu.unite(left_set, boss_index);
                    parent[left_set] = boss_index;
                    dsu.unite(right_set, boss_index);
                    parent[right_set] = boss_index;
                    ++boss_index;
                }
            }
        }
        out << boss_index << std::endl;
        for (int i : range(boss_index)) {
            out << salaries[i] << " ";
        }
        out << std::endl;

        out << dsu.find_set(0) + 1 << std::endl;
        for (int i : range(boss_index)) {
            if (parent[i] != -1) {
                out << i + 1 << " " << parent[i] + 1 << std::endl;
            }
        }
	}


	DDogeforces() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
