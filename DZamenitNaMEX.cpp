#include "base/header.hpp"

class DZamenitNaMEX {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		int timer = 0;
		std::vector<int> time(n + 5, 0);
		auto get_mex = [&timer, &time, &a, n]() {
			++timer;
			for (int x : a) {
				time[x] = timer;
			}
			for (int i : inclusiveRange<int>(time.size())) {
				if (time[i] != timer) {
					return i;
				}
			}
		};

		auto sorted = [&a, n]() {
			for (int i : range(1, n)) {
				if (a[i] < a[i - 1]) {
					return false;
				}
			}
			return true;
		};
		std::vector<int> ans;

//		int delta = 1;
//		while (!sorted()) {
//			const int mex = get_mex();
//			if (mex == n) {
//				delta = 1;
//			}
//			if (mex == 0) {
//				delta = 0;
//			}
//			debug(a, mex);
//			const int pos = mex - delta;
//			a[pos] = mex;
//			ans.emplace_back(pos);
//		}

//		int value = 0;
//		while (!sorted()) {
//			const int mex = get_mex();
//			debug(a, mex);
//			bool ok = false;
//			for (int i : range(value + 1, n)) {
//				if (a[i] == value) {
//					a[i] = mex;
//					ans.emplace_back(i);
//					ok = true;
//					break;
//				}
//			}
//			if (!ok) {
//				a[mex] = mex;
//				ans.emplace_back(mex);
//				++value;
//			}
//		}

		int value = 0;
		while (!sorted()) {
			if (a[value] == value) {
				++value;
				continue;
			}
			const int mex = get_mex();
			if (mex == n) {
				for (int i : range(n)) {
					if (a[i] == value) {
						a[i] = mex;
						ans.emplace_back(i);
						break;
					}
				}
				continue;
			}
			// debug(a, mex);
			const int pos = mex;
			a[pos] = mex;
			ans.emplace_back(pos);
		}

		out << ans.size() << std::endl;
		for (int x : ans) {
			out << x + 1 << " ";
		}
		out << std::endl;
	}


	DZamenitNaMEX() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int testsCount;
		in >> testsCount;
		for (int testid : range(testsCount)) {
			int n;
			in >> n;
			std::vector<int> a(n);
			in >> a;

			int k;
			out >> k;
			std::vector<int> pans(k);
			out >> pans;

			if (k >= n * 2) {
				debug(testid, n * 2, k);
				return false;
			}

			int timer = 0;
			std::vector<int> time(n + 5, 0);
			auto get_mex = [&timer, &time, &a, n]() {
				++timer;
				for (int x : a) {
					time[x] = timer;
				}
				for (int i : inclusiveRange<int>(time.size())) {
					if (time[i] != timer) {
						return i;
					}
				}
			};

			for (int x : pans) {
				a[x - 1] = get_mex();
			}

			auto b = a;
			sort(a);
			if (a != b) {
				debug(testid, a, b);
				return false;
			}

		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 1000;
		const int n = Random::get(1, kMaxn);
		test << 1 << std::endl << n << std::endl;
		for (int i : range(n)) {
			test << Random::get(0, n) << " ";
		}
		test << std::endl;
	}

};
