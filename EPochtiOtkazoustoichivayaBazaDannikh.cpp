#include "base/header.hpp"
#include "maths/bits.hpp"

class EPochtiOtkazoustoichivayaBazaDannikh {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

    int find_differences(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& diffs) {
        diffs.clear();
        for (int i : range(a.size())) {
            if (a[i] != b[i]) {
                diffs.emplace_back(i);
            }
        }
        return diffs.size();
    };

	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        auto a = make_vector<int>(n, m, 0);
        in >> a;

        int mx = 0;
        int best = 0;
        std::vector<int> diffs;
        for (int i : range(1, n)) {
            const int cur = find_differences(a.front(), a[i], diffs);
            if (cur > mx) {
                mx = cur;
                best = i;
            }
        }

        if (mx >= 5) {
            out << "No" << std::endl;
            return;
        }

        auto answer = [&out](const std::vector<int>& tmp) {
            out << "Yes" << std::endl;
            for (int x : tmp) {
                out << x << " ";
            }
            out << std::endl;
        };

        find_differences(a.front(), a[best], diffs);
        debug(mx, best, diffs);
        const int k = diffs.size();
        auto diffs_id = diffs;
        for (int mask : range(1 << k)) {
            if (popcount(mask) > 2) {
                continue;
            }
            std::vector<int> tmp = a.front();
            for (int i : range(k)) {
                if (mask & (1 << i)) {
                    tmp[diffs_id[i]] = a[best][diffs_id[i]];
                }
            }
            if (mask == 3) {
                debug(tmp);
            }

            bool ok = true;
            for (int i : range(n)) {
                ok &= (find_differences(tmp, a[i], diffs) <= 2);
            }
            if (ok) {
                answer(tmp);
                return;
            }
        }

        if (mx == 3) {
            for (int stay_id : range(3)) {
                debug(stay_id);
                const int change_id = diffs_id[stay_id];
                for (int mode : range(2)) {
                    auto tmp = a.front();

                    std::vector<int> changes;
                    for (int i : range(3)) {
                        if (i != stay_id) {
                            changes.emplace_back(diffs_id[i]);
                        }
                    }
                    tmp[changes[1 - mode]] = a[best][changes[1 - mode]];
                    if (stay_id == 1) {
                        debug(stay_id, tmp);
                    }

                    bool ok = true;
                    bool change_allowed = true;
                    for (int i : range(1, n)) {
                        const int diff_cnt = find_differences(tmp, a[i], diffs);
                        debug(i, diff_cnt, change_allowed);
                        if (diff_cnt == 4) {
                            ok = false;
                            break;
                        }
                        if (diff_cnt == 2) {
                            if (tmp[change_id] == a[i][change_id] && i != best) {
                                change_allowed = false;
                            }
                            continue;
                        }
                        if (diff_cnt == 3) {
                            if (!change_allowed || tmp[change_id] == a[i][change_id]) {
                                ok = false;
                                break;
                            }
                            change_allowed = false;
                            tmp[change_id] = a[i][change_id];
                            debug(tmp);
                        }
                    }
                    if (ok) {
                        answer(tmp);
                        return;
                    }
                }
            }
        }

        out << "No" << std::endl;
	}


	EPochtiOtkazoustoichivayaBazaDannikh() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    int n, m;
	    in >> n >> m;
	    auto a = make_vector<int>(n, m, 0);
	    in >> a;

        std::string jans, pans;

        std::istringstream& read_ans = (jury.str().empty() ? in : jury);
        read_ans >> jans;
        out >> pans;

        if (pans == "No") {
            if (jans != pans) {
                debug("WA", jans, pans);
                return false;
            }
            return true;
        }

        std::vector<int> pvec(m);
        out >> pvec;

        std::vector<int> diffs;
        for (int i : range(n)) {
            if (find_differences(a[i], pvec, diffs) > 2) {
                debug("WA", pvec, a[i]);
                return false;
            }
        }

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
        const int kMaxn = 10;
        const int kMaxm = 10;
        const int kMaxValue = 100;

        const int n = Random::get(1, kMaxn);
        const int m = Random::get(1, kMaxm);
        auto a = make_vector<int>(n, m, 0);
        for (int i : range(m)) {
            a.front()[i] = Random::get(1, kMaxValue);
        }

        auto tmp = a.front();

        for (int i : range( n)) {
            const int diffs_count = Random::get(0, 2);
            a[i] = tmp;
            for (int j : range(diffs_count)) {
                const int pos = Random::get(0, m - 1);
                a[i][pos] = Random::get(1, kMaxValue);
            }
        }

        test << n << " " << m << std::endl;
        for (int i : range(n)) {
            for (int j : range(m)) {
                test << a[i][j] << " ";
            }
            test << std::endl;
        }
        test << std::endl << "Yes" << std::endl;
        for (int x : tmp) {
            test << x << " ";
        }
        test << std::endl;
	}

};
