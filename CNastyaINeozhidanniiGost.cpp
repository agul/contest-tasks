#include "base/header.hpp"

class CNastyaINeozhidanniiGost {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		auto a = make_vector<int>(m, 0);
		in >> a;
		sort(a);
		int r, g;
		in >> g >> r;

		auto dist = make_vector<ll>(m, g, LINF);
		std::deque<pii> q;

		auto push = [&q, &dist](const int stop, const int time, const int cur_dist, const int len) {
			const int new_dist = cur_dist + len;
			if (dist[stop][time] <= new_dist) {
				return;
			}
			dist[stop][time] = new_dist;
			if (len == 0) {
				q.push_front({stop, time});
			} else {
				q.emplace_back(stop, time);
			}
		};

		push(0, 0, 0, 0);
		while (!q.empty()) {
			int stop, time;
			std::tie(stop, time) = q.front();
			q.pop_front();

			const int cur_dist = dist[stop][time];
			const int len = (time == 0 ? 1 : 0);

			if (stop > 0) {
				const int to = a[stop] - a[stop - 1];
				if (time + to <= g) {
					push(stop - 1, (time + to) % g, cur_dist, len);
				}
			}
			if (stop < m - 1) {
				const int to = a[stop + 1] - a[stop];
				if (time + to <= g) {
					push(stop + 1, (time + to) % g, cur_dist, len);
				}
			}
		}


		ll ans = LINF;
		for (int i : range(m)) {
			const int to = n - a[i];
			if (to <= g && dist[i][0] != LINF) {
				umin(ans, dist[i][0] * (r + g) + to);
			}
		}
		out << (ans == LINF ? -1 : ans) << std::endl;
	}


	CNastyaINeozhidanniiGost() {}

	int n, m, r, g;
	std::vector<int> a;
	std::unordered_set<pii> used;

	void solve_slow(std::istream& in, std::ostream& out) {
		in >> n >> m;
		auto a = make_vector<int>(m, 0);
		in >> a;
		sort(a);
		in >> r >> g;

	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& out) {
		const int kMaxn = 20;
		const int kMaxTime = 1000;

		int n = Random::get(1, kMaxn);
		int m = Random::get(2, n);

		std::vector<int> stops(n + 1);
		std::iota(all(stops), 0);
		std::random_shuffle(all(stops));
		stops.resize(m);

		int g = Random::get(1, kMaxTime);
		int r = Random::get(1, kMaxTime);

		out << n << " " << m << std::endl;
		for (int x : stops) {
			out << x << " ";
		}
		out << std::endl;
		out << g << " " << r << std::endl;
	}

};
