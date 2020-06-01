#include "base/header.hpp"
#include "data_structures/segment_tree/top_down_segment_tree.hpp"

class EProstoeZadanie {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		// solve_sqrt_decomposition(in, out);
		solve_segment_tree(in, out);
	}

	struct ApplyUpdate : Applier<int> {
		int operator()(const int& value, const int& update, const size_t left, const size_t right) const {
			// debug("apply", left, right, update);
			if (update == -1) {
				return value;
			}
			return update * (right - left + 1);
		}
	};

	struct MergeUpdates : Merger<int> {
		int operator()(const int& acc_updates, const int& update) const {
			// debug("merge", acc_updates, update);
			if (update == -1) {
				return acc_updates;
			}
			return update;
		}
	};

	using SegmentTree = TopDownSegmentTree<int, std::plus<int>, int, ApplyUpdate, MergeUpdates>;

	void solve_segment_tree(std::istream& in, std::ostream& out) {
		const int kAlphabetSize = 26;

		int n, q;
		std::string s;
		in >> n >> q >> s;
		std::vector<int> a(n);
		for (int i : range(n)) {
			a[i] = s[i] - 'a';
		}

		std::vector<SegmentTree> trees(kAlphabetSize, SegmentTree(n, 0, std::plus<int>(), -1));

		for (int i : range(kAlphabetSize)) {
			std::vector<int> b = a;
			for (int& x : b) {
				x = (x == i ? 1 : 0);
			}
			// debug(b);
			trees[i].build(b);
			// debug(trees[i].data());
			// debug(trees[i].updates());
			const int x = std::accumulate(all(b), 0);
			const int y = trees[i].get(0, n);
			// debug(x, y);
		}

		for (int _ : range(q)) {
			int l, r, t;
			in >> l >> r >> t;
			--l, --r;
			std::vector<int> cnt(kAlphabetSize);
			for (int i : range(kAlphabetSize)) {
				cnt[i] += trees[i].get(l, r);
				trees[i].range_update(l, r, 0);
			}
			// debug(cnt);
			int index = (t == 1 ? l : r);
			const int delta = (t == 1 ? 1 : -1);
			for (int i : range(kAlphabetSize)) {
				if (cnt[i] == 0) {
					continue;
				}
				int from = index;
				int to = (cnt[i] - 1) * delta + index;
				if (from > to) {
					std::swap(from, to);
				}
				// debug(from, to);
				trees[i].range_update(from, to, 1);
				index += cnt[i] * delta;
			}
		}
		for (int i : range(n)) {
			for (int j : range(kAlphabetSize)) {
				const int cur_value = trees[j].get(i);
				if (cur_value > 0) {
					a[i] = j;
					break;
				}
			}
		}

		std::string ans;
		for (int x : a) {
			ans += x + 'a';
		}
		out << ans << std::endl;
	}

	void solve_sqrt_decomposition(std::istream& in, std::ostream& out) {
		const int kBucketSize = 350;
		const int kAlphabetSize = 26;

		int n, q;
		std::string s;
		in >> n >> q >> s;
		std::vector<int> a(n);
		for (int i : range(n)) {
			a[i] = s[i] - 'a';
		}

		auto build_string = [](const std::vector<int>& a) {
			std::string ans;
			for (int x : a) {
				ans += x + 'a';
			}
			return ans;
		};

		const int buckets_count = (n - 1) / kBucketSize + 1;

		auto get_bucket = [kBucketSize](const int n) {
			return n / kBucketSize;
		};

		auto bucket_begin = [kBucketSize](const int bucket_id) {
			return bucket_id * kBucketSize;
		};

		auto bucket_end = [kBucketSize, n](const int bucket_id) {
			return std::min((bucket_id + 1) * kBucketSize, n) - 1;
		};

		auto bucket_size = [&bucket_begin, &bucket_end](const int bucket_id) {
			return bucket_end(bucket_id) - bucket_begin(bucket_id) + 1;
		};

		auto counter = make_vector<int>(buckets_count, kAlphabetSize, 0);
		for (int i : range(n)) {
			counter[get_bucket(i)][a[i]]++;
		}

		std::vector<int> sorted(buckets_count, 0);

		auto restore_bucket = [&sorted, &counter, &bucket_begin, &bucket_end, &a](const int bucket_id) {
			if (sorted[bucket_id] == 0) {
				return;
			}
			// debug("restore ", bucket_id);
			const auto& bucket_counter = counter[bucket_id];
			const int delta = sorted[bucket_id];
			// debug(bucket_counter);
			int index = (delta == 1 ? bucket_begin(bucket_id) : bucket_end(bucket_id));
			// debug(index);
			for (int i : range(kAlphabetSize)) {
				for (int j : range(bucket_counter[i])) {
					a[index] = i;
					index += delta;
				}
			}
			sorted[bucket_id] = 0;
		};

		auto restore_ans = [&sorted, &restore_bucket, &a, buckets_count, &build_string]() {
			auto backup_a = a;
			auto backup_sorted = sorted;
			for (int i : range(buckets_count)) {
				restore_bucket(i);
			}
			const std::string ans = build_string(a);
			a = backup_a;
			sorted = backup_sorted;
			return ans;
		};

		for (int _ : range(q)) {
			// debug(_);
			// debug(restore_ans());
			int l, r, t;
			in >> l >> r >> t;
			--l;
			--r;

			const int l_bucket = get_bucket(l);
			const int r_bucket = get_bucket(r);

			// debug(l, l_bucket);
			// debug(r, r_bucket);

			restore_bucket(l_bucket);
			restore_bucket(r_bucket);

			std::vector<int> cur_cnt(kAlphabetSize, 0);

			for (int bucket_id : inclusiveRange(l_bucket, r_bucket)) {
				const int from = bucket_begin(bucket_id);
				const int to = bucket_end(bucket_id);
				if (l > from || r < to) {
					for (int i : inclusiveRange(std::max(l, from), std::min(r, to))) {
						const int cur_value = a[i];
						cur_cnt[cur_value]++;
					}
				} else {
					for (int i : range(kAlphabetSize)) {
						cur_cnt[i] += counter[bucket_id][i];
					}
				}
			}

			// debug(cur_cnt);

			int symbol = (t == 1 ? 0 : kAlphabetSize - 1);
			const int delta = (t == 1 ? 1 : -1);

			auto next_symbol = [&symbol, &cur_cnt, delta]() {
				while (cur_cnt[symbol] == 0) {
					symbol += delta;
				}
				--cur_cnt[symbol];
				return symbol;
			};

			for (int bucket_id : inclusiveRange(l_bucket, r_bucket)) {
				const int from = bucket_begin(bucket_id);
				const int to = bucket_end(bucket_id);
				// debug(from, to);
				if (l > from || r < to) {
					for (int i : inclusiveRange(std::max(l, from), std::min(r, to))) {
						--counter[bucket_id][a[i]];
						a[i] = next_symbol();
						++counter[bucket_id][a[i]];
					}
				} else {
					int sum = 0;
					auto& bucket_counter = counter[bucket_id];
					const int cur_bucket_size = bucket_size(bucket_id);
					// debug(bucket_counter);
					// debug(cur_bucket_size);
					bucket_counter.assign(kAlphabetSize, 0);
					while (sum < cur_bucket_size) {
						const int symbol = next_symbol();
						++bucket_counter[symbol];
						++sum;
						if (sum == cur_bucket_size || cur_cnt[symbol] == 0) {
							continue;
						}
						const int diff = std::min(cur_cnt[symbol], cur_bucket_size - sum);
						bucket_counter[symbol] += diff;
						cur_cnt[symbol] -= diff;
						sum += diff;
					}
					// debug(bucket_counter);
					sorted[bucket_id] = delta;
				}
			}
		}

		const std::string ans = restore_ans();
		out << ans << std::endl;
	}


	EProstoeZadanie() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n, q;
		std::string s;
		in >> n >> q >> s;
		for (int i : range(q)) {
			int l, r, t;
			in >> l >> r >> t;
			std::sort(s.begin() + l - 1, s.begin() + r);
			if (t == 0) {
				std::reverse(s.begin() + l - 1, s.begin() + r);
			}
		}
		std::string pans;
		out >> pans;
		if (s != pans) {
			debug(s, pans);
			return false;
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 1000;
		const int kMaxQ = 100;

		const int n = Random::get(1, kMaxn);
		const int q = Random::get(1, kMaxQ);
		std::string s;
		for (int i : range(n)) {
			s += Random::get(0, 25) + 'a';
		}
		test << n << " " << q << std::endl << s << std::endl;
		for (int i : range(q)) {
			const int L = Random::get(1, n);
			const int R = Random::get(L, n);
			const int T = Random::get(0, 1);
			test << L << " " << R << " " << T << std::endl;
		}
	}

};
