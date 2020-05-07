#pragma comment(linker, "/STACK:66777216")
#include <cstdio>
#pragma warning(disable : 4996)
#include <algorithm>
#include <array>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <utility>
#include <functional>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <queue>
#include <cmath>
#include <random>
#include <sstream>
#include <numeric>
#include <limits>
#include <chrono>
#include <type_traits>
#pragma hdrstop

// using namespace std;

#ifdef _MSC_VER
#include <intrin.h>
#define clz(a) __clz(a)
#else
#define LLD "%lld"
#define LLU "%llu"
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif


#define ll int64_t


namespace std {


}

#ifdef _MSC_VER
static uint32_t __inline __clz(uint32_t x) {
	unsigned long r = 0;
	_BitScanReverse(&r, x);
	return (31 - r);
}

#endif


namespace Random {


}


extern bool useFastIO;
extern std::istream * pin;
extern std::ostream * pout;


//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


template<typename T> 
class SegmentTree {
public:

	std::vector<T> data;

	SegmentTree(const size_t N, const std::function<const T(const T&, const T&)>& pred, const T& neutral_ = static_cast<T>(0)) : N_(N), pred_(pred), neutral_(neutral_) {
		offset_ = 1 << (31 - clz(N) + ((N & (N - 1)) == 0 ? 0 : 1));
		size_ = offset_ << 1;
		data.resize(size_);
		init();
	}

	SegmentTree() = delete;

	SegmentTree(SegmentTree&) = default;
	SegmentTree(SegmentTree&&) = default;

	SegmentTree& operator =(SegmentTree&) = default;
	SegmentTree& operator =(SegmentTree&&) = default;

	~SegmentTree() = default;


	void init() {
		std::fill_n(data.begin(), data.size(), neutral_);
	}

	void build(T a[]) {
		std::copy(a, a + N_, data.begin() + offset_);
		for (size_t i = offset_ - 1; i >= 1; --i) {
			data[i] = pred_(data[i << 1], data[(i << 1) ^ 1]);
		}
	}

	T query(const size_t left, const size_t right) const {
		T res = neutral_;
		for (size_t l = left + offset_, r = right + offset_; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) {
				res = pred_(data[l++], res);
			}
			if ((r & 1) == 0) {
				res = pred_(data[r--], res);
			}
		}
		return res;
	}


private:
	const std::function<const T(const T&, const T&)> pred_;
	const T neutral_;
	size_t offset_;
	size_t size_;
	size_t N_;

};


void suffixLCPArrayCyclic(int sa[], int lcp[], const char * s, const int n, const int alphabet = 27);


using namespace std;

const int MAXN = 255555;

int lcp[MAXN], p[MAXN];
char s[MAXN];

void solve(istream& ins, ostream& out) {
	int n;
	ins >> n >> s;
	for (int i = 0; i < n; ++i) {
		s[i] -= 'A';
	}
	suffixLCPArrayCyclic(p, lcp, s, n, 26);
	ll ans = 0;
	for (int i = 0; i < n - 1; ++i) {
		ans += lcp[i];
	}
	out << fixed << setprecision(3) << ans / (n - 1.) << endl;
}
#include <fstream>


bool useFastIO = false;
istream * pin;
ostream * pout;

int main() {
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;
    useFastIO = true;

    ostream& out = cout;
    out << fixed << setprecision(16);
    pin = &in; pout = &out;
    solve(in, out);
    return 0;
}


void suffixLCPArrayCyclic(int sa[], int lcp[], const char * s, const int n, const int alphabet)
// building suffix and LCP array for cyclic shifts, O(n log^2 n)
// to prevent using cyclic shifts consider n = n + 1; s[n] = 0;
{
	int *cnt, *c[2], *pn, *lpos, *rpos, *la[2], * indices, * arr;
	auto comparator = [&arr](const int& x, const int& y) {
		if (x == -1) {
			return y;
		}
		return (y == -1 || arr[x] < arr[y] ? x : y);
	};
	static SegmentTree<int> tree(n, comparator, -1);
	cnt = new int[std::max(255, n)];
	pn = new int[n];
	lpos = new int[n];
	rpos = new int[n];
	indices = new int[n];
	for (int i = 0; i < n; ++i) {
		indices[i] = i;
	}
	std::fill_n(lpos, n, 0);
	std::fill_n(rpos, n, 0);
	for (int i = 0; i < 2; ++i) {
		c[i] = new int[n];
		la[i] = new int[n];
		std::fill_n(la[i], n, 0);
	}
	std::fill_n(cnt, alphabet, 0);
	for (int i = 0; i < n; ++i) {
		++cnt[s[i]];
	}
	for (int i = 1; i < alphabet; ++i) {
		cnt[i] += cnt[i - 1];
	}
	for (int i = 0; i < n; ++i) {
		sa[--cnt[s[i]]] = i;
	}
	c[0][sa[0]] = 0;
	int classes = 1;
	for (int i = 1; i < n; ++i) {
		if (s[sa[i]] != s[sa[i - 1]]) {
			++classes;
		}
		c[0][sa[i]] = classes - 1;
	}
	int h, ci, ni;
	for (h = 0; (1 << h) <= n; ++h) {
		ci = h & 1, ni = ci ^ 1;
		for (int i = 0; i < n; ++i) {
			rpos[c[ci][sa[i]]] = i;
		}
		for (int i = n - 1; i >= 0; --i) {
			lpos[c[ci][sa[i]]] = i;
		}
		for (int i = 0; i < n; ++i) {
			pn[i] = sa[i] - (1 << h);
			if (pn[i] < 0) {
				pn[i] += n;
			}
		}
		std::fill_n(cnt, classes, 0);
		for (int i = 0; i < n; ++i) {
			++cnt[c[ci][pn[i]]];
		}
		for (int i = 1; i < classes; ++i) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = n - 1; i >= 0; --i) {
			sa[--cnt[c[ci][pn[i]]]] = pn[i];
		}
		c[ni][sa[0]] = 0;
		classes = 1;
		for (int i = 1; i < n; ++i) {
			int mid1 = (sa[i] + (1 << h)) % n, mid2 = (sa[i - 1] + (1 << h)) % n;
			if (c[ci][sa[i]] != c[ci][sa[i - 1]] || c[ci][mid1] != c[ci][mid2]) {
				++classes;
			}
			c[ni][sa[i]] = classes - 1;
		}
		arr = la[ci];
		tree.build(indices);
		for (int i = 0; i < n - 1; ++i) {
			int a = sa[i], b = sa[i + 1];
			if (c[ci][a] != c[ci][b]) {
				la[ni][i] = la[ci][rpos[c[ci][a]]];
			}
			else {
				int aa = (a + (1 << h)) % n, bb = (b + (1 << h)) % n;
				la[ni][i] = (1 << h) + la[ci][tree.query(lpos[c[ci][aa]], rpos[c[ci][bb]] - 1)];
				la[ni][i] = std::min(n, la[ni][i]);
			}
		}
	}
	for (int i = 0; i < n - 1; ++i) {
		lcp[i] = la[ni][i];
	}
	delete[] cnt;
	delete[] pn;
	delete[] lpos;
	delete[] rpos;
	delete[] indices;
	for (int i = 0; i < 2; ++i) {
		delete[] c[i];
		delete[] la[i];
	}
}
