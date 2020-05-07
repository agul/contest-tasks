#pragma comment(linker, "/STACK:66777216")
#pragma warning(disable : 4996)

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#pragma hdrstop

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

#ifdef _MSC_VER

#endif

template<typename T, size_t N>
struct MakeVector {
	
};

template<typename T>
struct MakeVector<T, 1> {
	/// caide keep
	template<typename R = std::vector<T>>
	static R make_vector(std::size_t size, const T& value) {
		return R(size, value);
	}
};

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

namespace std {

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& vec) {
	for (auto& it : vec) {
		in >> it;
	}
	return in;
}

}

#include <iterator>

template<typename T>
class IntegerIterator : public std::iterator<std::input_iterator_tag, T, std::ptrdiff_t, T*, T> {
public:
	using value_type = T;

	constexpr explicit IntegerIterator(const value_type value) : value_(value) {}

	IntegerIterator& operator++() {
		++value_;
		return *this;
	}

	constexpr value_type operator*() const {
		return value_;
	}

	constexpr bool operator ==(const IntegerIterator rhs) const {
		return value_ == rhs.value_;
	}

	constexpr bool operator !=(const IntegerIterator rhs) const {
		return !(*this == rhs);
	}

private:
	value_type value_;

};

template<typename T>
class IntegerRange {
public:
	using const_iterator = IntegerIterator<T>;

	constexpr IntegerRange(const T begin, const T end) : begin_(begin), end_(end) {}

	constexpr const_iterator begin() const {
		return const_iterator(begin_);
	}

	constexpr const_iterator end() const {
		return const_iterator(end_);
	}

private:
	T begin_;
	T end_;

};

template<typename T>
constexpr IntegerRange<T> range(const T to) {
	return IntegerRange<T>(0, to);
}

template<typename R>
void reverse(R& range) {
	std::reverse(range.begin(), range.end());
}

template<typename R>
R reversed(R range) {
	reverse(range);
	return range;
}

template<typename T>
class Polynom : public std::vector<T> {
public:
	using size_type = typename std::vector<T>::size_type;

	Polynom() : Polynom(0) {}

	explicit Polynom(const size_type degree) : std::vector<T>(degree + 1) {}

	constexpr size_type degree() const {
		return this->size() - 1;
	}

	Polynom add(const Polynom& rhs) const {
		Polynom res(std::max(rhs.degree(), degree()));
		std::copy(this->begin(), this->end(), res.begin());
		for (size_t i = 0; i < rhs.size(); ++i) {
			res[i] += rhs[i];
		}
		res.normalize();
		return res;
	}

	Polynom subtract(const Polynom& rhs) const {
		return add(rhs.negate());
	}

	Polynom operator -(const Polynom& rhs) const {
		return subtract(rhs);
	}

	Polynom& operator -=(const Polynom& rhs) {
		Polynom res = subtract(rhs);
		this->swap(res);
		return *this;
	}

	static Polynom one() {
		Polynom res;
		res.front() = 1;
		return res;
	}

	Polynom negate() const {
		Polynom res = *this;
		for (auto& it : res) {
			it = -it;
		}
		return res;
	}

	void reverse() {
		std::reverse(this->begin(), this->end());
	}

	void normalize() {
		while (this->size() > 1 && this->back() == T(0)) {
			this->pop_back();
		}
	}
};

template<typename T, typename U>
inline T binpow(T a, U b) {
	static_assert(std::is_integral<U>::value, "Degree must be integral. For real degree use pow.");
	T ret = 1;
	while (b != 0) {
		if ((b & 1) != 0) {
			ret *= a;
		}
		a *= a;
		b >>= 1;
	}
	return ret;
}

template<typename T, typename U, typename Q>
inline T binpow(T a, U b, Q mod) {
	static_assert(std::is_integral<U>::value, "Degree must be integral. For real degree use pow.");
	long long ret = 1;
	a %= mod;
	while (b != 0) {
		if ((b & 1) != 0) {
			ret = ret * a % mod;
		}
		a = a * a % mod;
		b >>= 1;
	}
	return ret % mod;
}

template<typename T, typename U>
T inverse_element(const T n, const U mod)
// inverse element for prime mod
{
	return binpow(static_cast<long long>(n), mod - 2, mod);
}

constexpr const int BASE_MOD = 1000000007;  /// caide keep

template<typename T>
inline T& add_mod(T& a, const T b, const T mod = BASE_MOD) {
	if ((a += b) >= mod) {
		a -= mod;
	}
	return a;
}

template<typename T>
inline T& sub_mod(T& a, const T b, const T mod = BASE_MOD) {
	if ((a -= b) < 0) {
		a += mod;
	}
	return a;
}

template<typename T>
inline T& mul_mod(T& a, const T b, const T mod = BASE_MOD) {
	a = static_cast<long long>(a) * b % mod;
	return a;
}

template<typename T, T MOD = BASE_MOD>
class ModInt {
public:

	/// caide keep
	constexpr ModInt() : ModInt(0) {}

	constexpr ModInt(const T value) : value_(value) {
		static_assert(MOD > 0, "Modulo must be strictly positive.");
		// static_assert((std::equal<T, int32_t> && mod <= 0x3f3f3f3f) || (std::equal<T, int64_t> && mod <= 0x3f3f3f3f3f3f3f3fLL), "Modulo must be less than half of the max value for typename.");
	}

	template<typename U>
	constexpr static ModInt from_integer(const U value) {
		return{ ModInt::normalize(value) };
	}

	constexpr bool operator ==(const ModInt rhs) const {
		return value_ == rhs.value_;
	}

	ModInt operator +(const ModInt rhs) const {
		T x = value_;
		return{ add_mod(x, rhs.value_, MOD) };
	}

	ModInt operator -(const ModInt rhs) const {
		T x = value_;
		return{ sub_mod(x, rhs.value_, MOD) };
	}

	ModInt operator *(const ModInt rhs) const {
		T x = value_;
		return{ mul_mod(x, rhs.value_, MOD) };
	}

	ModInt& operator +=(const ModInt rhs) {
		add_mod(value_, rhs.value_, MOD);
		return *this;
	}

	ModInt& operator -=(const ModInt rhs) {
		sub_mod(value_, rhs.value_, MOD);
		return *this;
	}

	ModInt& operator *=(const ModInt rhs) {
		mul_mod(value_, rhs.value_, MOD);
		return *this;
	}

	constexpr ModInt operator -() const {
		return negate();
	}

	constexpr ModInt negate() const {
		return{ normalize(-value_) };
	}

	constexpr ModInt inverse() const {
		return{ inverse_element(value_, MOD) };
	}

	friend std::istream& operator >>(std::istream& in, ModInt& rhs) {
		T x;
		in >> x;
		rhs.value_ = rhs.normalize(x);
		return in;
	}

	friend std::ostream& operator <<(std::ostream& out, const ModInt& rhs) {
		out << rhs.value_;
		return out;
	}

private:
	T value_;

	template<typename U>
	static T normalize(const U value) {
		if (value >= 0 && value < MOD) {
			return value;
		}
		const T ret = value % MOD;
		if (ret < 0) {
			return ret + MOD;
		}
		return ret;
	}

};

using namespace std;

const int MAXN = 1 << 18;

const int mod = 786433;
const int root = 5;
const int root_inverse = 471860;

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

#include <fstream>

int main() {
    srand(time(NULL));
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;

    ostream& out = cout;

    out << fixed << setprecision(16);
    solve(in, out);
    return 0;
}

