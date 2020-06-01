#include "base/header.hpp"

class EGukiZIGukiZiana {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	template<typename T = int64_t>
	struct Block {
		static constexpr int kSize = 707;

		using pair_type = std::pair<T, int>;

		Block(std::vector<pair_type>& a, const size_t id) : a(a), id(id), updates(0) {
			left = begin();
			right = end();
			sort();
		}

		void sort() {
			std::sort(a.begin() + left, a.begin() + right + 1);
		}

		size_t begin() const {
			return id * kSize;
		}

		size_t end() const {
			return std::min(a.size(), (id + 1) * kSize) - 1;
		}

		int find_leftmost(const T value) const {
			const T lookup_value = value - updates;
			const auto it = std::lower_bound(a.cbegin() + left, a.cbegin() + right + 1, pair_type{lookup_value, -1});
			if (it == a.cbegin() + right + 1 || it->first != lookup_value) {
				return -1;
			}
			// debug(*it, it - a.begin(), value, updates, id);
			return it->second;
		}

		int find_rightmost(const T value) const {
			const T lookup_value = value - updates;
			const auto it = std::upper_bound(a.cbegin() + left, a.cbegin() + right + 1, pair_type{lookup_value, INF});
			if (it == a.cbegin() + left || std::prev(it)->first != lookup_value) {
				return -1;
			}
			return std::prev(it)->second;
		}

		void update(size_t from, size_t to, const T update) {
			from = std::max(from, left);
			to = std::min(to, right);
			if (from > to || update == 0) {
				return;
			}
			if (from <= left && to >= right) {
				updates += update;
				return;
			}
			for (size_t i : inclusiveRange(left, right)) {
				a[i].first += updates;
				if (from <= a[i].second && a[i].second <= to) {
					a[i].first += update;
				}
			}
			updates = 0;
			sort();
		}

		std::vector<pair_type>& a;
		size_t left;
		size_t right;
		size_t id;
		T updates;
	};


	void solve(std::istream& in, std::ostream& out) {
		int n, q;
		in >> n >> q;
		std::vector<pli> a(n);
		for (int i : range(n)) {
			int x;
			in >> x;
			a[i] = {x, i};
		}

		const int blocks_count = (n - 1) / Block<>::kSize + 1;
		std::vector<Block<>> blocks;
		blocks.reserve(blocks_count);
		for (int i : range(blocks_count)) {
			blocks.emplace_back(a, i);
		}

		auto get_block_id = [](const int index) {
			return index / Block<>::kSize;
		};

		for (int _ : range(q)) {
			int t;
			in >> t;
			if (t == 1) {
				int l, r;
				ll x;
				in >> l >> r >> x;
				--l;
				--r;
				const int left_block_id = get_block_id(l);
				const int right_block_id = get_block_id(r);
				for (int i : inclusiveRange(left_block_id, right_block_id)) {
					blocks[i].update(l, r, x);
				}
			} else {
				ll x;
				in >> x;
				int left = 0;
				int right = -1;
				for (const auto& block : blocks) {
					if (right == -1) {
						const int leftmost = block.find_leftmost(x);
						if (leftmost == -1) {
							continue;
						}
						left = leftmost;
						right = leftmost;
					}
					const int rightmost = block.find_rightmost(x);
					if (rightmost != -1) {
						right = rightmost;
					}
				}
//				debug(blocks.size());
//				debug(a, blocks.back().updates);
//				debug(left, right);
				out << right - left << std::endl;
			}
		}
	}


	EGukiZIGukiZiana() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n, q;
		in >> n >> q;
		std::vector<int> a(n);
		in >> a;

		std::vector<int> jans;
		int cnt = 0;
		for (int _ : range(q)) {
			int t;
			in >> t;
			if (t == 1) {
				int l, r;
				ll x;
				in >> l >> r >> x;
				for (int i : range(l - 1, r)) {
					a[i] += x;
				}
			} else {
				++cnt;
				ll x;
				in >> x;
				int left = -1;
				int right = -2;
				for (int i : range(n)) {
					if (a[i] == x) {
						if (left == -1) {
							left = i;
						}
						right = i;
					}
				}
				jans.emplace_back(right - left);
			}
		}

		std::vector<int> pans(cnt);
		out >> pans;

		if (jans != pans) {
			debug(jans, pans);
			return false;
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 5;
		const int kMaxQ = 5;
		const int kMaxValue = 10;

		const int n = Random::get(1, kMaxn);
		const int q = Random::get(1, kMaxQ);
		test << n << " " << q << std::endl;
		for (int i : range(n)) {
			test << Random::get(1, kMaxValue) << " ";
		}
		test << std::endl;

		for (int i : range(q)) {
			const int t = Random::get(1, 2);
			if (t == 1) {
				const int l = Random::get(1, n);
				const int r = Random::get(l, n);
				const int value = Random::get(1, kMaxValue);
				test << "1 " << l << " " << r << " " << value << std::endl;
			} else {
				const int value = Random::get(1, kMaxValue);
				test << "2 " << value << std::endl;
			}
		}

	}

};
