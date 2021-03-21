#include "base/header.hpp"

class CMaksimalnayaShirina {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        std::string s, t;
        in >> n >> m >> s >> t;

        std::vector<int> a(n);
        for (int i : range(n)) {
            a[i] = s[i] - 'a';
        }

        std::vector<int> b(m);
        for (int i : range(m)) {
            b[i] = t[i] - 'a';
        }

        auto positions = make_vector<int>(26, 0, 0);
        for (int i : range(n)) {
            positions[a[i]].emplace_back(i);
        }

        std::vector<int> pos_left;
        int index = 0;
        for (int i : range(n)) {
            if (b[index] == a[i]) {
                pos_left.emplace_back(i);
                ++index;
            }
        }

        std::vector<int> pos_right;
        index = m - 1;
        for (int i : downrange(n)) {
            if (a[i] == b[index]) {
                pos_right.emplace_back(i);
                --index;
            }
        }
        reverse(pos_right);

        int ans = 0;
        for (int i : range(1, m)) {
            umax(ans, pos_right[i] - pos_left[i - 1]);
        }
        out << ans << std::endl;
	}


	CMaksimalnayaShirina() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
