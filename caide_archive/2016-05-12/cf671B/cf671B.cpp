#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n, k;
	io >> n >> k;
	if (n == 1) {
		io << 0 << endl;
		return;
	}
	vector<ll> a(n);
	ll sum = 0;
	for (auto& it : a) {
		io >> it;
		sum += it;
	}
	ll mean = sum / n;
	ll vmax = sum / n + (sum % n != 0 ? 1 : 0);
	sort(all(a));
	ll min_value = a.front();
	ll max_value = a.back();

	int last = 0;
	bool ok = false;
	ll rem = k;
	for (int i = 1; i < n && a[i] < mean && rem > 0; last = i++) {
		ll diff = a[i] - a[i - 1];
		if (diff * i > rem) {
			ll steps = rem / i;
			min_value = min(mean, a[i - 1] + steps);
			ok = true;
			break;
		}
		rem -= diff * i;
	}
	if (!ok) {
		min_value = min(mean, a[last] + rem / (last + 1));
	}


	last = n - 1;
	rem = k;
	ok = false;
	for (int i = n - 2; i >= 0 && a[i] > mean && rem > 0; last = i--) {
		ll diff = a[i + 1] - a[i];
		if (diff * (n - i - 1) > rem) {
			ll steps = rem / (n - i - 1);
			max_value = max(vmax, a[i + 1] - steps);
			ok = true;
			break;
		}
		rem -= diff * (n - i - 1);
	}
	if (!ok) {
		max_value = max(vmax, a[last] - rem / (n - last));
	}


	io << max_value - min_value << endl;
}
