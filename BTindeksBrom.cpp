#include "base/header.hpp"

class BTindeksBrom {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int m, n;
        std::string s;
        in >> m >> n >> s;

        std::vector<std::vector<int>> positions(26);
        for (int i : range(n)) {
            positions[s[i] - 'a'].emplace_back(i);
        }
        for (int _ : range(m)) {
            std::string t;
            in >> t;
            std::vector<int> index(26, 0);
            ll error = 0;
            const int k = t.length();
            for (int i : range(k)) {
                const int letter = t[i] - 'a';
                if (positions[letter].empty()) {
                    error += k;
                    continue;
                }
                while (index[letter] < positions[letter].size() && positions[letter][index[letter]] < i) {
                    ++index[letter];
                }
                if (index[letter] == positions[letter].size()) {
                    error += std::abs(i - positions[letter].back());
                    continue;
                }
                if (index[letter] == 0) {
                    error += std::abs(i - positions[letter].front());
                    continue;
                }
                error += std::min(std::abs(i - positions[letter][index[letter]]), std::abs(i - positions[letter][index[letter] - 1]));
            }
            out << error << std::endl;
        }
	}


	BTindeksBrom() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
