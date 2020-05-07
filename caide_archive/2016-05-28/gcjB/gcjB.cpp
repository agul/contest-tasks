#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 222;

double get_prob(const std::vector<double>& a) {
	using pid = std::pair<int, double>;
	std::vector<pid> states = { {0, 1} };
	for (const auto& it : a) {
		std::vector<pid> upd;
		for (const auto& state : states) {
			upd.emplace_back(state.first + 1, state.second * it);
			upd.emplace_back(state.first - 1, state.second * (1 - it));
		}
		states.swap(upd);
		upd.clear();
		sort(all(states));
		for (int i = 0, cur_ind = 0; i < states.size(); i = cur_ind) {
			double sum = 0;
			while (cur_ind < states.size() && states[i].first == states[cur_ind].first) {
				sum += states[cur_ind].second;
				++cur_ind;
			}
			upd.emplace_back(states[i].first, sum);
		}
		states.swap(upd);
	}
	double ret = 0;
	for (const auto& state : states) {
		if (state.first == 0) {
			ret += state.second;
		}
	}
	return ret;
}

void solve(istream& in, ostream& out) {
	input_txt();
	in >> __;
	for (int _ = 1; _ <= __; ++_) {
		std::cerr << _ << std::endl;
		out << "Case #" << _ << ": ";
		int n, k;
		in >> n >> k;
		vector<double> a(n);
		in >> a;
		sort(all(a));
		double ans = 0;
		for (int i = 0; i <= n - k; ++i) {
			vector<double> val;
			val.insert(val.end(), a.begin() + i, a.begin() + i + k);
			const double cur = get_prob(val);
			umax(ans, cur);
		}
		{
			for (int i = 0; i < k; ++i) {
				vector<double> val;
				val.insert(val.end(), a.begin(), a.begin() + i);
				val.insert(val.end(), a.begin() + n - k + i, a.end());
				umax(ans, get_prob(val));
			}
		}
		out << fixed << setprecision(16) << ans << endl;
	}
}
