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

#define ll long long

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
class Matrix {
public:
	using RowStorage = std::vector<T>;
	using DataStorage = std::vector<RowStorage>;

	Matrix(const size_t rows_cnt, const size_t cols_cnt, const T mod = 1000000007) :
		rows_cnt_(rows_cnt), cols_cnt_(cols_cnt),
		data_(rows_cnt, RowStorage(cols_cnt, 0)),
		mod_(mod) {}

	Matrix() = delete;

	RowStorage& operator[] (const size_t index) {
		return data_[index];
	}

	const RowStorage& operator[] (const size_t index) const {
		return data_[index];
	}

	Matrix operator *(const Matrix& rhs) const {
		Matrix result(rows_cnt_, rhs.cols_cnt_);
		for (size_t i = 0; i < rows_cnt_; i++) {
			for (size_t k = 0; k < rhs.cols_cnt_; k++) {
				for (size_t j = 0; j < rhs.rows_cnt_; j++) {
					result[i][k] += data_[i][j] * rhs[j][k];
				}
			}
		}
		return result;
	}

	Matrix& operator *=(const Matrix& rhs) {
		Matrix result = operator *(rhs);
		swap(result);
		return *this;
	}

	template<typename U>
	Matrix binpow(U b) const {
		static_assert(std::is_integral<U>::value, "Degree must be integral. For real degree use pow.");
		Matrix ret = identity_matrix(rows_cnt_, cols_cnt_);
		Matrix a = *this;
		while (b != 0) {
			if ((b & 1) != 0) {
				ret *= a;
			}
			a *= a;
			b >>= 1;
		}
		return ret;
	}

	void swap(Matrix& rhs) {
		data_.swap(rhs.data_);
		std::swap(mod_, rhs.mod_);
		std::swap(rows_cnt_, rhs.rows_cnt_);
		std::swap(cols_cnt_, rhs.cols_cnt_);
	}

	static Matrix identity_matrix(const size_t rows_cnt, const size_t cols_cnt) {
		Matrix result(rows_cnt, cols_cnt);
		for (size_t i = 0; i < std::min(rows_cnt, cols_cnt); ++i) {
			result[i][i] = 1;
		}
		return result;
	}

private:
	size_t rows_cnt_;
	size_t cols_cnt_;
	T mod_;

	DataStorage data_;
};

constexpr const int BASE_MOD = 1000000007;  /// caide keep

template<typename T>
inline T& add_mod(T& a, const T b, const T mod = BASE_MOD) {
	if ((a += b) >= mod) {
		a -= mod;
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

	ModInt operator *(const ModInt rhs) const {
		T x = value_;
		return{ mul_mod(x, rhs.value_, MOD) };
	}

	ModInt& operator +=(const ModInt rhs) {
		add_mod(value_, rhs.value_, MOD);
		return *this;
	}

	friend std::ostream& operator <<(std::ostream& out, const ModInt& rhs) {
		out << rhs.value_;
		return out;
	}

private:
	T value_;

};

using namespace std;

inline int pc(ll x) {
	int res = 0;
	while (x > 0) {
		res += (x & 1);
		x >>= 1;
	}
	return res;
}

void solve(std::istream& in, std::ostream& out) {
	int n;
	ll m;
	in >> n >> m;
	vector<ll> a(n);
	in >> a;
	Matrix<ModInt<int>> g(n, n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (pc(a[i] ^ a[j]) % 3 == 0) {
				g[i][j] = 1;
			}
		}
	}
	auto b = g.binpow(m - 1);
	ModInt<int> ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			ans += b[i][j];
		}
	}
	out << ans << endl;
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

