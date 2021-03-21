#include "base/header.hpp"

class EArturIVoprosi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;
        std::vector<bool> unknown(n, false);
        std::vector<ll> a(n);
        for (int i : range(n)) {
            std::string s;
            in >> s;
            if (s == "?") {
                unknown[i] = true;
                a[i] = 0;
                continue;
            }
            a[i] = std::stoll(s);
        }

        auto is_question = [&unknown](const int index) {
            return index >= 0 && index < unknown.size() && unknown[index];
        };

        auto fail = [&out]() {
            out << "Incorrect sequence" << std::endl;
        };

        for (int i : range(k)) {
            std::vector<pii> values;
            values.emplace_back(-1, -LINF);
            for (int j = i; j < n; j += k) {
                values.emplace_back(j, a[j]);
            }
            values.emplace_back(n + 1, LINF);
            debug(values);
            int index = 0;
            while (index < values.size() - 1) {
                int end = index + 1;
                while (end < values.size() && is_question(values[end].first)) {
                    ++end;
                }

                const int min = values[index].second;
                const int max = values[end].second;
                const int cnt = end - index - 1;

                if (min + cnt >= max) {
                    fail();
                    return;
                }

                if (max <= 0) {
                    int cur = max;
                    for (int i : inclusiveDownrange(end - 1, index + 1)) {
                        --cur;
                        a[values[i].first] = cur;
                    }
                }
                else if (min >= 0) {
                    int cur = min;
                    for (int i : inclusiveRange(index + 1, end - 1)) {
                        ++cur;
                        a[values[i].first] = cur;
                    }
                } else {
                    int cur = std::min(max - cnt, std::max(min + 1, -cnt / 2)) - 1;
                    for (int i : inclusiveRange(index + 1, end - 1)) {
                        ++cur;
                        a[values[i].first] = cur;
                    }
                }

                index = end;
            }
        }

        debug(a);
        ll sum = std::accumulate(a.begin(), a.begin() + k - 1, 0LL);
        ll prev_sum = -LINF;
        for (int i : range(k - 1, n)) {
            sum += a[i];
            if (sum <= prev_sum) {
                fail();
                return;
            }
            prev_sum = sum;
            sum -= a[i - k + 1];
        }

        for (int x : a) {
            out << x << " ";
        }
        out << std::endl;
	}


	EArturIVoprosi() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    if (out.str() == "Incorrect sequence\n") {
	        debug("FAIL solution exists");
	        return false;
	    }
	    int n, k;
	    in >> n >> k;
        std::vector<bool> unknown(n, false);
        std::vector<ll> a(n);
        for (int i : range(n)) {
            std::string s;
            in >> s;
            if (s == "?") {
                unknown[i] = true;
                a[i] = 0;
                continue;
            }
            a[i] = std::stoll(s);
        }

        std::vector<ll> pans(n);
        out >> pans;

        for (int i : range(n)) {
            if (!unknown[i] && a[i] != pans[i]) {
                debug("WTF diff", i, a[i], pans[i]);
                return false;
            }
        }

        ll sum = std::accumulate(pans.begin(), pans.begin() + k - 1, 0LL);
        ll prev_sum = -LINF;
        for (int i : range(k - 1, n)) {
            sum += pans[i];
            if (sum <= prev_sum) {
                debug("FAIL", sum, prev_sum);
                return false;
            }
            prev_sum = sum;
            sum -= pans[i - k + 1];
        }
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
	    const int kMaxN = 10;
	    const int kMaxK = 100;

	    const int kMaxStartingValue = 10;
	    const int kMaxDelta = 10;

	    const int kQuestionProbability = 5;

	    const int n = Random::get(1, kMaxN);
	    const int k = Random::get(1, std::min(n, kMaxK));
	    test << n << " " << k << std::endl;
	    int value = Random::get(0, kMaxStartingValue) * (Random::get(0, 1) == 0 ? -1 : 1);
	    std::vector<ll> values;
	    for (int i : range(n)) {
	        values.emplace_back(value);
	        if (Random::get(0, kQuestionProbability - 1) == 0) {
	            test << "? ";
	        } else {
	            test << value << " ";
	        }
	        value += Random::get(1, kMaxDelta);
	    }
	    test << std::endl;
	    for (ll x : values) {
	        test << x << " ";
	    }
	    test << std::endl;
	}

};
