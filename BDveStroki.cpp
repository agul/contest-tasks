#include "base/header.hpp"

class BDveStroki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        std::string s, t;
        in >> s >> t;

        const int n = s.length();
        const int m = t.length();

        auto positions = make_vector<int>(26, 0, 0);
        for (int i : range(m)) {
            const int value = t[i] - 'a';
            positions[value].emplace_back(i);
        }
        std::vector<int> leftmost(n);
        std::vector<int> rightmost(n);

        auto fail = [&out]() {
            out << "No" << std::endl;
        };

        int left_index = -1;
        for (int i : range(n)) {
            if (left_index + 1 < m && s[i] == t[left_index + 1]) {
                ++left_index;
            }
            const auto& pos = positions[s[i] - 'a'];
            debug(i, pos, left_index);
            const auto it = std::upper_bound(all(pos), left_index);
            if (it == pos.cbegin()) {
                fail();
                return;
            }
            leftmost[i] = *std::prev(it);
        }

        int right_index = m;
        for (int i : downrange(n)) {
            if (right_index - 1 >= 0 && s[i] == t[right_index - 1]) {
                --right_index;
            }
            const auto& pos = positions[s[i] - 'a'];
            const auto it = std::lower_bound(all(pos), right_index);
            if (it == pos.cend()) {
                fail();
                return;
            }
            rightmost[i] = *it;
        }

        for (int i : range(n)) {
            if (leftmost[i] < rightmost[i]) {
                fail();
                return;
            }
        }
        out << "Yes" << std::endl;
	}


	BDveStroki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
