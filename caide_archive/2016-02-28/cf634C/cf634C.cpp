#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

template<typename T>
class SegmentTreeSum {
public:

	/* enum Type {
	NONE,
	INCREMENT, // Increment updates on a segment.

	}; */

	SegmentTreeSum(const int P, const size_t N, const T& neutral_ = static_cast<T>(0)) : P_(P), N_(N), neutral_(neutral_) {
		offset_ = 1 << (31 - clz(N) + ((N & (N - 1)) == 0 ? 0 : 1));
		size_ = offset_ << 1;
		data_.resize(size_);
		init();
	}

	SegmentTreeSum() = delete;

	SegmentTreeSum(SegmentTreeSum&) = default;
	SegmentTreeSum(SegmentTreeSum&&) = default;

	SegmentTreeSum& operator =(SegmentTreeSum&) = default;
	SegmentTreeSum& operator =(SegmentTreeSum&&) = default;

	~SegmentTreeSum() = default;

	constexpr size_t offset() const {
		return offset_;
	}

	constexpr size_t size() const {
		return size_;
	}

	constexpr size_t elements_count() const {
		return N_;
	}

	constexpr T neutral() const {
		return neutral_;
	}

	std::vector<T>& data() const {
		return data_;
	}

	void init() {
		std::fill_n(data_.begin(), data_.size(), neutral_);
	}

	void build(T a[]) {
		std::copy(a, a + N_, data_.begin() + offset_);
		for (size_t i = offset_ - 1; i >= 1; --i) {
			data_[i] = data_[i << 1] + data_[(i << 1) ^ 1];
		}
	}

	T query(const size_t left, const size_t right) const {
		T res = neutral_;
		for (size_t l = left + offset_, r = right + offset_; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) {
				res += data_[l++];
			}
			if ((r & 1) == 0) {
				res += data_[r--];
			}
		}
		return res;
	}

	void update(const size_t position, const T& value) {
		size_t pos = position + offset_;
		data_[pos] += value;
		umin(data_[pos], P_);
		for (pos >>= 1; pos >= 1; pos >>= 1) {
			data_[pos] = data_[pos << 1] + data_[(pos << 1) ^ 1];
		}
	}

private:
	int P_;
	std::vector<T> data_;
	const T neutral_;
	size_t offset_;
	size_t size_;
	size_t N_;

};


void solve(istream& ins, ostream& out) {
	int n, k, a, b;
	io >> n >> k >> a >> b >> __;
	SegmentTreeSum<int> tree_a(a, n), tree_b(b, n);
	for (int _ = 0; _ < __; ++_) {
		int type, day;
		io >> type >> day;
		if (type == 1) {
			int cnt;
			io >> cnt;
			tree_a.update(day - 1, cnt);
			tree_b.update(day - 1, cnt);
		}
		else {
			int ans = tree_b.query(0, day - 2);
			ans += tree_a.query(day + k - 1, n - 1);
			io << ans << endl;
		}
	}
}
