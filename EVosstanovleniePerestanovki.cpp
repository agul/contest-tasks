#include "base/header.hpp"

class EVosstanovleniePerestanovki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        std::vector<int> id(n);
        std::iota(all(id), 1);


        std::vector<int> min(n);
        {
            std::set<int> not_used(all(id));
            int prev = -1;
            for (int i : range(n)) {
                if (a[i] != prev) {
                    min[i] = a[i];
                    not_used.erase(a[i]);
                    prev = a[i];
                    continue;
                }
                min[i] = *not_used.begin();
                not_used.erase(not_used.begin());
            }
        }

        std::vector<int> max(n);
        {
            std::set<int> not_used(all(id));
            std::set<int, std::greater<>> possible;
            int prev = -1;
            for (int i : range(n)) {
                if (a[i] != prev) {
                    max[i] = a[i];
                    not_used.erase(a[i]);
                    prev = a[i];
                    while (!not_used.empty() && *not_used.begin() < a[i]) {
                        const int x = *not_used.begin();
                        possible.emplace(x);
                        not_used.erase(x);
                    }
                    continue;
                }
                max[i] = *possible.begin();
                possible.erase(possible.begin());
            }
        }

        for (int x : min) {
            out << x << " ";
        }
        out << std::endl;
        for (int x : max) {
            out << x << " ";
        }
        out << std::endl;
	}


	EVosstanovleniePerestanovki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
