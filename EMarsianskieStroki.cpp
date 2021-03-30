#include "base/header.hpp"
#include "string/prefix_function.hpp"

class EMarsianskieStroki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	static bool can_be_combined(const std::string& needle, const std::string& pile) {
	    if (needle.length() > pile.length()) {
	        return false;
	    }

        auto max_prefix_coverage = [](const std::string& s, const std::string& t) {
            const std::string tmp = t + "#" + s;
            const auto p = prefix_function(tmp);
            debug(tmp); debug(p);

            const int n = s.length();
            std::vector<size_t> max_value(n + 1, 0);
            max_value[0] = 0;
            for (int i : range(n)) {
                max_value[i + 1] = std::max(max_value[i], p[i + t.length() + 1]);
            }
            return max_value;
        };

        const auto max_prefix = max_prefix_coverage(pile, needle);
        auto max_suffix = max_prefix_coverage({all(reversed(pile))}, {all(reversed(needle))});
        reverse(max_suffix);

        debug(max_prefix); debug(max_suffix);

        const size_t len = needle.length();
        for (size_t i : range(pile.length())) {
            if (max_prefix[i + 1] < len && max_prefix[i + 1] > 0 && max_prefix[i + 1] + max_suffix[i + 1] >= len) {
                return true;
            }
        }
        return false;
	}

	void solve(std::istream& in, std::ostream& out) {
        std::string s;
        int m;
        in >> s >> m;

        int ans = 0;
        for (int _ : range(m)) {
            std::string t;
            in >> t;

            if (can_be_combined(t, s)) {
                ++ans;
            }
        }
        out << ans << std::endl;
	}


	EMarsianskieStroki() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    const int kMaxn = 10;
	    const int kAlphabetSize = 2;

	    const int n = Random::get(1, kMaxn);
	    std::string s(n, '$');
	    for (int i : range(n)) {
	        s[i] = Random::get(0, kAlphabetSize - 1) + 'a';
	    }

	    for (int i : range(n)) {
	        for (int j : range(i, n)) {
	            for (int x : range(j + 1, n)) {
	                for (int y : range(x, n)) {
	                    const std::string tmp = s.substr(i, j - i + 1) + s.substr(x, y - x + 1);
	                    if (!can_be_combined(tmp, s)) {
	                        debug("WTF", s, tmp);
	                        return false;
	                    }
	                }
	            }
	        }
	    }

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
