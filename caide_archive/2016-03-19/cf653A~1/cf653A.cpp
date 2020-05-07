#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n, k, f;
	ins >> n;
	vector<int>t;
	for (int i = 0; i < n; i++)
	{
		ins >> k;
		f = 0;
		for (int j = 0; j < t.size(); j++)
			if (t[j] == k)
			{
				f = 1;
				break;
			}
		if (f == 0)
		{
			t.push_back(k);
		}
	}
	sort(t.begin(), t.end());
	for (int i = 0; i < t.size() - 2; i++)
		if ((t[i] == t[i + 1] - 1) && (t[i] == t[i + 2] - 2))
		{
			out << "YES";
			return;
		}
	out << "NO";
	return;
}
