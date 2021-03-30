#include "base/header.hpp"
#include "maths/bits.hpp"
#include "collections/stack/stack.hpp"

class GMaksimiziruiOstavshuyusyaStroku {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        std::string s;
        in >> s;

        const int n = s.length();
        std::map<int, std::set<int>> positions;
        for (int i : range(n)) {
            const int ch = s[i] - 'a';
            positions[ch].emplace(i);
        }

        const int diff = positions.size();
        std::string ans;
        for (int i : range(diff)) {
            int best = -1;
            for (const auto& it : positions) {
                const int index = *it.second.begin();
                bool fail = false;
                for (const auto& jt : positions) {
                    if (*jt.second.rbegin() < index) {
                        fail = true;
                        break;
                    }
                }
                if (fail) {
                    continue;
                }
                umax(best, it.first);
            }
            ans += best + 'a';
            const int index = *positions[best].begin();
            positions.erase(best);
            for (auto& it : positions) {
                while (*it.second.begin() < index) {
                    it.second.erase(it.second.begin());
                }
            }
        }
        out << ans << std::endl;

        /*
        std::vector<bool> used(256, false);
        Stack<char> st(n);
        for (const char ch : s) {
            while (!st.empty() && ch >= st.top() && cnt[st.top()] > 0) {
                used[st.top()] = false;
                st.pop();
            }
            --cnt[ch];
            if (!used[ch]) {
                st.push(ch);
                used[ch] = true;
            }
        }

        std::string ans;
        for (int i : range(diff)) {
            ans += st.data().at(i);
        }
        out << ans << std::endl;
         */
    }


	GMaksimiziruiOstavshuyusyaStroku() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    int testsCount;
	    in >> testsCount;
	    for (int test : range(testsCount)) {
	        std::string s;
	        in >> s;
            const int n = s.length();

	        std::string jans;
	        std::vector<int> last_used(26, -1);
	        int timer = 0;

	        auto count_unique = [&last_used, &timer, &n](const std::string& s, const int mask) {
	            ++timer;
	            int ans = 0;
	            for (int i : range(n)) {
	                if (test_bit(mask, i) && umax(last_used[s[i] - 'a'], timer)) {
                        ++ans;
	                }
	            }
	            return ans;
	        };

	        const int total_unique = count_unique(s, (1 << n) - 1);

	        for (int mask : range(1 << n)) {
                if (popcount(mask) == total_unique && count_unique(s, mask) == total_unique) {
                    std::string tmp;
                    for (int i : range(n)) {
                        if (test_bit(mask, i)) {
                            tmp += s[i];
                        }
                    }
                    umax(jans, tmp);
                }
	        }


	        std::string pans;
	        out >> pans;

	        if (pans != jans) {
	            debug(test, s, jans, pans);
	            return false;
	        }
	    }
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
        const int testsCount = 100;
        const int kMaxLen = 20;
        const int kMaxAlphabet = 4;

        test << testsCount << std::endl;
        for (int _ : range(testsCount)) {
            const int n = Random::get(1, kMaxLen);
            std::string s;
            for (int i : range(n)) {
                s += 'a' + Random::get(0, kMaxAlphabet - 1);
            }
            test << s << std::endl;
        }
	}

};
