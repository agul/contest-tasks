#include "base/header.hpp"

class ERestavratsionnoeRasstoyanie {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		ll A, RM, M;
		in >> n >> A >> RM >> M;
		std::vector<ll> a(n);
		in >> a;
		sort(a);


		int L = a.front();
		int R = a.back();

		auto check = [&a, A, RM, M](const ll height) {
			ll total_add = 0;
			ll total_remove = 0;
			for (ll x : a) {
				if (x < height) {
					total_add += height - x;
				} else {
					total_remove += x - height;
				}
			}

			const ll total_move = std::min(total_add, total_remove);
			return std::min(
					total_add * A + total_remove * RM,
					total_move * M + (total_add - total_move) * A + (total_remove - total_move) * RM
			);
		};

		for (int i : range(0, 9)) {
			// out << i << " " << check(i) << std::endl;
		}

		while (R - L > 2) {
			const int diff = (R - L) / 3;
			int m1 = L + diff;
			int m2 = R - diff;

			const ll l_value = check(m1);
			const ll r_value = check(m2);
			debug(L, l_value);
			debug(R, r_value);

			if (l_value > r_value) {
				L = m1;
			} else {
				R = m2;
			}
		}

		debug(L, R);
		ll ans = LINF;
		for (int i : range(L, R + 5)) {
			umin(ans, check(i));
		}
		out << ans << std::endl;
		return;

/*
		ll cur_height = 0;

		ll cnt_less = 0;
		ll cnt_more = n;

		ll total_add = 0;
		ll total_remove = std::accumulate(all(a), 0LL);
		ll ans = total_remove * R;


		int index = 0;
		while (index < n) {
			ll cnt_eq = 0;
			const ll cur_value = a[index];
			while (index < n && a[index] == cur_value) {
				++cnt_eq;
				++index;
			}


			const ll height_diff = cur_value - cur_height;
			total_add += cnt_less * height_diff;
			total_remove -= cnt_more * height_diff;

			umin(ans, total_add * A + total_remove * R);

			const ll total_move = std::min(total_add, total_remove);
			umin(ans, total_move * M + (total_add - total_move) * A + (total_remove - total_move) * R);

			cur_height = cur_value;

			cnt_more -= cnt_eq;
			cnt_less += cnt_eq;
		}

		out << ans << std::endl; */
	}


	ERestavratsionnoeRasstoyanie() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
