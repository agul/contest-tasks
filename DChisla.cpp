#include "base/header.hpp"

class DChisla {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;
        std::multiset<int> values(all(a));

        int left = -INF;
        int right = INF;

        auto del = [&values](const int value) {
            const auto it = values.find(value);
            if (it == values.cend()) {
                return false;
            }
            values.erase(it);
            return true;
        };

        auto valid = [](const int a, const int b) {
            return std::abs(a - b) == 1;
        };

        auto put_left = [&del, &left, &right, &valid](const int value) {
            if (!del(value)) {
                return false;
            }
            if (left == -INF) {
                right = value;
            } else {
                // debug(left, value);
                // assert(valid(left, value));
            }
            left = value;
            return true;
        };

        auto put_right = [&del, &right, &left, &valid](const int value) {
            if (!del(value)) {
                return false;
            }
            if (right == INF) {
                left = value;
            } else {
                // assert(valid(right, value));
            }
            right = value;
            return true;
        };

        const int cur_min = *values.begin();
        if (values.count(cur_min + 1) < 2) {
            out << "NO" << std::endl;
            return;
        }
        put_left(cur_min);
        put_left(cur_min + 1);
        put_right(cur_min + 1);

        while (!values.empty()) {
            if (values.size() == 1) {
                const int last_value = *values.begin();
                if (!valid(last_value, left) || !valid(last_value, right)) {
                    out << "NO" << std::endl;
                    return;
                }
                put_left(last_value);
                continue;
            }

            const int cur_min = *values.begin();
            if (cur_min < left) {
                if (!put_left(cur_min) || !put_left(cur_min + 1)) {
                    out << "NO" << std::endl;
                    return;
                }
                continue;
            }
            if (cur_min == left) {
                if (!put_left(cur_min + 1) || !put_left(cur_min)) {
                    out << "NO" << std::endl;
                    return;
                }
                continue;
            }

            if (!valid(left, cur_min) || !put_left(cur_min) || !put_right(cur_min)) {
                out << "NO" << std::endl;
                return;
            }
        }
        if (!valid(left, right)) {
            out << "NO" << std::endl;
            return;
        }
        out << "YES" << std::endl;
	}


	DChisla() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
	    test << 100000 << std::endl;
	    for (int i : range(50000)) {
	        test << 1 << " " << 2 << " ";
	    }
	    test << std::endl;
	}

};
