#include "base/header.hpp"
#include "maths/polynom.hpp"
#include "maths/maths.hpp"
#include "maths/mod_int.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1 << 18;

const int mod = 786433;
const int root = 5;
const int root_inverse = 471860;
const int root_pw = 1 << 18;

using Num = ModInt<int, mod>;
using Poly = Polynom<Num>;

int init_m, log_table[MAXN];
Num ans[MAXN], wlen_pow[2][MAXN];
std::vector<Poly> M[20], M_fft[20], M_fast[20];

void fft(Poly& a, bool invert) {
	const size_t n = a.size();

	for (int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1) {
			j -= bit;
		}
		j += bit;
		if (i < j) {
			swap(a[i], a[j]);
		}
	}

	for (int len = 2; len <= n; len <<= 1) {
		const Num wlen = wlen_pow[invert][len];
		for (int i = 0; i < n; i += len) {
			Num w = 1;
			for (int j = 0; j<len / 2; ++j) {
				Num u = a[i + j];
				Num v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert) {
		Num nrev = Num(n).inverse();
		for (int i = 0; i < n; ++i) {
			a[i] *= nrev;
		}
	}
}

Poly input[2];

void multiply(const Poly& a, const Poly& b, Poly& res) {
	const int n = log_table[max(a.size(), b.size())];
	for (int w = 0; w < 2; ++w) {
		input[w].assign(n, 0);
	}
	std::copy(a.begin(), a.end(), input[0].begin());
	std::copy(b.begin(), b.end(), input[1].begin());
	for (int w = 0; w < 2; ++w) {
		fft(input[w], false);
	}
	res.resize(n);
	for (int i = 0; i < n; ++i) {
		res[i] = input[0][i] * input[1][i];
	}
	fft(res, true);
	res.normalize();
}

void fast_multiply(const Poly& a, const Poly& b, Poly& fft_res, Poly& res) {
	const int n = a.size();
	fft_res.resize(n);
	for (int i = 0; i < n; ++i) {
		fft_res[i] = a[i] * b[i];
	}
	res = fft_res;
	fft(res, true);
	res.normalize();
}

void extend_fft(Poly& a) {
	const size_t n = a.size();
	const size_t len = n * 2;
	a.resize(len);
	const Num wlen = wlen_pow[0][len];
	Num w = 1;
	for (int j = 0; j < n; ++j) {
		Num u = a[j];
		Num v = a[j + n] * w;
		a[j] = u + v;
		a[j + n] = u - v;
		w *= wlen;
	}
}

Poly inverse(const Poly& a, const size_t t) {
	if (t == 1) {
		return Poly::one();
	}
	Poly a0 = inverse(a, (t + 1) / 2);
	Poly tmp;
	multiply(a, a0, tmp);
	tmp.front() -= 1;
	multiply(tmp, a0, tmp);
	a0 -= tmp;
	a0.resize(t);
	return a0;
}

Poly get_remainder(const Poly& a, const Poly& b) {
	const int m = a.size();
	const int n = b.size();
	if (m < n) {
		return a;
	}
	const int sz = max(1, m - n + 1);
	Poly br_inv = inverse(reversed(b), sz);
	Poly d;
	multiply(reversed(a), br_inv, d);
	d.resize(sz);
	d.reverse();
	multiply(d, b, d);
	return a - d;
}

void calculate(const Poly& a, const int level, const int L, const int R) {
	if (L >= init_m) {
		return;
	}
	if (level == 0) {
		ans[L] = a.front();
		return;
	}
	const int new_L = L * 2;
	const int new_R = R * 2;
	Poly r0 = get_remainder(a, M[level - 1][L]);
	Poly r1 = get_remainder(a, M[level - 1][L + 1]);
	if (level == 1) {
		const int mid = (L + R) >> 1;
		calculate(r0, 0, L, mid);
		calculate(r1, 0, mid, R);
		return;
	}
	const int mid = (new_L + new_R) >> 1;
	calculate(r0, level - 1, new_L, mid);
	calculate(r1, level - 1, mid, new_R);
}

inline void precalc_log_table() {
	for (int i = 1; i < MAXN; ++i) {
		int& cur_pow = log_table[i];
		cur_pow = 1;
		while (cur_pow <= i) {
			cur_pow <<= 1;
		}
		cur_pow <<= 1;
	}
}

inline void precalc_wlen_pow() {
	for (int invert : range(2)) {
		const Num base = invert ? root_inverse : root;
		Num pow = base;
		for (int i = MAXN / 2; i >= 1; i >>= 1) {
			pow *= pow;
			wlen_pow[invert][i] = pow;
		}
	}
}

void solve(std::istream& in, std::ostream& out) {

	const int POW = 20;
	const int N = (1 << POW) + 1;
	for (int i = 2; i < N; ++i) {
		for (int j = 0; j <= 24; ++j) {
			ModInt<int, N> x = i;
			if (binpow(x, (1 << j)) == 1) {
				if (j >= POW) {
					out << i << " " << j << endl;
				}
				break;
			}
		}
	}
	cerr << ":(" << endl;
	return;

	precalc_log_table();
	precalc_wlen_pow();
	int n;
	in >> n;
	Poly a(n);
	in >> a >> init_m;
	vector<int> q(init_m);
	in >> q;
	while (q.size() <= n) {
		q.emplace_back(0);
	}
	int m = q.size();

	int deg = 1;
	int step = 0;
	while (deg < m) {
		deg <<= 1;
		++step;
	}

	for (int i : range(deg - m)) {
		q.emplace_back(0);
	}

	for (int i = 0; i <= step; ++i) {
		const int level_size = deg / (1 << i);
		M[i].resize(level_size);
		M_fft[i].resize(level_size);
		M_fast[i].resize(level_size);
		if (i > 0) {
			for (int j = 0; j < level_size; ++j) {
				multiply(M[i - 1][j << 1], M[i - 1][(j << 1) ^ 1], M[i][j]);
				fast_multiply(M_fft[i - 1][j << 1], M_fft[i - 1][(j << 1) ^ 1], M_fft[i][j], M_fast[i][j]);
				if (i > 1) {
					extend_fft(M_fft[i][j]);
				}




				const int need = log_table[M[i][j].size()];
				while (M[i][j].size() < need) {
					M[i][j].emplace_back(0);
				}
				fft(M[i][j], false);

				fft(M[i][j], true);
				if (M[i][j] != M_fast[i][j]) {
					cerr << i << " " << j << endl;
					const int need = log_table[M[i][j].size()];
					while (M[i][j].size() < need) {
						M[i][j].emplace_back(0);
					}
					fft(M[i][j], false);

					fft(M[i][j], true);
				}
			}
		}
		else {
			for (int j = 0; j < level_size; ++j) {
				Poly& cur = M[i][j];
				cur = Poly(1);
				cur.front() = Num::from_integer(-q[j]);
				cur.back() = 1;

				M_fast[i][j] = M[i][j];

				Poly& cur_fft = M_fft[i][j];
				cur_fft = cur;
				cur_fft.resize(8);
				fft(cur_fft, false);
			}
		}
	}

	calculate(a, step, 0, 2);

	for (int i : range(init_m)) {
		out << ans[i] << endl;
	}

}