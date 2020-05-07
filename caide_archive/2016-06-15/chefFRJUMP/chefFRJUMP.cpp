#include "base/header.hpp"
#include "maths.hpp"
#include "mod_int.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1111;

struct Result {
	long double exact, value;
	ModInt<int> rem;
	bool exact_fail;

	Result() : Result(1) {}
	Result(const int v) : exact(v), value(v), rem(v), exact_fail(false) {}

	void operator *= (const int rhs) {
		exact *= rhs;
		value *= rhs;
		rem *= rhs;
		normalize();
	}

	void operator /= (const int rhs) {
		rem *= ModInt<int>(rhs).inverse();
		while (exact < rhs) {
			exact *= 10;
		}
		exact /= rhs;
		while (value < rhs) {
			value *= 10;
		}
		value /= rhs;
	}

	void normalize() {
		while (exact >= 10000000000LL) {
			exact /= 10;
			exact_fail = true;
		}
		while (value >= 10) {
			value /= 10;
		}
	}

	int get_first_digit() const {
		ll tmp = static_cast<ll>(exact_fail ? value : exact);
		while (tmp >= 10) {
			tmp /= 10;
		}
		return tmp;
	}

};

const size_t MAXK = 5000;

void solve(std::istream& in, std::ostream& out) {
	size_t n;
	in >> n;
	vector<ll> a(n);
	in >> a >> __;
	vector<Result> res(n + 1);
	vector<vector<int>> divs(n + 1);
	for (int i = 1; i <= std::min(MAXK, n); ++i) {
		for (int j = i; j <= n; j += i) {
			divs[j].emplace_back(i);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j < n; j += i) {
			res[i] *= a[j];
		}
	}
	for (int _ = 0; _ < __; ++_) { 
		int type;
		in >> type;
		if (type == 1) {
			int index, value;
			in >> index >> value;
			--index;
			if (index != 0) {
				for (const auto& div : divs[index]) {
					res[div] /= a[index];
					res[div] *= value;
				}
			}
			a[index] = value;
			continue;
		}
		int value;
		in >> value;
		Result tmp = res[value];
		if (value >= MAXK) {
			tmp = Result(1);
			for (int i = value; i < n; i += value) {
				tmp *= a[i];
			}
		}
		tmp *= a.front();
		out << tmp.get_first_digit() << " " << tmp.rem << endl;
	}
}
