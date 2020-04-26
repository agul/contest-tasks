#include "../algolib/cpplib/base/header.hpp"
#include "../algolib/cpplib/maths/maths.hpp"

class DXeniaIRaznotsvetnieKamushki {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int na, nb, nc;
			in >> na >> nb >> nc;

			auto a = make_vector<ll>(na, 0);
			auto b = make_vector<ll>(nb, 0);
			auto c = make_vector<ll>(nc, 0);
			in >> a >> b >> c;
			sort(a);
			sort(b);
			sort(c);

			std::vector<ll> ans_vec = {
				solution(a, b, c),
				solution(a, c, b),
				solution(b, a, c),
				solution(b, c, a),
				solution(c, a, b),
				solution(c, b, a)
			};
			const ll ans = *std::min_element(all(ans_vec));
			out << ans << std::endl;
		}
	}

	ll solution(const std::vector<ll>& a, const std::vector<ll>& b, const std::vector<ll>& c) const {
		ll ans = LINF;
		int min = 0;
		int mid = 0;
		int max = 0;

		auto check_loss = [this, &a, &b, &c, &ans](const int min, const int mid, const int max) {
			if (min < 0 || mid < 0 || max < 0 || min >= a.size() || mid >= b.size() || max >= c.size() || a[min] > b[mid] || b[mid] > c[max]) {
				return LINF;
			}
			const ll cur_loss = loss(a[min], b[mid], c[max]);
			umin(ans, cur_loss);
			return cur_loss;
		};

		for (int min : range(a.size())) {
			while (max < c.size() && c[max] < a[min]) {
				check_loss(min, mid, max);
				++max;
			}
			while (mid < b.size() && b[mid] < a[min]) {
				check_loss(min, mid, max);
				++mid;
			}

			const ll x = (a[min] + c[max]) / 2;
			while (mid + 1 < b.size() && b[mid + 1] < x) {
				check_loss(min, mid, max);
				++mid;
			}

			check_loss(min, mid - 1, max);
			check_loss(min, mid, max);
			check_loss(min, mid + 1, max);
		}

		return ans;
	}

	ll loss(const ll x, const ll y, const ll z) const {
		return sqr(x - y) + sqr(x - z) + sqr(y - z);
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
