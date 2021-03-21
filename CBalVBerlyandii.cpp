#include "base/header.hpp"

class CBalVBerlyandii {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int a, b, k;
        in >> a >> b >> k;
        std::vector<int> boys(k), girls(k);
        in >> boys >> girls;

        std::vector<pii> pairs;
        std::vector<int> cnt_girls(b, 0);
        for (int i : range(k)) {
            --boys[i];
            --girls[i];
            pairs.emplace_back(boys[i], girls[i]);
            cnt_girls[girls[i]]++;
        }
        sort(pairs);

        int total = k;

        int index = 0;
        int last_boy = -1;
        ll ans = 0;
        for (int i : range(k)) {
            int boy, girl;
            std::tie(boy, girl) = pairs[i];
            if (boy != last_boy) {
                while (index < k && pairs[index].first == boy) {
                    --cnt_girls[pairs[index].second];
                    --total;
                    ++index;
                }
                last_boy = boy;
            }
            ans += total - cnt_girls[girl];
        }
        out << ans << std::endl;
	}


	CBalVBerlyandii() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
