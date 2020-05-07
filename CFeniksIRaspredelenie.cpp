#include "base/header.hpp"

class CFeniksIRaspredelenie {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n, k;
			in >> n >> k;
			std::string s;
			in >> s;
			std::vector<int> cnt(256, 0);
			for (char ch : s) {
				cnt[ch]++;
			}

			std::set<char> letters_set(all(s));
			std::vector<char> letters(all(letters_set));
			std::string ans;
			if (letters.size() == 1) {
				const char a = letters.front();
				ans = std::string(cnt[a] / k + (cnt[a] % k > 0 ? 1 : 0), a);
			}
			else {
				const char a = letters[0];
				if (cnt[a] < k) {
					int sum = 0;
					char last = a;
					for (char x : letters) {
						sum += cnt[x];
						last = x;
						if (sum >= k) {
							break;
						}
					}
					ans = std::string(1, last);
				} else {
					if (letters.size() == 2 && cnt[a] == k) {
						const char b = letters[1];
						ans = std::string(1, a) + std::string(cnt[b] / k + (cnt[b] % k > 0 ? 1 : 0), b);
					} else {
						ans = std::string(cnt[a] - k + 1, a);
						for (char x : letters) {
							if (x != a) {
								ans += std::string(cnt[x], x);
							}
						}
					}
				}
			}

			out << ans << std::endl;
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
