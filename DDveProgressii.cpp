#include "base/header.hpp"

class DDveProgressii {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        if (a.size() == 2) {
            out << a.front() << std::endl;
            out << a.back() << std::endl;
            return;
        }

        std::vector<std::vector<int>> ans(2);
        auto check = [&ans](std::vector<int> x, std::vector<int> y, const std::vector<int>& a) {
            const int placed = x.size() + y.size();
            if (x.size() < y.size()) {
                x.swap(y);
            }
            for (int i : range<int>(placed, a.size())) {
                bool placed = false;
                if (a[i] - x.back() == x[1] - x[0]) {
                    if (!y.empty() && x.back() == y.back()) {
                        y.pop_back();
                    }
                    x.emplace_back(a[i]);
                    placed = true;
                }
                if (y.size() < 2 || y[1] - y[0] == a[i] - y.back()) {
                    if (!y.empty() && x.back() == y.back()) {
                        if (y.size() == 1) {
                            y.pop_back();
                        } else {
                            x.pop_back();
                        }
                    }
                    y.emplace_back(a[i]);
                    placed = true;
                }
                if (!placed) {
                    if (y.size() == 2 && y.back() == x.back()) {
                        y.pop_back();
                        y.emplace_back(a[i]);
                        continue;
                    }
                    debug(x, y);
                    return false;
                }
            }
            if (y.empty()) {
                y = {x.back()};
                x.pop_back();
            }
            if (x.back() == y.back()) {
                x.pop_back();
            }
            ans = {x, y};
            return true;
        };

        if (check({a[0], a[1]}, {}, a) || check({a[0], a[2]}, {a[1]}, a) || check({a[0]}, {a[1], a[2]}, a)) {
            for (const auto& row : ans) {
                for (int x : row) {
                    out << x << " ";
                }
                out << std::endl;
            }
            return;
        }
        out << "No solution" << std::endl;
	}


	DDveProgressii() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    auto parse_string = [](std::istringstream& in) {
	        std::string s;
	        std::getline(in, s);
	        std::istringstream integers(s);
	        std::vector<int> a;
	        int x;
	        while (integers >> x) {
	            a.emplace_back(x);
	        }
	        return a;
	    };

	    auto check_sequence = [](const std::vector<int>& a) {
	        if (a.empty()) {
	            return false;
	        }
	        if (a.size() == 1) {
	            return true;
	        }
	        for (int i : range<int>(2, a.size())) {
	            if (a[i] - a[i - 1] != a[1] - a[0]) {
	                return false;
	            }
	        }
	        return true;
	    };

	    if (out.str() == "No solution\n") {
	        debug("WA jury has solution");
	        return false;
	    }

	    int n;
	    in >> n;
	    std::vector<int> a(n);
	    in >> a;

	    auto px = parse_string(out);
	    auto py = parse_string(out);
        if (!check_sequence(px)) {
            debug("WA incorrect", px);
            return false;
        }
        if (!check_sequence(py)) {
            debug("WA incorrect", py);
            return false;
        }

        int ix = 0, iy = 0;
        for (int i : range(n)) {
            if (ix < px.size() && a[i] == px[ix]) {
                ++ix;
                continue;
            }
            if (iy < py.size() && a[i] == py[iy]) {
                ++iy;
                continue;
            }
            debug("WA where is number?", a[i]);
            return false;
        }
        if (ix < px.size() || iy < py.size()) {
            debug("WA extra numbers", ix, px, iy, py);
            return false;
        }

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
	    const int kMaxn = 5;
	    const int kMaxValue = 10;

	    auto gen = [kMaxn, kMaxValue]() {
            const int n = Random::get(1, kMaxn);
            const int starting = Random::get(-kMaxValue, kMaxValue);
            const int delta = Random::get(1, kMaxValue) * (Random::get(0, 1) == 0 ? -1 : 1);
            std::vector<int> a = {starting};
            for (int i : range(1, n)) {
                a.emplace_back(a.back() + delta);
            }
            return a;
	    };

	    auto a = gen();
	    auto b = gen();

	    auto aa = a, bb = b;

	    reverse(a);
	    reverse(b);

	    std::vector<int> sequence;
	    while (!a.empty() || !b.empty()) {
	        if (a.empty()) {
	            sequence.emplace_back(b.back());
	            b.pop_back();
	            continue;
	        }
	        if (b.empty()) {
	            sequence.emplace_back(a.back());
	            a.pop_back();
                continue;
	        }
	        if (Random::get(1, 2) == 1) {
	            sequence.emplace_back(a.back());
	            a.pop_back();
	        } else {
	            sequence.emplace_back(b.back());
	            b.pop_back();
	        }
	    }
	    test << sequence.size() << std::endl;
	    for (int x : sequence) {
	        test << x << " ";
	    }
	    test << std::endl;

	    for (int x : aa) {
	        test << x << " ";
	    }
	    test << std::endl;
	    for (int x : bb) {
	        test << x << " ";
	    }
	    test << std::endl;
	}

};
