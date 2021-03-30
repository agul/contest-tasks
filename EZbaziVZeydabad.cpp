#include "base/header.hpp"
#include "cpplib/data_structures/fenwick_tree/fenwick_tree.hpp"

class EZbaziVZeydabad {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Tree = FenwickTreeSum<int>;

	void solve(std::istream& in, std::ostream& out) {
		auto a = input(in);
		const int n = a.size();
		const int m = a.front().size();
		std::vector<Tree> trees(n + m, Tree(n + m));

		auto z_left = make_vector<int>(n, m, 0);
		for (int i : range(n)) {
			for (int j : range(m)) {
				const int prev = (j > 0 ? z_left[i][j - 1] : 0);
				z_left[i][j] = (a[i][j] == 'z' ? prev + 1 : 0);
			}
		}

		auto z_right = make_vector<int>(n, m, 0);
		for (int i : range(n)) {
			for (int j : downrange(m)) {
				const int prev = (j < m - 1 ? z_right[i][j + 1] : 0);
				z_right[i][j] = (a[i][j] == 'z' ? prev + 1 : 0);
			}
		}

		auto z_down = make_vector<int>(n, m, 0);
		for (int i : downrange(n)) {
			for (int j : range(m)) {
				const int prev = (i < n - 1 && j > 0 ? z_down[i + 1][j - 1] : 0);
				z_down[i][j] = (a[i][j] == 'z' ? prev + 1 : 0);
			}
		}

		std::vector<std::pair<int, pii>> updates;
		updates.reserve(n * m);
		for (int i : range(n)) {
			for (int j : range(m)) {
				const int col = z_right[i][j] + j - 1;
				if (col >= j) {
					updates.emplace_back(col, pii{i, j});
				}
			}
		}
		sort(updates);
		reverse(updates);

		int index = 0;
		ll ans = 0;
		for (int j : downrange(m)) {
			while (index < updates.size() && updates[index].first == j) {
				const auto& it = updates[index].second;
				const int tree_id = it.X + it.Y;
				trees[tree_id].inc(it.Y, 1);
				++index;
			}
			for (int i : range(n)) {
				const int mn = std::min(z_left[i][j], z_down[i][j]);
				if (mn == 0) {
					continue;
				}
				ans += trees[i + j].query(j - mn + 1, j);
			}
		}

		out << ans << std::endl;
	}

	std::vector<std::string> input(std::istream& in) {
		int n, m;
#ifdef HOME
		in >> n >> m;
		auto a = make_vector<std::string>(n, "");
		in >> a;
#else
		scanf("%d%d", &n, &m);
		auto a = make_vector<std::string>(n, "");
		char s[3333];
		for (int i : range(n)) {
			scanf("%s", s);
			a[i] = std::string(s);
		}
#endif
		return a;
	}


	EZbaziVZeydabad() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
